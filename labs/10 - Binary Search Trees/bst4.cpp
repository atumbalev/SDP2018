#include <iostream>
#include <assert.h>

template<typename K, typename V>
class bst
{
private:
	struct node
	{
		K key;
		V value;
		int height;
		node *parent, *left, *right;
		node(const K& _key,
			const V& _value,
			int _height = 0,
			node *_parent = nullptr):
		key(_key),
		value(_value),
		height(_height),
		parent(_parent),
		left(nullptr),
		right(nullptr)
		{}

		bool isLeft() const
		{
			return parent && parent->key > key;
		}

		bool isRight() const
		{
			return parent && parent->key < key;
		}

		node *succ()
		{
			node *curr = this;
			if (right)
			{
				curr = curr->right;
				while(curr->left)
				{
					curr = curr->left;
				}
				return curr;
			}

			while(curr->isRight())
			{
				curr = curr->parent;
			}

			return curr->parent;
		}

		node *pred()
		{
			node *curr = this;
			if (left)
			{
				curr = curr->left;
				while(curr->right)
				{
					curr = curr->right;
				}
				return curr;
			}

			while(curr->isLeft())
			{
				curr = curr->parent;
			}

			return curr->parent;
		}

		int getHeight(node const*n) const
		{
			return !n ? -1 : n->height; 
		}

		void fixHeight()
		{
			node *curr = this;
			while(curr)
			{
				curr->height = 1 + std::max(getHeight(curr->left), getHeight(curr->right));
				curr = curr->parent;
			}
		}
	};

	node *root;
	size_t m_size;

	node* findCandidate(const K& _key) const
	{
		if (!root) return nullptr;
		node *curr = root;

		while(curr->key != _key)
		{
			if (curr->key > _key)
			{
				if (!curr->left) return curr;
				curr = curr->left;
			}

			else
			{
				if (!curr->right) return curr;
				curr = curr->right;
			}
		}

		return curr;
	}

	void del(node *& n)
	{
		if (!n) return;

		del(n->left);
		del(n->right);
		delete n;
		n = nullptr;
		m_size--;
	}

	void copyTree(const bst& other)
    {
        m_size = other.m_size;
        copy(root, other.root);
    }

    void copy(node*& r, node *other, node* parent = nullptr)
    {
        if (other)
        {
            r = new node(other->key, other->value, other->height, parent);
            copy(r->left, other->left, r);
            copy(r->right, other->right, r);
        }
    }

	node* _min() const
	{
		if (!root)
		{
			return nullptr;
		}

		node *curr = root;

		while(curr->left)
		{
			curr = curr->left;
		}

		return curr;
	}

	node* _max() const
	{
		if (!root)
		{
			return nullptr;
		}

		node *curr = root;

		while(curr->right)
		{
			curr = curr->right;
		}

		return curr;
	}

public:
	class iterator
	{
	private:
		node *ptr;
	public:
		iterator(node* _ptr): ptr(_ptr) {}
		bool operator==(const iterator& other)
		{
			return (ptr == other.ptr);
		}
		bool operator!=(const iterator& other)
		{
			return !(*this == other);
		}
		std::pair<K,V> operator*() const
		{
			return std::make_pair(ptr->key, ptr->value);
		}
		iterator& operator++()
		{
			ptr = ptr->succ();
			return *this;
		}
		iterator& operator--()
		{
			ptr = ptr->pred();
			return *this;
		}
	};

	bst():
		root(nullptr),
		m_size(0)
		{}
	~bst()
	{
		del(root);
	}
	bst& operator=(const bst& other)
	{
		if (this != &other)
		{
			del(root);
			copyTree(other);
		}

		return *this;
	}
	bst(const bst& other) = delete;

	iterator begin() const
	{
		return iterator(_min());
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	void insert(const K& _key, const V& _value)
	{
		node *candidate = findCandidate(_key);
		
		if (!candidate)
		{
			root = new node(_key, _value);
			m_size++;
			return;
		}

		if (candidate->key == _key)
		{
			candidate->value = _value;
			return;
		}

		else
		{
			if (candidate->key > _key)
			{
				candidate->left = new node(_key, _value, 0, candidate);
			}
			else
			{
				candidate->right = new node(_key, _value, 0, candidate);
			}

			m_size++;
			candidate->fixHeight();
		}
	}

	bool contains(const K& _key) const
	{
		node *candidate = findCandidate(_key);

		if (!candidate || candidate->key != _key)
		{
			return false;
		}

		return true;
	}

	V get(const K& _key)
	{
		node *candidate = findCandidate(_key);
		assert(candidate && candidate->key == _key);

		return candidate->value;
	}

	size_t size() const
	{
		return m_size;
	}

	bool empty() const
	{
		return !root;
	}

	void clear()
	{
		del(root);
	}

	void testR(node * r) const
	{
		if (!r) return;
		testR(r->left);
		std::cout<<r->key<<" "<<r->height<<std::endl;
		testR(r->right);
	}
	void test() const // TODO: delete
	{
		testR(root);
	}
};

int main(int argc, char const *argv[])
{
	bst<int,int> b;
	b.insert(5,5);
	b.insert(3,3);
	b.insert(7,7);
	b.insert(8,8);
	b.insert(1,1);
	b.insert(4,4);
	b.insert(2,2);


	b.test();
	return 0;
}