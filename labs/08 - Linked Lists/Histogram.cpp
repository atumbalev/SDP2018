// Задача 1. Да се напишат следните функции, работещи с линеен едносвързан списък. Ако се използва реализация, различна от използваната на лекции или упражнения, тя трябва да се опише.
// а) int count (T& a, списък<T>), която намира броя на срещанията на елемент в списък
// б) void remove (T& a, списък<T>), която премахва всички срещания на елемент от списък
// в) hist (списък), която по даден списък отпечатва на екрана двойки с честотата на срещанията на всеки негов елемент
// Пример: hist [1, 2, 3, 1, 5, 3] ~> 1, 2 \ 2, 1 \ 3, 2 \ 5,1

#include <iostream>
#include <list>

template<typename T>
int count(const T& elem, const std::list<T>& ls)
{
	size_t counter = 0;
	for (const T& el : ls)
	{
		if (el == elem)
		{
			++counter;
		}

	}
	return counter;
}

template<typename T>
void remove(const T& elem, std::list<T>& ls)
{
	// ls.remove(elem);
	auto it = ls.begin();
	while(it != ls.end())
	{
		if (*it == elem)
		{
			it = ls.erase(it);
		}
		else
		{
			++it;
		}
	}
}

template<typename T>
void print(const std::list<T>& ls)
{
	for(const T& elem : ls)
	{
		std::cout<<elem<<" ";
	}
	std::cout<<std::endl;
}

template<typename T>
void histogram(const std::list<T>& ls)
{
	if (ls.empty())
	{
		return;
	}
	std::list<T> copy = ls;
	copy.sort();
	auto it = copy.begin();
	T last = *it;
	size_t counter = 1;
	++it;
	for(it; it != copy.end(); ++it)
	{
		if (*it == last)
		{
			counter++;
		}
		else
		{
			std::cout<<last<<" : "<<counter<<std::endl;
			counter = 1;
			last = *it;
		}
	}

	std::cout<<last<<" : "<<counter<<std::endl;
}

int main(int argc, char const *argv[])
{
	std::list<int> ls = {1,3,2,2,3,4,4,4,4,3,5,5,5,5,5,3};
	std::cout<<count(3, ls)<<std::endl;
	remove(3, ls);
	print(ls);
	histogram(ls);
	return 0;
}
