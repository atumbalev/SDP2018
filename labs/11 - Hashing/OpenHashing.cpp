#include <iostream>
#include <vector>
#include <functional> // std::hash

const double MAX_LOAD_FACTOR = 0.75;
const double MIN_LOAD_FACTOR = 0.10;
const size_t PROBE_DISTANCE = 1;

template<typename T, typename Hasher>
class OpenHash
{
private:
	struct Entry
	{
		T value;
		bool empty;
		bool deleted;

		Entry(const T& in_value = T(), bool in_empty = true, bool in_deleted = false):
			value(in_value),
			empty(in_empty),
			deleted(in_deleted)
			{}
	};

	std::vector<Entry> container;
	size_t size;

public:
	OpenHash(size_t in_size = 31):
		container(in_size),
		size(in_size)
		{}

	void insert(const T& elem)
	{
		if (container.size() && (double)size / container.size() > MAX_LOAD_FACTOR)
		{
			resize(2);
		}

		size_t index = hash(elem);

		while(!container[index].deleted && !container[index].empty && container[index].value != elem)
		{
			probe(index);
		}

		if (container[index].value != elem)
		{
			++size;
			container[index] = Entry(elem, false, false);
		}
	}

	void remove(const T& elem)
	{
		if (container.size() && (double)size / container.size() < MIN_LOAD_FACTOR)
		{
			resize(0.5);
		}

		size_t index = hash(elem);

		while(!container[index].empty && container[index].value != elem)
		{
			probe(index);
		}

		if (!container[index].deleted && !container[index].empty)
		{
			--size;
			container[index].deleted = true;
		}
	}

	bool contains(const T& elem) const
	{
		size_t index = hash(elem);

		while(container[index].deleted || !container[index].empty && container[index].value != elem)
		{
			probe(index);
		}

		return !container[index].empty;
	}

	void print() const
	{
		for(const Entry& e : container)
		{
			if (!e.empty)
			{
				std::cout<<(e.deleted ? "#" : e.value);
			}
			std::cout<<std::endl;
		}
	}

private:
	size_t hash(const T& elem) const
	{
		return Hasher{}(elem) % container.size();
	}

	void resize(double factor)
	{
		std::vector<Entry> tmp = container;
		container = std::vector<Entry>(container.size() * factor);
		size = 0;
		for (const Entry& e : tmp)
		{
			if (!e.empty && !e.deleted)
			{
				insert(e.value);
			}
		}
	}

	void probe(size_t& index) const // Linear Probing
	{
		index = (index + PROBE_DISTANCE) % container.size();
	}
};

int main(int argc, char const *argv[])
{
	OpenHash<std::string, std::hash<std::string>> h(7);

	h.insert("Kappa");
	h.insert("KappaPride");
	h.insert("monkaS");
	h.insert("monkaGIGA");
	h.insert("monkaOMEGA");

	h.print();
	std::cout<<std::endl<<std::endl<<std::endl;
	std::cout<<std::boolalpha<<h.contains("monkaOMEGA")<<std::endl;

	h.remove("KappaPride");
	h.remove("monkaOMEGA");
	
	h.print();
	std::cout<<std::boolalpha<<h.contains("monkaOMEGA")<<std::endl;

	return 0;
}
