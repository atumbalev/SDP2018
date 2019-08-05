/*Задача 2. 
Да се дефинира шаблон MultiCounter<T>, който реализира “преброител” на елементите от тип T. Шаблонът да позволява да се “добавя” и “премахва” по един брой от даден елемент x на T. Шаблонът да дефинира следните операции:
    • [подходящ тип] operator += (const T& x): увеличава  броя на елемента x;
    • съответен оператор +;
    • [подходящ тип] operator -= (const T& x):  намалява броя на елемента x;
    • съответен оператор -;
    • int numUnique(): Връща колко елемента имат брой, различен от 0;
    • int operator [] (int i): оператор за индексиране, даващ i-тия елемент с брой, различен от 0. Редът на елементите не е от значение;
    • int howMany (const T& x): връща броя на елемента x.

Пример: 
При изпълнение на следния програмен фрагмент: 
MultiCounter<int> c; c += 0; c+= 1; c += 0; 
for (int i = 0; i < c.numUnique (); i++) 
cout << c[i] << “:” << c.howMany (c[i]) << “;” ;
изходът на конзолата е 0:2; 1:1

При нужда от такива, шаблонът трябва да съдържа всички необходими служебни методи (контруктори, деструктор, оператор за присвояване).
*/

#include <iostream>
#include <list>
#include <assert.h>

template<typename T>
class MultiCounter
{
private:
	std::list<std::pair<T, unsigned>> set;
public:
	void operator+=(const T& elem)
	{
		for(auto it = set.begin(); it != set.end(); ++it)
		{
			if (elem == (*it).first)
			{
				(*it).second++;
				return;
			}

			if (elem < (*it).first)
			{
				set.insert(it, std::make_pair(elem, 1));
				return;
			}
		}
		set.push_back(std::make_pair(elem, 1));
	}

	MultiCounter operator+(const T& elem) const
	{
		MultiCounter result = *this;
		result+=elem;
		return result;
	}

	void operator-=(const T& elem)
	{
		for(auto it = set.begin(); it != set.end(); ++it)
		{
			assert(elem <= (*it).first);
			if (elem == (*it).first)
			{
				if ((*it).second > 1)
				{
					(*it).second--;
				}
				else // counter is only 1
				{
					set.erase(it);
				}

				return;
			}
		}
	}

	MultiCounter operator-(const T& elem) const
	{
		MultiCounter result = *this;
		result-=elem;
		return result;
	}

	int numUnique() const
	{
		return set.size();
	}

	T const& operator[](int index) const
	{
		assert(index < set.size());
		auto it = set.begin();
		for(int i = 0 ; i < index; ++i)
		{
			++it;
		}

		return (*it).first;
	}

	int howMany(const T& elem) const
	{
		for (const std::pair<T, unsigned>& el : set)
		{
			if (el.first == elem)
			{
				return el.second;
			}
		}

	    throw "Element not in set";
	}

	void print() const
	{
		for (const std::pair<T, unsigned>& p : set)
		{
			std::cout<<p.first<<" "<<p.second<<std::endl;
		}
	}
};
int main(int argc, char const *argv[])
{
	MultiCounter<int> c; c += 0; c+= 1; c += 0;
	c.print();
	for (int i = 0; i < c.numUnique (); i++)
		std::cout << c[i] << ":" << c.howMany (c[i]) << ";" ;
	return 0;
}
