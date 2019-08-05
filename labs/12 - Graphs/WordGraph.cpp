/*
Дефиниция: Нека е даден непразен текстов файл. На всеки ред на файла има по една дума, съставена от не повече от 30 малки латински букви. Всяка дума от файла започва с различна буква. “Изречение от файла” наричаме всяка последователност от поне 3 думи от файла (не непременно различни помежду си), разделени една от друга със символа интервал и завършваща със символа точка.

Задача 1.  Да се дефинира функция 
bool canReadSentance (char *fname, [подходящ тип]g)
Функцията връща true, ако в графа g със символи по върховете съществува поне един път, който е изречение от файла с име fname.

Пример. За файла с думите
hello
man 
nix 
thr
едно коректно изречение от файла е “hello man hello.”.
*/

// Понеже има проблеми с условието, това е реализацията, в която в графа има " " и "." и трябва да се четат, wordGraph2.cpp е без тях

#include <fstream>
#include <string>

#include "graph.hpp"

auto getDictionary(const std::string& fileName)
{
	std::ifstream in(fileName);
	std::vector<std::string> result(26);
	std::string word;
	while(in>>word)
	{
		result[word[0] - 'a'] = word;
	}

	in.close();

	return result;
}

bool canReadWord(const graph& g, const std::string& word)
{
	int curr = word[0] - 'a';
	for (int i = 1; i < word.size(); i++)
	{
		bool found = false;
		int next = word[i] - 'a';
		for (const auto& e : g[curr])
		{
			if (e.first == next)
			{
				curr = next;
				found = true;
				break;
			}
		}

		if (!found)
		{
			return false;
		}
	}

	return true;
}

bool canReadWords(const graph& g, int start, int count, const std::vector<std::string>& dict)
{
	for (auto e : g[start])
	{
		if (dict[e.first] != "" && canReadWord(g, dict[e.first]))
		{
			// try to read 1 word and then " "
			int last = dict[e.first].back() - 'a';
			bool foundSpace = false;
			for (auto e : g[last])
			{
				if (count == 1 && e.first == 28)
				{
					return true;
				}

				if (e.first == 27)
				{
					foundSpace = true;
				}
			}

			return foundSpace ? canReadWords(g, 27, count - 1, dict) : false;
		}
	}

	return false;
}

bool canReadSentence(const std::string& fileName, const graph& g)
{
	auto dict = getDictionary(fileName);
	for (int i = 0 ; i < g.size(); i++)
	{
		if (canReadWords(g, i, 3, dict))
		{
			return true;
		}
	}

	return false;
}


int main(int argc, char const *argv[])
{
	graph g(28); //0 - 26 alphabet, 27 is " ", 28 is '.'

	g['h' - 'a'].push_back(std::make_pair('e' - 'a', 1));
	g['e' - 'a'].push_back(std::make_pair('l' - 'a', 1));
	g['l' - 'a'].push_back(std::make_pair('l' - 'a', 1));
	g['l' - 'a'].push_back(std::make_pair('o' - 'a', 1));
	g['o' - 'a'].push_back(std::make_pair(27, 1));
	g['o' - 'a'].push_back(std::make_pair(28, 1));
	g[27].push_back(std::make_pair('h' - 'a', 1));

	
	std::cout<<std::boolalpha<<canReadSentence("words.txt", g);
	return 0;
}
