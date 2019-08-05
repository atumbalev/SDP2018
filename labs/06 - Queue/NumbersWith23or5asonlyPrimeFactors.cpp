/*
зад. 2
Напишете програма, която намира n-тото по големина число, чиито прости делители са измежду 2, 3 и 5 (т.е. от числата,
чиито прости делители са измежду 2, 3 и 5 да се намери n-тото по големина).
*/

#include <queue>
#include <iostream>

int main(int argc, char const *argv[])
{
	int n, min;

	std::cin>>n;

	std::queue<int> q2, q3, q5;
	q2.push(2);
	q3.push(3);
	q5.push(5);

	for (int i = 0 ; i < n ; i++)
	{
		min = std::min(std::min(q2.front(), q3.front()), q5.front());

		if (q2.front() == min)
		{
			q2.pop();
		}

		if (q3.front() == min)
		{
			q3.pop();
		}

		if (q5.front() == min)
		{
			q5.pop();
		}

		q2.push(min * 2);
		q3.push(min * 3);
		q5.push(min * 5);

	}
	std::cout<<min<<std::endl;
	return 0;
}
