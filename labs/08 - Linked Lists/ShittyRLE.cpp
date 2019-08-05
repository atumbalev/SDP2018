/*Задача 1. Run-length encoding (RLE) е метод за компресия на списъци, в който всяко поредица от еднакви елементи се представя като двойка от елемента и броя на повторенията. Да се напишат функции
    1. списък<списък<T>> compressRLE(списък<T>&), която компресира списък от елементи. Резултатът да се представи във вид на списък от списъци с по два елемента, от които първият да е елеменът, а вторият - броят поредни срещания.
Пример: вход: [‘m’,’i’,’s’,’s’,’i’,’p’,’p’,’i’] => изход: [[‘m’,1],[’i’,1],[’s’,2],’[i’,1],[‘p’,2],[’i’,1]]
    2. списък<T> extractRLE(списък<списък<Т>>&), която декомпресира даден списък, като в резултата всеки елемент се повторя толкова пъти, колкото указва съответното число от двойката в дадения списък от списъци (обратното на горната подточка).*/

// Няма да си играем да пишем хетерогенни списъци за 2 елемента.

#include <list>
#include <iostream>

template<typename T>
std::list<std::pair<T, size_t>> compressRLE(const std::list<T> ls)
{
	std::list<std::pair<T, size_t>> result;

	if (ls.empty())
	{
		return result;
	}

	auto it = ls.begin();
	T last = *it;
	size_t counter = 1;
	++it;
	for(it; it!=ls.end(); ++it)
	{
		if (*it == last)
		{
			counter++;
		}
		else
		{
			result.push_back(std::make_pair(last, counter));
			last = *it;
			counter = 1;
		}
	}
	result.push_back(std::make_pair(last, counter));
}

template<typename T>
std::list<T> extractRLE(const std::list<std::pair<T, size_t>>& ls)
{
	std::list<T> result;
	for (const std::pair<T, size_t>& p : ls)
	{
		for(size_t i = 0; i < p.second; i++)
		{
			result.push_back(p.first);
		}
	}

	return result;
}

int main(int argc, char const *argv[])
{
	std::list<char> word = {'m', 'i', 's', 's', 'i', 's', 's', 'i', 'p', 'p', 'i'};
	std::list<std::pair<char, size_t>> compressed = compressRLE(word);
	for(const std::pair<char, size_t>& p : compressed)
	{
		std::cout<<p.first<<" "<<p.second<<std::endl;
	}

	std::list<char> uncompressed = extractRLE(compressed);
	for (const char& letter : uncompressed)
	{
		std::cout<<letter;
	}
	std::cout<<std::endl;
	return 0;
}
