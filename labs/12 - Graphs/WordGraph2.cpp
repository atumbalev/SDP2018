// See WordGraph.cpp for problem

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
	if (!count)
	{
		return true;
	}

	for (auto e : g[start])
	{
		if (dict[e.first] != "" && canReadWord(g, dict[e.first]))
		{
			return canReadWords(g, dict[e.first].back() - 'a', count - 1, dict);
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
	graph g(26);

	g['h' - 'a'].push_back(std::make_pair('e' - 'a', 1));
	g['e' - 'a'].push_back(std::make_pair('l' - 'a', 1));
	g['l' - 'a'].push_back(std::make_pair('l' - 'a', 1));
	g['l' - 'a'].push_back(std::make_pair('o' - 'a', 1));
	g['o' - 'a'].push_back(std::make_pair('h' - 'a', 1));
	
	std::cout<<std::boolalpha<<canReadSentence("words.txt", g);
	return 0;
}
