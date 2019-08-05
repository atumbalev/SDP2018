// 2015

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <list>

struct Node
{
	std::list<int> value;
	Node *left, *right;

	Node(const std::list<int>& val, Node* l = nullptr, Node *r = nullptr):
		value(val),
		left(l),
		right(r)
		{}
};

bool mirror(const std::list<int>& a, std::list<int> b)
{
	b.reverse();
	return a == b;
}

std::list<int> goDown(Node const* r, const std::string& path)
{
	Node const* tmp = r;
	for (auto c : path)
	{
		if (!tmp) throw "error";
		switch(c)
		{
			case 'L': tmp = tmp->left; break;
			case 'R': tmp = tmp->right; break;
			default: throw "Error";
		}
	}

	if (!tmp) throw "error";
	return tmp->value;
}

bool zadacha(Node const* n, const std::string& p1, const std::string& p2)
{
	return mirror(goDown(n, p1), goDown(n, p2));
}

int main(int argc, char const *argv[])
{
	Node * r = new Node({1}, new Node({3}, new Node({4}, nullptr, new Node({1,2,3}))), new Node({5}, new Node({3,2,1})));

	std::cout<<zadacha(r, "LLR", "RL");

	return 0;
}