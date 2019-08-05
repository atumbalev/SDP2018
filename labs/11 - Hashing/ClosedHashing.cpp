#include <iostream>
#include <forward_list>
#include <vector>
#include <functional> // std::hash
#include <string>
#include <iterator> // std::advance, std::next

template<typename T, typename Hasher>
class ClosedHash
{
private:
	std::vector<std::forward_list<T>> container;
public:
	ClosedHash(size_t size):
		container(size)
		{}

	void insert(const T& elem)
	{
		insertIntoSortedBucket(elem, hash(elem));
	}

	void remove(const T& elem)
	{
		container[hash(elem)].remove(elem);
	}
	
	bool contains(const T& elem) const
	{
		findInSortedBucket(elem, hash(elem));
	}
	
	void print() const
	{
		for (const std::forward_list<T>& bucket : container)
		{
			for (const T& elem : bucket)
			{
				std::cout<<elem<<" ";
			}
			std::cout<<std::endl;
		}
	}
private:
	size_t hash(const T& elem) const
	{
		return Hasher{}(elem) % container.size();
	}

	void insertIntoSortedBucket(const T& elem, size_t index)
	{
		auto it = container[index].before_begin();
		while(it != container[index].cend() && std::next(it) != container[index].cend() && *std::next(it) <= elem)
		{
			std::cout<<*it<<std::endl;
			std::advance(it, 1);
		}

		if (*it != elem)
		{
			container[index].insert_after(it, elem);
		}
	}

	bool findInSortedBucket(const T& elem, size_t index) const
	{
		for (const T& el : container[index])
		{
			if (el == elem)
			{
				return true;
			}

			if (el > elem)
			{
				return false;
			}
		}

		return false;
	}
};

int main(int argc, char const *argv[])
{
	ClosedHash<std::string, std::hash<std::string>> h(13);

	h.insert("Kappa");
	h.insert("KappaPride");
	h.insert("monkaS");
	h.insert("monkaGIGA");
	h.insert("monkaOMEGA");

	std::cout<<std::boolalpha<<h.contains("Kappa")<<std::endl;
	h.print();

	h.remove("Kappa");
	
	std::cout<<std::boolalpha<<h.contains("Kappa")<<std::endl;
	h.print();

	return 0;
}
