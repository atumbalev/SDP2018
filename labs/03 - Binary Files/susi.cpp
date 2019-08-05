#include<iostream>
#include<string.h>
#include<fstream>
#include<string>
#include<assert.h>

class Student
{
private:
	char FN[6], name[11];
	double grade;
public:
	Student(): FN(""), name(""), grade(0)
	{

	};

	Student(const char* _FN, const char* _name, double _grade): grade(_grade)
	{
		strcpy(this->FN, _FN);
		strcpy(this->name, _name);
	}

	void print() const
	{
		writeToText(std::cout);
	}

	void writeToText(std::ostream& out) const
	{
		out << FN << " " << name << " " << grade << "\n";
	}

	void readFromText(std::istream& in)
	{
		in >> FN >> name >> grade;
	}

	void writeToBin(std::ostream& out) const
	{

		out.write(reinterpret_cast<const char*>(this), sizeof(Student));
	}

	void readFromBin(std::istream& in)
	{
		in.read(reinterpret_cast<char*>(this), sizeof(Student));
	}

	double getGrade() const
	{
		return grade;
	}
};

template<typename T>
using Predicate = bool(*)(T);

class SUSI
{
private:
	std::fstream file;
	size_t size;
	
	size_t getPosition(size_t index) const
	{
		return index * sizeof(Student);
	}

	void reset()
	{
		file.seekg(0);
		file.seekp(0);
	}

	void swapStudents(size_t a, size_t b)
	{
		Student tempA, tempB;
		
		file.seekg(getPosition(a));
		tempA.readFromBin(file);
		
		file.seekg(getPosition(b));
		tempB.readFromBin(file);
		
		file.seekp(getPosition(a));
		tempB.writeToBin(file);

		file.seekp(getPosition(b));
		tempA.writeToBin(file);

		reset();
	}

public:
	SUSI(std::string filename, size_t _size): size(_size)
	{
		file.open(filename, std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
		assert(file);
		Student empty;
		for (int i = 0; i < size; ++i)
		{
			empty.writeToBin(file);
		}
		reset();
	}

	SUSI(std::string binFilename, std::string textFilename): size(0)
	{
		file.open(binFilename, std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc);
		assert(file);
		std::ifstream text(textFilename);
		assert(text);
		Student toStore;
		while(!text.eof())
		{
			toStore.readFromText(text);
			toStore.writeToBin(file);
			size++;
		}
		reset();
	}

	SUSI(std::string filename)
	{
		file.open(filename, std::ios::in|std::ios::out|std::ios::binary);
		assert(file);
		file.seekg(0, std::ios::end);
		size = file.tellg() / sizeof(Student);
		reset(); 
	}

	~SUSI()
	{
		file.close();
	}

	void deleteStudent(size_t index)
	{
		assert(index < size);
		Student empty;
		file.seekp(getPosition(index));
		empty.writeToBin(file);
		reset();
	}

	void setStudent(size_t index, const Student& stud)
	{
		assert(index < size);
		file.seekp(getPosition(index));
		stud.writeToBin(file);
		reset();
	}

	Student getStudent(size_t index)
	{
		Student stud;
		assert(index < size);
		file.seekg(getPosition(index));
		stud.readFromBin(file);
		reset();

		return stud;
	}

	void addStudent(const Student& stud)
	{
		file.seekp(getPosition(size));
		stud.writeToBin(file);
		size++;
		reset();
	}

	void printFile(Predicate<Student> pred = [](Student stud){ return true; })
	{
		Student toPrint;
		for (size_t i = 0; i < size; ++i)
		{
			toPrint = getStudent(i);
			if (pred(toPrint))
			{
				getStudent(i).print();
			}
		}
		reset();
	}

	void sortByGrade()
	{
		Student stud;
		double maxGrade;
		size_t toSwap;
		for (size_t i = 0; i < size - 1; ++i)
		{
			stud = getStudent(i);
			maxGrade = stud.getGrade();
			toSwap = i;

			for (size_t j = i + 1; j < size; ++j)
			{
				stud = getStudent(j);
				if (stud.getGrade() > maxGrade)
				{
					maxGrade = stud.getGrade();
					toSwap = j;
				}
			}

			swapStudents(i, toSwap);
		}

		reset();
	}
};

int main(int argc, char const *argv[])
{
	SUSI susi("pe6ovci.bin", "pe6ovci.txt");
	Student navlek("18181", "navlek", 6);
	susi.addStudent(navlek);
	susi.sortByGrade();
	susi.printFile([](Student stud){return stud.getGrade() > 3;});

	return 0;
}
