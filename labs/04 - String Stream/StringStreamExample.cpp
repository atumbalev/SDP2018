#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>


int main(int argc, char const *argv[])
{
	std::string str = "kappa 1 10 1.4";
	std::string word;
	double number;

	// String to StringStream

	std::istringstream ss1(str);
	ss1 >> word;
	std::cout<<word<<std::endl;

	ss1 >> number;
	std::cout<<number<<std::endl;

	ss1 >> number;
	std::cout<<number<<std::endl;
	ss1 >> number;
	std::cout<<number<<std::endl;

	// output string stream
	std::ostringstream ss2;
	ss2 << "37 in dec: " << 37 << std::endl;
	// you can use formatting
	ss2 << "37 in hex: " << std::hex << 37 << std::endl;
	ss2 << true;
	ss2 << std::boolalpha << true;
	std::cout<<ss2.str()<<std::endl;
	return 0;
}
