#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <assert.h>

struct book
{
	char author[23];
	char title[31];
	unsigned numPages;

	book(const char* _author = "", const char* _title = "", unsigned _numPages = 0) : numPages(_numPages)
	{
		strcpy(author, _author);
		strcpy(title, _title);
	}

	void printText(std::ostream& out = std::cout) const
	{
		out << author << " " << title << " " << numPages << std::endl;
	}

	void printBinary(std::ostream& out) const
	{
		out.write(reinterpret_cast<const char*>(this), sizeof(book)); 
	}

	std::istream& readBinary(std::istream& in)
	{
		return in.read(reinterpret_cast<char*>(this), sizeof(book));
	}

	bool operator<(const book& other) const
	{
		if (strcmp(author, other.author) < 0)
		{
			return true;
		}

		if (strcmp(author, other.author) == 0)
		{
			return numPages < other.numPages;
		}

		return false;
	}

	bool moreThan500Pages() const
	{
		return numPages > 500;
	}
};

void fillFile(std::ostream& out, const std::vector<book>& books)
{
	for (const book& book : books)
	{
		book.printBinary(out);
	}
}

size_t getSize(std::istream& in)
{
	in.seekg(0, std::ios::end);
	return in.tellg() / sizeof(book);
}

book getBook(std::istream& in, size_t i)
{
	in.seekg(i * sizeof(book));
	book res;
	res.readBinary(in);
	return res;
}

void writeBook(std::ostream& out, size_t i, const book& b)
{
	out.seekp(i * sizeof(book));
	b.printBinary(out);
}

void swapBooks(std::iostream& file, size_t i, size_t j)
{
	book tmp1, tmp2;

	tmp1 = getBook(file, i);
	tmp2 = getBook(file, j);

	writeBook(file, i, tmp2);
	writeBook(file, j, tmp1);
}

void test(std::istream& in)
{
	size_t size = getSize(in);

	for (int i = 0; i < size; ++i)
	{
		getBook(in, i).printText();
	}
}

void selectionSort(std::iostream& stream)
{
	book max, tmp;
	size_t maxIndex;

	size_t size = getSize(stream);

	for(int i = 0 ; i < size - 1; ++i)
	{
		maxIndex = i;
		max = getBook(stream, i);
		for(int j = i + 1; j < size; ++j)
		{
			tmp = getBook(stream, j);
			if (tmp < max)
			{
				max = tmp;
				maxIndex = j;
			}
		}

		if (i != maxIndex)
		{
			swapBooks(stream, i, maxIndex);
		}
	}
}

void mergeSorted(std::ostream& out, std::istream& in1, std::istream& in2)
{
	size_t size1 = getSize(in1);
	size_t size2 = getSize(in2);

	size_t i = 0, j = 0;

	book head1, head2;
	while(i != size1 && j != size2)
	{
		head1 = getBook(in1, i);
		head2 = getBook(in2, j);

		if (head1 < head2)
		{
			head1.printBinary(out);
			++i;
		}

		else
		{
			head2.printBinary(out);
			++j;
		}
	}
	
	while( i != size1)
	{
		head1 = getBook(in1, i);
		++i;
		head1.printBinary(out);
	}

	while( j != size2)
	{
		head1 = getBook(in2, j);
		++j;
		head1.printBinary(out);
	}
}

void filterByPages(std::istream& in, std::ostream& out)
{
	size_t size = getSize(in);
	book tmp;
	for(size_t i = 0 ; i < size; ++i)
	{
		tmp = getBook(in, i);
		if (tmp.moreThan500Pages())
		{
			out << i << " ";
		}
	}
}

int main(int argc, char const *argv[])
{
	std::fstream f1("file1.bin", std::ios::binary | std::ios::in | std::ios::out);
	assert(f1);
	std::fstream f2("file2.bin", std::ios::binary | std::ios::in | std::ios::out);
	assert(f2);

	std::vector<book> books1 = {book("Kappo", "123", 300), book("Kappo", "345", 200), book("Aappo", "678", 600)};
	std::vector<book> books2 = {book("Kappo", "kniga", 600), book("Keepo", "druga", 500), book("Aappo", "treta", 300)};

	fillFile(f1, books1);
	fillFile(f2, books2);

	test(f1);
	std::cout<<std::endl;
	test(f2);
	std::cout<<std::endl<<std::endl;

	selectionSort(f2);
	selectionSort(f1);

	test(f1);
	std::cout<<std::endl;
	test(f2);
	std::cout<<std::endl<<std::endl;

	std::fstream fMerged("fileMerged.bin", std::ios::binary | std::ios::in | std::ios::out);
	assert(fMerged);

	mergeSorted(fMerged, f1, f2);
	test(fMerged);

	std::ofstream fLong("fileLongBooks.txt");
	filterByPages(fMerged, fLong);

	f1.close();
	f2.close();
	fMerged.close();
	fLong.close();
	return 0;
}
