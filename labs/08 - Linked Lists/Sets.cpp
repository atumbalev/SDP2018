#include<iostream>
#include<list>

template<typename T>
using set = std::list<T>;

template<typename T>
void insertIntoSet(set<T>& ls, T num)
{
	auto it = ls.cbegin();
	for(it; it != ls.cend() && num > *it; ++it)
	{}
	ls.insert(it, num);
}

template<typename T>
set<T> operator+(const set<T>& set1, const set<T>& set2)
{
	if (set1.empty())
	{
		return set2;
	}

	if (set2.empty())
	{
		return set1;
	}

	set<T> result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while(it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			result.push_back(*it1);
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			result.push_back(*it1);
			++it1;
		}
		else
		{
			result.push_back(*it2);
			++it2;
		}
	}

	for(; it1 != set1.cend(); ++it1)
	{
		result.push_back(*it1);
	}

	for(; it2 != set2.cend(); ++it2)
	{
		result.push_back(*it2);
	}

	return result;
}

template<typename T>
set<T> operator*(const set<T>& set1, const set<T>& set2)
{
	if (set1.empty() || set2.empty())
	{
		return {};
	}
	set<T> result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while(it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			result.push_back(*it1);
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			++it1;
		}
		else
		{
			++it2;
		}
	}

	return result;
}

template<typename T>
set<T> operator-(const set<T>& set1, const set<T>& set2)
{
	if (set1.empty())
	{
		return {};
	}

	if (set2.empty())
	{
		return set1;
	}
	set<T> result;
	auto it1 = set1.cbegin(), it2 = set2.cbegin();
	while(it1 != set1.cend() && it2 != set2.cend())
	{
		if (*it1 == *it2)
		{
			++it1;
			++it2;
		}
		else if (*it1 < *it2)
		{
			result.push_back(*it1);
			++it1;
		}
		else
		{
			++it2;
		}
	}

	for(; it1 != set1.cend(); ++it1)
	{
		result.push_back(*it1);
	}

	return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const set<T>& s)
{
	for(auto num : s)
	{
		os << num << " ";
	}

	return os;
}

int main(int argc, char const *argv[])
{
	set<int> ls1;
	ls1 = {1,2,5};

	insertIntoSet(ls1, 0);
	std::cout<<ls1<<std::endl;

	set<int> ls2 = {1,5,7};
	std::cout<<ls2<<std::endl;

	set<int> un = ls1 + ls2;
	std::cout<<un<<std::endl;

	set<int> intersection = ls1 * ls2;
	std::cout<<intersection<<std::endl;

	set<int> difference = ls1 - ls2;
	std::cout<<difference<<std::endl;

	return 0;
}