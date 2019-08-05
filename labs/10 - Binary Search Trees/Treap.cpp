#include <iostream>
#include <random>
#include <queue>



template<typename T>
class Treap
{
private:
    
    struct Node
    {
        T data;
        double priority;
        Node *parent, *left, *right;

        Node(const T& _data, double _priority, Node *_parent = nullptr):
        data(_data),
        priority(_priority),
        parent(_parent),
        left(nullptr),
        right(nullptr)
        {}
    } *root;

    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

    void del(Node *& n)
    {
        if (n)
        {
            del(n->left);
            del(n->right);
            delete n;
            n = nullptr;
        }
    }

    void copyTreap(const Treap& other)
    {
        root = copy(other.root);
        gen = std::mt19937(std::random_device()());
        dis = std::uniform_real_distribution<>(0,1);        
    }

    Node* copy(Node const* other, Node* parent = nullptr) const
    {
        if (other)
        {
            Node *newRoot = new Node(other->data, other->priority, parent);
            newRoot->left = copy(other->left, newRoot);
            newRoot->right = copy(other->right, newRoot);
            return newRoot;
        }

        return nullptr;
    }

    void rotateLeft(Node *p)
    {
        Node *rc = p->right;

        rc->parent = p->parent;
        
        // MOVE rc up
        if (p->parent)
        {
            if (p->parent->left == p)
            {
                p->parent->left = rc;
            }
            else
            {
                p->parent->right = rc;
            }
        }
        else
        {
            root = rc;
        }

        // Move rc's left under p
        p->right = rc->left;
        if (rc->left)
        {
            rc->left->parent = p;
        }

        // Move p under rc
        rc->left = p;
        p->parent = rc;
    }

    void rotateRight(Node *p)
    {
        Node *lc = p->left;

        lc->parent = p->parent;
        
        // MOVE lc up
        if (p->parent)
        {
            if (p->parent->left == p)
            {
                p->parent->left = lc;
            }
            else
            {
                p->parent->right = lc;
            }
        }
        else
        {
            root = lc;
        }

        // Move lc's left under p
        p->left = lc->right;
        if (lc->right)
        {
            lc->right->parent = p;
        }

        // Move p under lc
        lc->right = p;
        p->parent = lc;
    }

    void fixUp(Node *n)
    {
        while(n->parent && n->priority > n->parent->priority)
        {
            if (n->parent->left == n)
            {
                rotateRight(n->parent);
            }
            else
            {
                rotateLeft(n->parent);
            }
        }
    }

    void fixDown(Node *n)
    {
        Node *maxNode = nullptr;
        while(n != maxNode)
        {
            double maxPriority = n->priority;
            maxNode = n;
            if (n->left && n->left->priority > maxPriority)
            {
                maxNode = n->left;
                maxPriority = n->left->priority;
            }
            if (n->right && n->right->priority > maxPriority)
            {
                maxNode = n->right;
            }

            if (maxNode == n->left)
            {
                rotateRight(n);
            }
            else if (maxNode == n->right)
            {
                rotateLeft(n);
            }
        }
    }

    Node* find(const T& elem)
    {
        if (!root)
        {
            return nullptr;
        }

        Node *curr = root;
        
        while(curr->data != elem)
        {
            if (elem < curr->data)
            {
                if (!curr->left)
                {
                    break;
                }

                curr = curr->left;
            }
            else
            {
                if (!curr->right)
                {
                    break;
                }

                curr = curr->right;
            }
        }

        return curr;
    }

    void contract(Node* old, Node* newN)
    {
        if (!old->parent)
        {
            root = newN;
        }
        else if (old == old->parent->left)
        {
            old->parent->left = newN;
        }
        else
        {
            old->parent->right = newN;
        }

        if (newN)
        {
            newN->parent = old->parent;
        }

        delete old;
    }

public:
    Treap(): root(nullptr)
    {
        gen = std::mt19937(std::random_device()());
        dis = std::uniform_real_distribution<>(0,1);
    }

    Treap(const Treap& other)
    {
        copyTreap(other);
    }
    
    Treap& operator=(const Treap& other)
    {
        if (this != &other)
        {
            del(root);
            copyTreap(other);
        }

        return *this;
    }
    
    ~Treap()
    {
        del(root);
    }

    void insert(const T& elem)
    {
        Node *parent = find(elem);

        if (!parent)
        {
            root = new Node(elem, dis(gen), nullptr);
        }
        else if (elem == parent->data)
        {
            return;
        }
        else if (elem < parent->data)
        {
            parent->left = new Node(elem, dis(gen), parent);
            fixUp(parent->left);
        }
        else
        {
            parent->right = new Node(elem, dis(gen), parent);
            fixUp(parent->right);
        }
    }

    bool contains(const T& elem)
    {
        return find(elem)->data == elem;
    }

    void remove(const T& elem)
    {
        Node *toDel = find(elem);

        if (elem != toDel->data)
        {
            return;
        }
        else if (!toDel->left) // 1 or 0
        {
            contract(toDel, toDel->right);
        }
        else if (!toDel->right) // 1
        {
            contract(toDel, toDel->left);
        }
        else // 2 children
        {
            Node *replacement = toDel->right;
            while(replacement->left)
            {
                replacement = replacement->left;
            }

            toDel->data = replacement->data;
            toDel->priority = replacement->priority;
            contract(replacement, replacement->right);
            fixDown(toDel);
        }
    }

    void test() const
    {
        if (root)
        {
            std::queue<Node const*> q;
            q.push(root);
            q.push(nullptr);

            while(!q.empty())
            {
                if(q.front())
                {
                    std::cout<<"("<<q.front()->priority<<";"<<q.front()->data<<") ";
                    if (q.front()->left)
                    {
                        q.push(q.front()->left);
                    }
                    if (q.front()->right)
                    {
                        q.push(q.front()->right);
                    }
                    q.pop();
                }
                else
                {
                    std::cout<<std::endl;
                    q.pop();
                    if (!q.empty())
                    {
                        q.push(nullptr);
                    }
                }
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Treap<int> t;
    t.insert(8);
    t.insert(7);
    t.insert(6);
    t.insert(5);
    t.insert(4);
    t.insert(3);
    t.insert(2);
    t.insert(1);

    t.test();
    
    for(int i = 0 ; i < 10; i++)
    {
        std::cout<<"The treap does"<<(t.contains(i) ? "" : " not")<<" contain the element "<<i<<std::endl; 
    }

    return 0;
}
