#include <iostream>
#include <queue>

int main(int argc, char const *argv[])
{
	int N, k;
	std::queue<int> q;


	std::cin>>N>>k;
	q.push(N);

	int number;
	for(int i = 0 ; i < k; i++)
	{
		number = q.front();
		q.push(number + 1);
		q.push(number * 2);
		q.pop();

	}
	std::cout<<number<<std::endl;
	return 0;
}
