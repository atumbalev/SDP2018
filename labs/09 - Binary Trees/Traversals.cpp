#ifndef Traversals
#define Traversals

#include <iostream>
#include <stack>
#include <queue>

#include "SimpleBinaryTree.h"

void inorder(node* node)
{
    if (node)
    {
        inorder(node->left);
        std::cout<<node->data<<" ";
        inorder(node->right);
    }
}

void preorder(node* node) // DFS
{
    if (node)
    {
        std::cout<<node->data<<" ";
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(node* node)
{
    if (node)
    {
        postorder(node->right);
        postorder(node->left);
        std::cout<<node->data<<" ";
    }
}

void DFS(node* n)
{
    std::stack<node*> st;
    st.push(n);
    node* top;
    
    while(!st.empty())
    {
        top = st.top();
        st.pop();
        if (top)
        {
           std::cout<<top->data<<" ";
           st.push(top->right);
           st.push(top->left);
        }
    }
}

void BFS(node* n)
{
    std::queue<node*> q;
    q.push(n);
    node* front;
    
    while(!q.empty())
    {
        front = q.front();
        q.pop();
        if (front)
        {
            std::cout<<front->data<<" ";
            q.push(front->left);
            q.push(front->right);
        }
    }
}

void layers(node* n)
{
    if (!n)
    {
        return;
    }
    int layer = 0;
    std::queue<node*> q;
    q.push(n);
    q.push(nullptr);
    node* front;
    std::cout<<"layer "<<layer++<<": ";
    
    
    while(!q.empty())
    {
        front = q.front();
        q.pop();
        if (!front)
        {
            std::cout<<std::endl;
            if (!q.empty())
            {
                q.push(nullptr);
                std::cout<<"layer "<<layer++<<": ";
            }
        }
        else
        {
            std::cout<<front->data<<" ";
            if (front->left)
            {
                q.push(front->left);
            }
            if (front->right)
            {
                q.push(front->right);
            }
        }
    }
}

/*int main()
{
    node* a = new node(1, new node(2, new node(4, new node(8), new node(9)), new node(5, new node(10))), new node(3, new node(6), new node(7)));
    
    std::cout<<"INORDER: ";
    inorder(a);
    std::cout<<"\nPREORDER: ";
    preorder(a);
    std::cout<<"\nPOSTORDER: ";
    postorder(a);
    std::cout<<"\nDFS: ";
    DFS(a);
    std::cout<<"\nBFS: ";
    BFS(a);
    std::cout<<"\nLayered:\n";
    layers(a);

    deleteTree(a);
    std::cout<<a<<std::endl;
}*/

#endif
