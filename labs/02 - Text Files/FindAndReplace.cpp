// Replace all examples of (a+b).(a-b) in a text file with (a^2-b^2). a and b are digits.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

// O(n^2) pattern matching
// Later lectures will cover a more efficient solution

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

std::string match(std::ifstream& f)
{
	std::string findBuffer = "(";
	std::string replaceBuffer = "(a^2-b^2)";

	char c;
	c = f.get();
	if (f.peek() < '0' || f.peek() > '9')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;
	replaceBuffer[1] = c;

	if (f.peek() != '+')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer +=c;

	if (f.peek() < '0' || f.peek() > '9')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;
	replaceBuffer[5] = c;

	if (f.peek() != ')')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != '.')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != '(')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != replaceBuffer[1])
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != '-')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != replaceBuffer[5])
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	if (f.peek() != ')')
	{
		return findBuffer;
	}
	c = f.get();
	findBuffer += c;

	return replaceBuffer;
}

void findAndReplaceWithBuffer(std::iostream& buffer, const std::string& fname)
{
	char c;
	std::ifstream find(fname);
	while(!find.eof())
	{
		c = find.peek();
		if (c == '(')
		{
				buffer << match(find);
		}
		else
		{
			c = find.get();
			buffer << c;
		}
	}

	find.close();
	std::ofstream replace(fname, std::ios::trunc | std::ios::out);
	buffer.seekg(0);
	buffer.clear();
	while (!buffer.eof())
	{	
		char c = buffer.get();
		if (c != -1)
		{
			replace<<c;
		}
	}
}

int main(int argc, char const *argv[])
{
	std::fstream fileBuffer("fbuffer"); // file buffer
	std::stringstream memoryBuffer(""); // in memory, stringstream buffer (pick one)
	findAndReplaceWithBuffer(memoryBuffer, "test.txt");
	return 0;
}
