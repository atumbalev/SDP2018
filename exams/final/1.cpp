#include <iostream>
#include <unordered_map>
// or the BST you had in the notes
// or just any container (slow but good enough for an exam)
#include <fstream>
#include <string>
#include <cassert>

int main(int argc, char const *argv[])
{
	std::string inFileName, outFileName;
	std::cin >> inFileName >> outFileName;
	std::ifstream in(inFileName);
	std::ofstream out(outFileName);

	assert(in && out);

	int numberOfStudents;
	std::string name, surname;

	in >> numberOfStudents;

	std::unordered_map<std::string, unsigned> surnames;

	for (int i = 0 ; i < numberOfStudents ; i++)
	{
		in >> name >> surname;
		auto found = surnames.find(surname);

		if (found != surnames.end())
		{
			surnames[surname] = found->second + 1;		
		}

		else
		{
			surnames[surname] = 1;
		}

		out << name << " " << surname << " - " << surname;
		if (surnames[surname] != 1)
		{
			out << surnames[surname];
		}
		out << std::endl;

	}

	return 0;
}