#include <iostream>
#include <string>
#include <queue>

int main(int argc, char const *argv[])
{
	std::queue<std::string> q;
	std::string str = "1";
	q.push(str);
	int n;
	
	std::cin>>n;

	for (int i = 0; i < n; ++i)
	{
		str = q.front();
		q.pop();
		std::cout<<str<<std::endl;
		q.push(str + "0");
		q.push(str + "1");
	}

	return 0;
}
