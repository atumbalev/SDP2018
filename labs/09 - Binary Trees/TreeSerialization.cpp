#include <iostream>
#include <stack>
#include <queue>
#include <fstream>

#include "SimpleBinaryTree.h"

void print(node const* root, std::ostream& out = std::cout)
{
	if (!root)
	{
		out << "()";
		return;
	}

	out << "(" << root->data;
	print(root->left, out);
	print(root->right, out);
	out << ")";
}

node* read(std::istream& in)
{
	in.get(); // (
	if (in.peek() == ')')
	{
		in.get(); // )
		return nullptr;
	}
	int data;
	in >> data;
	node* left = read(in);
	node* right = read(in);
	in.get();  // )
	return new node(data, left, right);
}

/*int main(int argc, char const *argv[])
{
	node* a = new node(1, new node(2, new node(4, new node(8), new node(9)), new node(5, new node(10))), new node(3, new node(6), new node(7)));
    std::ofstream file("tree");
    print(a, file);
    file.close();

    std::ifstream input("tree");
    node* newTree = read(input);
    print(newTree);
    input.close();

    node* newerTree = copyTree(newTree);
    std::cout<<std::endl;
    print(newerTree);

    deleteTree(a);
    deleteTree(newerTree);
    deleteTree(newTree);
	return 0;
}*/
