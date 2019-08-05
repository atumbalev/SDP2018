#include <iostream>
#include <vector>
#include <assert.h>

template<typename T>
class BinaryHeap
{
private:
	std::vector<T> container; // no need to write our own vector again ...
	size_t parent(size_t index) const
	{
		return (index - 1) / 2;
	}

	size_t leftChild(size_t index) const
	{
		return index * 2 + 1;
	}

	size_t rightChild(size_t index) const
	{
		return index * 2 + 2;
	}

	void shiftUp(size_t i)
	{
		size_t p = parent(i);
		while(i > 0 && container[p] > container[i])
		{
			std::swap(container[p], container[i]);
			i = p;
			p = parent(i);
		}
	}

	void shiftDown(size_t i)
	{
		while(true)
        {
            size_t smallest = i;
            size_t l = leftChild(i);
            size_t r = rightChild(i);
            if (l < container.size() && container[smallest] > container[l])
        	{
            	smallest = l;
            }
            if (r < container.size() && container[smallest] > container[r])
            {
            	smallest = r;
            }
            if (smallest == i)
        	{
        		break;
        	}
            else
            {
                std::swap(container[i], container[smallest]);
                i = smallest;
            }
        }
	}

public:
	T top() const
	{
		assert(!container.empty());
		return container[0];
	}

	bool empty() const
	{
		return container.empty();
	}

	size_t size() const
	{
		return container.size();
	}

	void push(const T& elem)
	{
		container.push_back(elem);
		shiftUp(container.size() - 1);
	}

	void pop()
	{
		assert(!container.empty());
		std::swap(container[0], container[size()-1]);
		container.pop_back();
		shiftDown(0);
	}
};

int main(int argc, char const *argv[])
{
	BinaryHeap<int> bh;
	bh.push(1);
	bh.push(0);
	bh.push(5);

	while(!bh.empty())
	{
		std::cout<<bh.top()<<" ";
		bh.pop();
	}

	return 0;
}
