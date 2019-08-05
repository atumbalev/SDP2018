#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>

template<typename K, typename V>
class BST
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

        int getHeight(Node const* r) const
        {
            return !r ? -1 : r->height;
        }

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

        void fix()
        {
            Node *p = this;
            while(p)
            {
                p->height = 1 + std::max(getHeight(p->left), getHeight(p->right));
                p = p->parent;
            }
        }
    };

    Node *root;
    size_t m_size;

    void copyTree(const BST& other)
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
        old->fix();
        delete old;
    }

public:
    class BSTInorderIterator
    {
    private:
        Node const*ptr;
    public:
        BSTInorderIterator(Node* _ptr): ptr(_ptr) {}

        BSTInorderIterator& operator++()
        {
            ptr = ptr->successor();
            return *this;
        }

        BSTInorderIterator operator++(int)
        {
            BSTInorderIterator old = *this;
            ++(*this);
            return old;
        }

        BSTInorderIterator& operator--()
        {
            ptr = ptr->predecessor();
            return *this;
        }

        BSTInorderIterator operator--(int)
        {
            BSTInorderIterator old = *this;
            --(*this);
            return old;
        }

        operator bool() const
        {
            return ptr;
        }

        bool operator==(const BSTInorderIterator& other) const
        {
            return ptr == other.ptr;
        }

        bool operator!=(const BSTInorderIterator& other) const
        {
            return !(ptr == other.ptr);
        }

        std::pair<K,V> operator*()
        {
            return std::make_pair(ptr->key, ptr->value);
        }
    };

    BST()
    {
        root = nullptr;
        m_size = 0;
    }

    ~BST()
    {
        del(root);
    }

    BST(const BST& other)
    {
        copyTree(other);
    }

    BST& operator=(const BST& other)
    {
        if (this!=&other)
        {
            del(root);
            copyTree(other);
        }

        return *this;
    }

    BSTInorderIterator begin() const
    {
        return BSTInorderIterator(root->min());
    }

    BSTInorderIterator end() const
    {
        return BSTInorderIterator(nullptr);
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
            
            if (!replacement->left)
            {
                replace(replacement, replacement->right);
            }
            else
            {
                replace(replacement, replacement->left);
            }
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
            m_size++;
            Node *p = candidate->left;
            p->fix();
            return;
        }

        candidate->right = new Node(_key, _value, 0, candidate);
        m_size++;
        Node *p = candidate->right;
        p->fix();
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
    BST<int, int> bst;
    bst.insert(5,5);
    bst.insert(3,3);
    bst.insert(8,8);
    bst.insert(2,2);
    bst.insert(4,4);
    bst.insert(6,6);
    bst.insert(9,9);
    bst.insert(1,1);
    bst.insert(7,7);

    bst.remove(5); 
 

    auto mst = bst;

    mst.testLayers();

    for (auto p : mst)
    {
        std::cout<<p.first<<";"<<p.second<<" ";
    }
    std::cout<<std::endl;

    for(int i = 0 ; i < 10 ; i++)
    {
        if (mst.contains(i)) std::cout<<i<<": "<<mst.get(i)<<std::endl;
        else std::cout<<"No "<<i<<std::endl;
    }
    
    std::cout<<mst.min()<<" "<<mst.max()<<std::endl;
  
    std::vector<int> range = mst.range(5, 10);
    for(auto item : range) std::cout<<item<<" ";
    std::cout<<std::endl;

    std::cout<<"OK"<<std::endl;
    return 0;
}
