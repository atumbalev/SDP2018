#include <iostream>
#include <functional> // std::hash

struct JavaStringHasher
{
	size_t operator()(const std::string& str)
	{
		size_t hash = 0;

		for (char c : str)
		{
			hash = (hash << 5) - hash + c; // hash * 31 + c
		}

		return hash;
	}
};

int main(int argc, char const *argv[])
{
	std::string s("sdp");

	std::cout<<std::hash<std::string>{}(s)<<std::endl;
	std::cout<<JavaStringHasher{}(s)<<std::endl;
	return 0;
}