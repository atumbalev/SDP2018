#include <iostream>
#include <initializer_list>
#include <assert.h>

template<typename T>
class LinkedList
{
private:
	using Comparator = bool(*)(const T&, const T&);
	using UnaryPredicate = bool(*)(const T&);
	using BinaryOperation = T(*)(const T&, const T&);
	using UnaryOperation = T(*)(const T&);

	struct Node
	{
		T m_data;
		Node *m_prev, *m_next;
		Node(const T& data, Node *prev = nullptr, Node* next = nullptr): m_data(data), m_prev(prev), m_next(next) {}
		Node() = default;
	};
	
	Node *m_start, *m_end;
	size_t m_size;

	void del()
	{
		LinkedListIterator it = this->begin();
		while(it != this->end())
		{
			it = this->erase(it);
		}

		delete this->m_end;
	}

	void copy(const LinkedList& other)
	{
		this->m_size = 0;
		this->m_start = this->m_end = new Node();
		for(const T& item : other)
		{
			this->push_back(item);
		}
	}
public:
	struct LinkedListIterator
	{
	private:
		Node* m_ptr;
	public:
        friend class LinkedList;
		LinkedListIterator(Node* ptr): m_ptr(ptr) {}
		LinkedListIterator(): m_ptr(nullptr) {}

		bool operator==(const LinkedListIterator& other) const
		{
			return this->m_ptr == other.m_ptr;
		}

		bool operator!=(const LinkedListIterator& other) const
		{
			return !(*this == other);
		}

		operator bool() const
		{
			return m_ptr;
		}

		LinkedListIterator& operator++()
		{
			return *this = LinkedListIterator(this->m_ptr->m_next);
		}

		LinkedListIterator operator++(int)
		{
			LinkedListIterator oldValue = *this;
			++(*this);
			return oldValue;
		}

		LinkedListIterator& operator--()
		{
			return *this = LinkedListIterator(this->m_ptr->m_prev);
		}

		LinkedListIterator operator--(int)
		{
			LinkedListIterator oldValue = *this;
			--(*this);
			return oldValue;
		}

		T& operator*() const
		{
			return m_ptr->m_data;
		}

	};

	LinkedList(): m_size(0)
	{
		this->m_start = this->m_end = new Node();
	}
	
	LinkedList(const LinkedList& other)
	{
		this->copy(other);
	}
	
	LinkedList(const std::initializer_list<T>& other): m_size(0)
	{
		this->m_start = this->m_end = new Node();
		for(const T& item : other)
		{
			this->push_back(item);
		}
	}

	~LinkedList()
	{
		this->del();
	}

	LinkedList& operator=(const LinkedList& other)
	{
		if (this != &other)
		{
			this->del();
			this->copy(other);
		}

		return *this;
	}

	LinkedListIterator begin() const
	{
		return LinkedListIterator(m_start);
	}

	LinkedListIterator end() const
	{
		return LinkedListIterator(m_end);
	}

	bool empty() const
	{
		return (this->m_start == this->m_end);
	}

	LinkedListIterator insert(const LinkedListIterator& it, const T& elem)
	{
		assert(it);

		if (it == this->begin())
		{
			this->push_front(elem);
			return this->begin();
		}

		if (it == this->end())
		{
			this->push_back(elem);
			return LinkedListIterator(this->end().m_ptr->m_prev);
		}

		Node* newNode = new Node(elem, it.m_ptr->m_prev, it.m_ptr);
		it.m_ptr->m_prev->m_next = newNode;
		it.m_ptr->m_prev = newNode;
		++this->m_size;
		return LinkedListIterator(newNode);
	}
	
	void push_front(const T& elem)
	{
		++this->m_size;
		if (this->empty())
		{
			this->m_start = new Node(elem, nullptr, this->m_end);
			this->m_end->m_prev = this->m_start;
			return;
		}

		Node* newNode = new Node(elem, nullptr, this->m_start);

		this->m_start->m_prev = newNode;
		this->m_start = newNode;
	}

	void push_back(const T& elem)
	{
		if (this->empty())
		{
			this->push_front(elem);
            return;
		}

		++this->m_size;
		Node* newNode = new Node(elem, this->m_end->m_prev, this->m_end);
		this->m_end->m_prev->m_next = newNode;
		this->m_end->m_prev = newNode;
	}

	size_t size() const
	{
		return this->m_size;
	}

	void pop_back()
	{
		assert(!this->empty());
		--this->m_size;
		if (this->m_start->m_next == this->m_end)
		{
			delete this->m_start;
			this->m_start = this->m_end;
			this->m_end->m_prev = nullptr;
			return;
		}

		Node* oldEnd = this->m_end->m_prev;
		oldEnd->m_prev->m_next = this->m_end;
		this->m_end->m_prev = oldEnd->m_prev;
		delete oldEnd;
	}

	void pop_front()
	{
		assert(!this->empty());

		if (this->m_start->m_next == this->m_end)
		{
			this->pop_back();
			return;
		}

		Node* oldStart = this->m_start;
		this->m_start = oldStart->m_next;
		oldStart->m_next->m_prev = nullptr;
		--this->m_size;
		delete oldStart;
	}

	LinkedListIterator erase(LinkedListIterator& it)
	{
		assert(it && it != this->end());

		if (it == this->begin())
		{
			this->pop_front();
			return LinkedListIterator(this->m_start);
		}

		Node* toDel = it.m_ptr;
		Node* next = toDel->m_next;
		toDel->m_prev->m_next = next;
		next->m_prev = toDel->m_prev;
		--this->m_size;
		it.m_ptr = nullptr;
		delete toDel;
		return LinkedListIterator(next);
	}

	void clear()
	{
		LinkedListIterator it = this->begin();

		while(it != this->end())
		{
			it = this->erase(it);
		}
	}

	void merge(LinkedList& other, Comparator cmp = [](const T& lhs, const T& rhs){return lhs < rhs;})
	{
		LinkedListIterator it1 = this->begin();
		LinkedListIterator it2 = other.begin();

		while(it2 != other.end() && it1 != this->end())
		{
			if (cmp(*it1, *it2))
			{
				++it1;
			}
			else
			{
				this->insert(it1, *(it2++));
			}
		}

		while(it2 != other.end())
		{
			this->insert(it1, *(it2++));
		}
		
	}

	void sort(Comparator cmp = [](const T& lhs, const T& rhs){return lhs < rhs;})
	{
		LinkedList half;
		LinkedListIterator slow = this->begin();
		LinkedListIterator fast = this->begin();

		if (this->empty() || this->m_start->m_next == this->m_end)
		{
			return;
		}

		while(fast && fast != this->end())
		{
			++fast;
			++fast;
			half.push_back(*slow);
			slow = this->erase(slow);
		}

		this->sort(cmp);
		half.sort(cmp);

		this->merge(half, cmp);
	}

	void remove_if(UnaryPredicate pred)
	{
		LinkedListIterator it = this->begin();
		while(it != this->end())
		{
			if (pred(*it))
			{
				it = this->erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void remove(const T& element)
	{
		LinkedListIterator it = this->begin();
		while(it != this->end())
		{
			if (*it == element)
			{
				it = this->erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void transform(UnaryOperation op)
	{
		for(T& element : *this)
		{
			element = op(element);
		}
	}

	T accumulate(const T& init, BinaryOperation op) const
	{
		T result = init;
		for(const T& item: *this)
		{
			result = op(result, item);
		}

		return result;
	}

};

int main(int argc, char const *argv[])
{
	LinkedList<int> l = {3,3,4,5,2,6,1,9,7,3,0};
    auto it = l.end();
    it = l.insert(it, 11);
    it = l.insert(it, 2);
    std::cout<<"elements: \n";
    for(auto item: l)
	{
	    std::cout<<item<<std::endl;
	}
	std::cout<<"-------"<<std::endl;
	l.sort();
	std::cout<<"sorted elements: \n";
	for(auto item: l)
	{
	    std::cout<<item<<std::endl;
	}
	std::cout<<"-------"<<std::endl;
	
	l.remove_if([](const int& a){return a % 2 == 0;});
	std::cout<<"odd elements: \n";
	for(auto item: l)
	{
	    std::cout<<item<<std::endl;
	}
	std::cout<<"-------"<<std::endl;
	
	l.remove(3);
	std::cout<<"all 3s removed: \n";
	for(auto item: l)
	{
	    std::cout<<item<<std::endl;
	}
	std::cout<<"-------"<<std::endl;
	
	l.transform([](const int& a){return a * a;});
	std::cout<<"all elements squared: \n";
	for(auto item: l)
	{
	    std::cout<<item<<std::endl;
	}
	std::cout<<"-------"<<std::endl;

	std::cout<<"Product: "<<l.accumulate(1, [](const int& lhs, const int& rhs) {return lhs * rhs;})<<std::endl;
	std::cout<<"size: "<<l.size()<<std::endl;
	return 0;
}
