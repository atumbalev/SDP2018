#include <iostream>
#include <sstream>
#include <assert.h>

struct node
{
	char data;
	node *left, *right;
	node(char _data, node *_left = nullptr, node *_right = nullptr): data(_data), left(_left), right(_right) {}
};

void deleteTree(node*& tree)
{
	if (!tree)
	{
		return;
	}

	deleteTree(tree->left);
	deleteTree(tree->right);
	delete tree;
	tree = nullptr;
}

node* read(std::istream& input) // from prefix
{
	char next;
	next = input.get();
	if (next >= '0' && next <= '9')
	{
		return new node(next);
	}

	node* left = read(input);
	node* right = read(input);

	return new node(next, left, right);
}

double evaluate(node const* expr)
{
	if (expr->data >= '0' && expr->data <= '9')
	{
		return expr->data - '0';
	}

	double left = evaluate(expr->left), right = evaluate(expr->right);
	switch(expr->data)
	{
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': assert(right); return left / right;
		default: throw "Invalid Expression";
	}
}

int main(int argc, char const *argv[])
{
	node *expr = new node('+', new node('1'), new node('*', new node('2'), new node('3')));
	std::cout<<evaluate(expr)<<std::endl;;


	std::istringstream in("+1*43");
	node *readExpr = read(in);
	std::cout<<evaluate(readExpr)<<std::endl;
	deleteTree(expr);
	deleteTree(readExpr);
	return 0;
}
