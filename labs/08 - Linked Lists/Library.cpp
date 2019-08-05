/*Даден е текстов файл, в който е записана информация за книгите в библиотека. Форматът на файла е следният:
Име Фамилия (на автора)	брой книги
Следват данни за указания брой книги в следния формат:
Година на издаване	Име на книга
като данните за всяка книга на даден автор са на отделен ред.

Да се дефинира функция, която организира картотека на книгите в библиотеката, като информацията от текстовия файл се прочете и се запише в свързан списък от автори. В записа за всеки автор се включва информация за името на автора и списък от неговите книги. Картотеката трябва да се поддържа организирана по азбучен ред на авторите, за да може да се осъществява по-бързо търсене по името на автора.
Да се дефинира функция, която обработва списъка от автори с помощта на указател към филтрираща функция (предикат), подаден като аргумент. Списъкът, съдържащ елементите, които удовлетворяват условието на филтриращата функция, да се запише в двоичен файл по такъв начин, че данните да могат да бъдат възстановени коректно.*/

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

struct book
{
	int year;
	std::string title;
	void print(std::ostream& out = std::cout) const
	{
		out << year << " " << title << std::endl;
	}

	void printBinary(std::ostream& out) const
	{
		out.write(reinterpret_cast<const char*>(&year), sizeof(year));
		size_t size = title.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		out.write(title.c_str(), title.size());
	}
};

struct author
{
	std::string firstName, lastName;
	std::list<book> books;
	bool operator>(const author& other) const
	{
		if (firstName > other.firstName)
		{
			return true;
		}

		if (firstName == other.firstName && lastName > other.lastName)
		{
			return true;
		}

		return false;
	}

	void print(std::ostream& out = std::cout) const
	{
		out << firstName << " " << lastName<<std::endl;
		for(const book& b : books)
		{
			b.print(out);
		}
	}

	void printBinary(std::ostream& out) const
	{
		size_t size = firstName.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		out.write(firstName.c_str(), firstName.size());
		size = lastName.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		out.write(lastName.c_str(), lastName.size());
		size = books.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(size));
		for(const book& bk : books)
		{
			bk.printBinary(out);
		}
	}
};

void insertIntoSortedList(std::list<author>& authors, const author& auth)
{
	auto it = authors.cbegin();
	for(it; it != authors.cend() && auth > *it; ++it)
	{}
	authors.insert(it, auth);
}

void filterAndWrite(
	const std::list<author>& authors,
	bool(*predicate)(const author&),
	std::string fileName)
{
	std::ofstream bFile(fileName, std::ios::binary | std::ios::out);
	assert(bFile);
	for (const author& a : authors)
	{
		if (predicate(a))
		{	
			a.printBinary(bFile);
		}
	}

	bFile.close();
}

std::list<author> read(std::istream& file)
{
	std::list<author> result;
	author auth;
	unsigned books;
	book bk;
	while(!file.eof())
	{
		auth.books.clear();
		file >> auth.firstName;
		file >> auth.lastName;
		file >> books;
		for(int i = 0 ;i < books; i++)
		{
			file >> bk.year;
			file.ignore(); // white space
			std::getline(file, bk.title);
			auth.books.push_back(bk);
		}
		insertIntoSortedList(result, auth);
	}

	return result;
}

int main(int argc, char const *argv[])
{

	std::ifstream f("authors.txt");
	assert(f);
	std::list<author> authors = read(f);
	for (const author& a : authors)
	{
		a.print();
	}
	f.close();

	filterAndWrite(authors, [](const author& a){return a.firstName == "Pe6o";},"test");
	return 0;
}
