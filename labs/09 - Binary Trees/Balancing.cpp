#include <iostream>
#include <sstream>
#include <math.h>
#include <assert.h>
#include <vector>

#include "SimpleBinaryTree.h"
#include "BinaryTrees.cpp"
#include "Traversals.cpp"

bool balanced(node const* tree)
{
	return !tree || (abs(height(tree->left) - height(tree->right)) <= 1 && balanced(tree->left) && balanced(tree->right));
}

node* rotateRight(node *t)
{
	assert(t->left);
	node *L = t->left;
	node *LR = L->right;

	L->right = t;
	t->left = LR;

	return L;
}

node* rotateLeft(node *t)
{
	assert(t->right);
	node *R = t->right;
	node *RL = R->left;

	R->left = t;
	t->right = RL;

	return R;
}

node* fromSortedVector(const std::vector<int>& arr, int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (start + end) / 2;

    node *root = new node(arr[mid]);
    root->left = fromSortedVector(arr, start, mid - 1);
    root->right = fromSortedVector(arr, mid + 1, end);

    return root;
}

int main(int argc, char const *argv[])
{
	node* t = new node(5, new node(2, new node(1), new node(3, nullptr, new node(4))), new node(6));
	layers(t);
	std::cout<<std::endl;
	std::cout<<"Height: "<<height(t)<<std::endl;
	std::cout<<"Balanced: "<<std::boolalpha<<balanced(t)<<std::endl<<std::endl;

	t->left = rotateLeft(t->left);
	t = rotateRight(t);
	layers(t);
	std::cout<<std::endl;
	std::cout<<"Height: "<<height(t)<<std::endl;
	std::cout<<"Balanced: "<<std::boolalpha<<balanced(t)<<std::endl;
	deleteTree(t);

	std::vector<int> nums = {1,2,3,4,5,6};
	node *v = fromSortedVector(nums, 0, nums.size() - 1);
	layers(v);
	deleteTree(v);
	return 0;
}
