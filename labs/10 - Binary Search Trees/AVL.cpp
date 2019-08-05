#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>

template<typename K, typename V>
class AVL
{
private:
    struct Node
    {
        K key;
        V value;
        int height;
        Node *parent, *left, *right;

        Node(const K& _key, const V& _value, int _height = 0, Node *_parent = nullptr):
            key(_key),
            value(_value),
            height(_height),
            parent(_parent),
            left(nullptr),
            right(nullptr)
            {}

        bool isLeftChild() const
        {
           return parent && parent->left == this;
        }

        bool isRightChild() const
        {
           return parent && parent->right == this;
        }

        Node* successor() const
        {
            if (right)
            {
                return right->min();
            }

            Node const*curr = this;
            
            while(curr->isRightChild())
            {
                curr = curr->parent;
            }

            return curr->parent;
        }

        Node* predecessor() const
        {
            if (left)
            {
                return left->max();
            }

            Node const*curr = this;
            while(curr->isLeftChild())
            {
                curr = curr->parent;
            }

            return curr->parent;
        }

        Node* min()
        {
            Node* curr = this;
            while(curr->left)
            {
               curr = curr->left;
            }

            return curr;
        }

        Node* max()
        {
            Node* curr = this;
            while(curr->right)
            {
               curr = curr->right;
            }

            return curr;
        }

        int getBalance() const
        {
            return getHeight(left) - getHeight(right);
        }
    };

    Node *root;
    size_t m_size;

    void copyTree(const AVL& other)
    {
        m_size = other.m_size;
        copy(root, other.root);
    }

    void copy(Node*& node, Node *other, Node* parent = nullptr)
    {
        if (other)
        {
            node = new Node(other->key, other->value, other->height, parent);
            copy(node->left, other->left, node);
            copy(node->right, other->right, node);
        }
        else
        {
            node = nullptr;
        }
    }

    void del(Node*& node)
    {
        if (node)
        {
            del(node->left);
            del(node->right);
            delete node;
            node = nullptr;
        }
    }

    Node* findNode(const K& _key) const
    {
        Node* curr = root;
        while (curr && curr->key != _key)
        {
            if (_key < curr->key)
            {
                if (!curr->left)
                {
                   return curr;
                }
                curr = curr->left;
            }
            else
            {
                if (!curr->right)
                {
                   return curr;
                }
                curr = curr->right;
            }
        }

        return curr;
    }
    
    void replace(Node *old, Node *New)
    {
        if (old == root)
        {
            root = New;
        }
        else if (old == old->parent->left)
        {
            old->parent->left = New;
        }
        else
        {
            old->parent->right = New;
        }
        if (New)
        {
            New->parent = old->parent;
        }
        
        m_size--;
        fix(old);
        delete old;
    }

    void rotateLeft(Node *n)
    {
        Node *r = n->right;
        
        r->parent = n->parent;
        if (n->parent)
        {
            if (n->isLeftChild())
            {
                n->parent->left = r;
            }
            else
            {
                n->parent->right = r;
            }
        }
        else
        {
            root = r;
        }

        n->right = r->left;
        if (r->left)
        {
            r->left->parent = n;
        }

        r->left = n;
        n->parent = r;

        fixHeight(n);
        fixHeight(r);
    }

    void rotateRight(Node *n)
    {
        Node *l = n->left;
        
        l->parent = n->parent;
        if (n->parent)
        {
            if (n->isLeftChild())
            {
                n->parent->left = l;
            }
            else
            {
                n->parent->right = l;
            }
        }
        else
        {
            root = l;
        }

        n->left = l->right;
        if (l->right)
        {
            l->right->parent = n;
        }

        l->right = n;
        n->parent = l;

        fixHeight(n);
        fixHeight(l);
    }

    int getHeight(Node const* r) const
    {
        return !r ? -1 : r->height;
    }

    void fix(Node *n)
    {
        while(n)
        {
            fixOnce(n);
            n = n->parent;
        }
    }

    void fixHeight(Node *n)
    {
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    }

    void fixOnce(Node *n)
    {
        fixHeight(n);
        int balance = getHeight(n->left) - getHeight(n->right);

        if (balance == 2)
        {
            if (getHeight(n->left->left) < getHeight(n->left->right))
            {
                rotateLeft(n->left);
            }

            rotateRight(n);
        }

        if (balance == -2)
        {
            if (getHeight(n->right->right) < getHeight(n->right->left))
            {
                rotateRight(n->right);
            }
            
            rotateLeft(n);
        }
    }

public:
    class AVLInorderIterator
    {
    private:
        Node const*ptr;
    public:
        AVLInorderIterator(Node* _ptr): ptr(_ptr) {}

        AVLInorderIterator& operator++()
        {
            ptr = ptr->successor();
            return *this;
        }

        AVLInorderIterator operator++(int)
        {
            AVLInorderIterator old = *this;
            ++(*this);
            return old;
        }

        AVLInorderIterator& operator--()
        {
            ptr = ptr->predecessor();
            return *this;
        }

        AVLInorderIterator operator--(int)
        {
            AVLInorderIterator old = *this;
            --(*this);
            return old;
        }

        operator bool() const
        {
            return ptr;
        }

        bool operator==(const AVLInorderIterator& other) const
        {
            return ptr == other.ptr;
        }

        bool operator!=(const AVLInorderIterator& other) const
        {
            return !(ptr == other.ptr);
        }

        std::pair<K,V> operator*()
        {
            return std::make_pair(ptr->key, ptr->value);
        }
    };

    AVL()
    {
        root = nullptr;
        m_size = 0;
    }

    ~AVL()
    {
        del(root);
    }

    AVL(const AVL& other)
    {
        copyTree(other);
    }

    AVL& operator=(const AVL& other)
    {
        if (this!=&other)
        {
            del(root);
            copyTree(other);
        }

        return *this;
    }

    AVLInorderIterator begin() const
    {
        return AVLInorderIterator(root->min());
    }

    AVLInorderIterator end() const
    {
        return AVLInorderIterator(nullptr);
    }

    size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return !root;
    }

    bool contains(const K& _key) const
    {
        Node *candidate = findNode(_key);
        if (!candidate)
        {
           return false;
        }
        return candidate->key == _key;
    }

    V get(const K& _key) const
    {
        assert(!empty());
        Node *candidate = findNode(_key);
        assert(candidate->key == _key);

        return candidate->value;
    }

    void clear()
    {
        del(root);
        m_size = 0;
    }

    void remove(const K& _key)
    {
        assert(!empty());
        Node* candidate = findNode(_key);
        assert(candidate->key == _key);
        
        if (!candidate->left)
        {
            replace(candidate, candidate->right);
        }
        else if (!candidate->right)
        {
            replace(candidate, candidate->left);
        }
        else
        {
            Node *replacement = candidate->successor();
            candidate->value = replacement->value;
            candidate->key = replacement->key;
            
            replace(replacement, replacement->right);
        }
     }

    void insert(const K& _key, const V& _value)
    {
        if (empty())
        {
            root = new Node(_key, _value);
            m_size++;
            return;
        }

        Node* candidate = findNode(_key);

        if (_key == candidate->key)
        {
            candidate->value = _value;
            return;
        }

        if (_key < candidate->key)
        {
            candidate->left = new Node(_key, _value, 0, candidate);
        }
        else
        {
            candidate->right = new Node(_key, _value, 0, candidate);
        }
        m_size++;
        fix(candidate);
    }

    V max() const
    {
        assert(!empty());
        return root->max()->value;
    }

    V min() const
    {
        assert(!empty());
        return root->min()->value;
    }

    std::vector<V> range(const K& start, const K& end) const
    {
        assert(start <= end);
        std::vector<V> numbers;
        Node* candidateStart = findNode(start);
        Node* candidateEnd = findNode(end);

        if (start > candidateStart->key)
        {
            candidateStart = candidateStart->successor();
        }

        if (end < candidateEnd->key)
        {
            candidateEnd = candidateEnd->predecessor();
        }

        while(candidateStart)
        {
            numbers.push_back(candidateStart->value);
            if (candidateStart == candidateEnd)
            {
                return numbers;
            }
            candidateStart = candidateStart->successor();
        }

        return numbers;
    }

    void testLayers() const // TEST
    {
        std::queue<Node*> q;
        if (!root) return;
        q.push(root);
        q.push(nullptr);
        while (!q.empty())
        {
            Node const* tmp = q.front();
            q.pop();
            if (!tmp)
            {
                std::cout<<std::endl;
                if (!q.empty()) q.push(nullptr);
            }
            else
            {
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
                std::cout<<tmp->value<<";"<<tmp->height<<" ";
            }
        }

        std::cout<<std::endl;
    }
};

int main()
{
    AVL<int, int> bst;
    
    for(int i = 1; i < 10; i++)
    {
        bst.insert(i,i);
        bst.testLayers();
        std::cin.get();
    }

    for (int i = 1 ; i < 10 ; i++)
    {
        bst.remove(i);
        bst.testLayers();
        std::cin.get();
    }
    
    return 0;
}
