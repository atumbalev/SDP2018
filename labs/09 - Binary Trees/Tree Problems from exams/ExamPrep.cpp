// 2016
// Both Variants

#include <iostream>

template<typename T>
struct Node
{
	T value;
	Node *left, *right;

	Node(const T& val, Node* l = nullptr, Node *r = nullptr):
		value(val),
		left(l),
		right(r)
		{}
};

using intNode = Node<int>;
using charNode = Node<char>;

template<typename T>
int nodes(Node<T> const* n)
{
	if (!n) return 0;
	return 1 + nodes(n->left) + nodes(n->right); 
}

int sum(intNode const* n)
{
	if (!n) return 0;
	return n->value + sum(n->left) + sum(n->right);
}

int calcNode(intNode const* n1, charNode const* n2)
{
	switch(n2->value)
	{
		case '+': return n1->value + sum(n1);
		case '-': return n1->value - sum(n1);
		case '*': return n1->value * sum(n1);
		default: throw "error";
	}
}

int calculate(intNode const* n1, charNode const* n2)
{
	if (!n1) return 0;
	return calcNode(n1, n2) + calculate(n1->left, n2->left) + calculate(n1->right, n2->right);
}

int main(int argc, char const *argv[])
{
	Node<int> * root1 = new intNode(5, new intNode(4, new intNode(3), new intNode(2)), new intNode(1, nullptr, new intNode(10)));
	Node<char> * root2 = new charNode('*', new charNode('+', new charNode('+'), new charNode('*')), new charNode('-', nullptr, new charNode('-')));
	std::cout<<calculate(root1, root2);
	return 0;
}

