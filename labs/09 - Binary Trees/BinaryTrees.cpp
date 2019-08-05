#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

#include "SimpleBinaryTree.h"
#include "Traversals.cpp"

int height(node* n)
{
    if (!n)
    {
        return 0;
    }
    
    return 1 + std::max(height(n->left), height(n->right)); 
}

bool contains(node* n, int a)
{
    if (!n)
    {
        return false;
    }
    
    if (n->data == a)
    {
        return true;
    }
    
    return contains(n->left, a) || contains(n->right, a);
}

void map(node *root, int(*unaryFunction)(int))
{
    if (!root) return;
    root->data = unaryFunction(root->data);
    map(root->left, unaryFunction);
    map(root->right, unaryFunction);
}

void filter(node*& root, bool(*pred)(int))
{
    if (!root) return;
    if (pred(root->data))
    {
        filter(root->left, pred);
        filter(root->right, pred);
    }
    else 
    {
        deleteTree(root);
    }
}

bool same(node const* lhs, node const* rhs)
{
    if (!lhs && !rhs)
    {
        return true;
    }

    if (lhs->data == rhs->data)
    {
        return same(lhs->left, rhs->left) && same(lhs->right, rhs->right);
    }

    return false;
}

int apply(node const* root, int(*binOP)(int, int), int base = 0)
{
    if (!root)
    {
        return base;
    }

    return binOP(
        binOP(root->data,
            apply(root->left, binOP, base)),
        apply(root->right, binOP, base));
}

bool all(node const* root, bool(*pred)(int))
{
    if (!root)
    {
        return true;
    }

    return pred(root->data) &&
    all(root->left, pred) &&
    all(root->right, pred);
}

void orderedHelper(node const* root, std::vector<int>& v);

bool ordered(node const* root)
{
    std::vector<int> res;
    orderedHelper(root, res);
    return std::is_sorted(res.begin(), res.end()); // na kontrolno si go proverqvame nie
}

void orderedHelper(node const* root, std::vector<int>& v)
{
    if (!root) return;

    orderedHelper(root->left, v);
    v.push_back(root->data);
    orderedHelper(root->right, v);
}

void mirror(node* n)
{
    if (!n)
    {
        return;
    }
   
    mirror(n->left);
    mirror(n->right);
    std::swap(n->left, n->right);
}

/*int main()
{
    node* a = new node(1, new node(2, new node(4, new node(8), new node(9)), new node(5, new node(10))), new node(3, new node(6), new node(7)));

    std::cout<<"\nHeight: "<<height(a)<<std::endl;
    
    std::cout<<std::boolalpha<<contains(a, 1)<<" "<<contains(a, 5)<<" "<<contains(a, 7)<<" "<<contains(a, 15)<<std::endl;
    
    map(a, [](int x){ return x*2;});
    std::cout<<"\nLayered:\n";
    layers(a);
    
    std::cout<<"Sum: "<<apply(a, [](int x, int y){return x + y;})<<std::endl;
    
    mirror(a);
    std::cout<<"\nLayered:\n";
    layers(a);

    deleteTree(a);
}*/
