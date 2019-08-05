#include <iostream>

template<typename T>
class queue
{
private:
	size_t size, capacity;
	int _front, end;
	T* arr;
	void del()
	{
		delete [] arr;
	}
	void copy(const queue& other)
	{
		size = other.size;
		capacity = other.capacity;
		_front = 0;
		end = size - 1;
		arr = new T[capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = other.arr[(other._front + i) % capacity];
		}

	}

	void resize(double factor)
	{
		T* tmp = arr;
		capacity *= factor;
		arr = new T[capacity];

		for (int i = 0; i < size; ++i)
		{
			arr[i] = tmp[(_front + i) % capacity];
		}
		_front = 0;
		end = size-1;
		delete tmp;
	}

	void extend()
	{
		resize(2);
	}

	void downsize()
	{
		resize(0.5);
	}


public:
	queue(size_t _capacity = 4): size(0), capacity(_capacity), _front(0), end(-1)
	{
		arr = new T[capacity];
	}

	queue(const queue& other)
	{
		copy(other);
	}

	queue& operator=(const queue& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}

		return *this;
	}

	~queue()
	{
		del();
	}

	void push(const T& elem)
	{
		if (size == capacity)
		{
			extend();
		}
		end = (end + 1) % capacity;
		arr[end] = elem;
		size++;
	}

	void pop()
	{
		if (empty())
		{
			throw "Empty Queue";
		}

		if (size < capacity / 4)
		{
			downsize();
		}

		_front = (_front + 1) % capacity;
		size--;
	}

	T front() const
	{
		if (empty())
		{
			throw "Empty Queue";
		}
		return arr[_front];
	}

	size_t getSize() const
	{
		return size;
	}

	bool empty() const
	{
		return !size;
	}
};

int main(int argc, char const *argv[])
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	q.pop();
	q.pop();

	q.push(6);
	q.push(7);

	queue<int> q2 = q, q3;
	q3 = q;

	while(!q.empty())
	{
		std::cout<<q.front()<<" "<<q2.front()<<" "<<q3.front()<<std::endl;
		q.pop();
		q2.pop();
		q3.pop();
	}


	return 0;
}