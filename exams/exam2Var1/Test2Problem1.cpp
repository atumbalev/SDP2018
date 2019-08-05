#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

struct node
{
	int data;
	node *left, *right;

	node(int _data, node *_left = nullptr, node* _right = nullptr):
		data(_data),
		left(_left),
		right(_right)
		{}

	~node()
	{
		delete left;
		delete right;
	}
};
// (5 ((9 ()) (1 ((4 ()) (42 ())))))
node* read(std::istream& in)
{
	char c;
	int num;
	node *l, *r;
	//    (    root      (     ) or (
	in >> c >> num >> c >> c;
	if (c == '(') // has 2 children
	{
		in.putback(c);
		l = read(in);
		r = read(in);
	}
	else // has no children
	{
		l = r = nullptr;
	}
	in >> c;
	return new node(num, l, r); 
}

node* readFromFile(const std::string& fName)
{
	std::ifstream in(fName);
	assert(in);
	node *tr = read(in);
	in.close();
	return tr;
}

int maxSum(node *r) // trees have either 2 or no children
{
	if (!r->left)
	{
		return r->data;
	}

	return r->data + std::max(maxSum(r->left), maxSum(r->right));
}

int main(int argc, char const *argv[])
{
	node *r = readFromFile("tree");
	std::cout<<maxSum(r)<<std::endl;
	delete r;
	return 0;
}