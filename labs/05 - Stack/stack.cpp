#include<assert.h>
#include <iostream>

template<typename T>
class stack
{
private:
	unsigned size, capacity;
	T *arr;
	void copy(const stack& other)
	{
		size = other.size;
		capacity = other.capacity;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = other.arr[i];
		}
	}

	void del()
	{
		delete [] arr;
	}

	void extend()
	{
		T* temp = arr;
		capacity*=2;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}
		delete [] temp;
	}

	void downsize()
	{
		T* temp = arr;
		capacity/=2;
		arr = new T[capacity];
		for(int i = 0 ; i < size; ++i)
		{
			arr[i] = temp[i];
		}

		delete [] temp;
	}
public:
	stack(unsigned _capacity = 4): capacity(_capacity), size(0)
	{
		assert(capacity > 0);
		arr = new T[capacity];
	}

	stack(const stack& other)
	{
		copy(other);
	}

	stack& operator=(const stack& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}

		return *this;
	}

	~stack()
	{
		del();
	}

	void push(const T& element)
	{
		if (size == capacity)
		{
			extend();
		}

		arr[size++] = element;
	}

	T top() const
	{
		assert(size);
		return arr[size-1];
	}

	void pop()
	{
		assert(size);
		if (size < capacity / 4)
		{
			downsize();
		}
		size--;
	}

	bool empty()
	{
		return !size;
	}
};

int main(int argc, char const *argv[])
{
	stack<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);

	stack<int> c = a;
	stack<int> b;
	b = c;

	while(!b.empty())
	{
		std::cout<<b.top();
		b.pop();
	}
	return 0;
}
