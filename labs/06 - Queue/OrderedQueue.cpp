#include <iostream>
#include <queue>

template<typename T>
bool orderedQueue(std::queue<T>& q)
{
	if (q.size() < 2)
	{
		return true;
	}

	bool couldBeIncreasing = true, couldBeDecreasing = true;
	
	int last = q.front();
	q.pop();
	q.push(last);
	for (int i = 1; i < q.size(); ++i && couldBeIncreasing && couldBeDecreasing)
	{
		if (last < q.front())
		{
			couldBeDecreasing = false;
		}

		if (last > q.front())
		{
			couldBeIncreasing = false;
		}

		last = q.front();
		q.pop();
		q.push(last);
	}

	return couldBeIncreasing || couldBeDecreasing;

}

int main(int argc, char const *argv[])
{
	std::queue<int> q;

	int number;

	while(std::cin>>number)
	{
		q.push(number);
	}

	std::cout<<std::boolalpha<<orderedQueue(q)<<std::endl;
	return 0;
}
