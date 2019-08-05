#include <iostream>
#include <forward_list>

template<typename T>
class Set
{
private:
	std::forward_list<T> elements;
public:
	bool member(const T& x) const
	{
		for (const T& element : elements)
		{
			if (element == x)
			{
				return true;
			}
			if (element > x)
			{
				return false;
			}
		}
		return false;	
	}

	void add(const T& elem)
	{
		if (elements.empty())
		{
			elements.push_front(elem);
			return;
		}

		auto prev = elements.before_begin();
		auto next = elements.begin();

		while(next != elements.end())
		{
			if (*next == elem)
			{
				throw "Attempting to add duplicate";
			}

			if (*next > elem)
			{
				elements.insert_after(prev, elem);
				return;
			}

			++prev;
			++next;
		}

		elements.insert_after(prev, elem);
	}

	void print() const
	{
		for(const T& element : elements)
		{
			std::cout<<element<<" ";
		}
	}

	Set unite(const Set& other)
	{
		Set result;
		auto itR = result.elements.before_begin();
		auto it1 = elements.begin();
		auto it2 = other.elements.begin();

		while(it1 != elements.end() && it2 != other.elements.end())
		{
			if (*it1 == *it2)
			{
				itR = result.elements.insert_after(itR, *(it1++));
				++it2;
			}

			else if (*it1 < *it2)
			{
				itR = result.elements.insert_after(itR, *(it1++));
			}

			else
			{
				itR = result.elements.insert_after(itR, *(it2++));
			}

		}
		while(it1 != elements.end())
		{
			itR = result.elements.insert_after(itR, *(it1++));
		}

		while(it2 != other.elements.end())
		{
			itR = result.elements.insert_after(itR, *(it2++));
		}

		return result;
	}

	bool subset(const Set& other)
	{
		auto it1 = elements.begin();
		auto it2 = other.elements.begin();

		while(it1 != elements.end())
		{
			if (it2 == other.elements.end())
			{
				return false;
			}

			if (*it1 == *it2)
			{
				++it1;
				++it2;
			}

			else if (*it1 > *it2)
			{
				++it2;
			}

			else if (*it1 < *it2)
			{
				return false;
			}
		}

		return true;
	}
};

int main(int argc, char const *argv[])
{
	Set<int> s;
	s.add(1); s.add(2); s.add(3);
	s.print();
	std::cout<<std::endl;
	Set<int> ss;
	ss.add(1); ss.add(2); ss.add(5);
	ss.print();
	std::cout<<std::endl;
	auto sss = s.unite(ss);
	sss.print();
	std::cout<<std::endl;
	std::cout<<std::boolalpha<<ss.subset(sss);
	return 0;
}