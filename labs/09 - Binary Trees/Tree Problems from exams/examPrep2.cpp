// 2015

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

struct Node
{
	char value;
	Node *left, *right;

	Node(const char& val, Node* l = nullptr, Node *r = nullptr):
		value(val),
		left(l),
		right(r)
		{}
};

std::string level(Node const* n, int lvl)
{
	if (!n) return "";
	std::queue<Node const*> q;
	q.push(n);
	q.push(nullptr);
	std::string str = "";
	int currLvl = 0;
	while(!q.empty())
	{
		if (!q.front())
		{
			q.pop();
			if (currLvl == lvl)
			{
				return str;
			}
			str = "";
			currLvl++;
			if (!q.empty()) q.push(nullptr);
		}
		else
		{
			str+=q.front()->value;
			if (q.front()->left) q.push(q.front()->left);
			if (q.front()->right) q.push(q.front()->right);
			q.pop();
		}
	}

	return "";
}

bool sentanceOnLevel (Node const* t, int k, char *fname)
{
	std::ifstream f(fname);
	std::string word;
	std::vector<std::string> dict(26);

	while (f >> word)
	{
		dict[word[0] - 'a'] = word;
	}

	f.close();

	word = level(t, k);

	if (word == "") return false;
	char letter = word[0];

	if (letter < 'a' || letter > 'z')
	{
		return false;
	}

	return dict[letter - 'a'] == word;
}

int main(int argc, char const *argv[])
{

	Node *r = new Node('a', new Node('b', new Node('c')), new Node('b', new Node('c', new Node('d'), new Node('d')), new Node('c', nullptr, new Node('d'))));

	for(int i = 0 ; i < 5; i++)
	{
		std::cout<<std::boolalpha<<sentanceOnLevel(r, i, "words.txt")<<std::endl;
	}

	return 0;
}