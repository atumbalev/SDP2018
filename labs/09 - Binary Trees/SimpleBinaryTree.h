#ifndef SimpleBinaryTree
#define SimpleBinaryTree

struct node
{
    int data;
    node* left, *right;
    node(int _data, node *_left = nullptr, node *_right = nullptr): data(_data), left(_left), right(_right) {}
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

node* copyTree(node const* tree)
{
	if (!tree)
	{
		return nullptr;
	}

	return new node(tree->data, copyTree(tree->left), copyTree(tree->right));
}

#endif
