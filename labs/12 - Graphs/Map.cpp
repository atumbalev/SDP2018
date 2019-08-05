/*
Географската карта на България е представена с неориентиран граф без тегла.
Даден е вектор с n на брой елементи, които описват български градове. За всеки град е известен и
броя на забележителностите, които се намират в непосредствена близост с него.
Връзките между различните градове (или ребрата в графа) са описани в списък, елементите на който
са двойки от вида
(<ID на начален град>, <ID на краен град>).
ID на градовете са цели числа в интервала [0; n-1]. Ребро между градовете А и Б означава, че времето
за изминаване на пътя между градовете е 1 час.
Да се дефинират функции, които:
а) преобразуват текущото представяне на графа до списък от наследници;
б) да се намери списък с градовете, които могат да бъдат достигнати от даден начален град и
които са отдалечени от него най-много на p часа път;
в) да се намерят първите k града записани в списъка, намерен в б), с най-много забележителности
около тях, подредени по брой на забележителностите.
*/

#include <queue>
#include <list>
#include <algorithm>

#include "graph.hpp"

auto create(const std::list<std::pair<int, int>>& edges)
{
	graph g(edges.size());
	for (const auto& e : edges)
	{
		g[e.first].push_back(std::make_pair(e.second, 1));
		g[e.second].push_back(std::make_pair(e.first, 1));
	}

	return g;
}

auto neighbours(const graph& g, int source, int p)
{
	std::vector<int> result;
	std::vector<int> distance(g.size(), -1);
	std::queue<int> q;
	distance[source] = 0;

	q.push(source);

	while(!q.empty())
	{
		int front = q.front();
		q.pop();

		for (auto e : g[front])
		{
			if (distance[e.first] == -1)
			{
				distance[e.first] = distance[front] + 1;
				q.push(e.first);
			}
		}
	}

	for (int i = 0 ; i < g.size(); ++i)
	{
		if (i != source && distance[i] <= p && distance[i] != -1)
		{
			result.push_back(i);
		}
	}

	return result;
}

auto kWithMostAttractions(std::vector<int> list, const std::vector<int>& attractions, size_t k)
{
	// Heapify and make k pops O(n + klogn)
	/* Alternatively
		Sort and get the first k elements O(nlogn)
		Selection Sort that stops after k iterations O(kn)
	*/
	// Complexity for something like this won't matter during the test
 
	std::vector<int> res;
	auto cmp = [attractions](int a, int b){ return attractions[a] < attractions[b]; };
	std::make_heap(list.begin(), list.end(), cmp);

	for (int i = 0 ; i < std::min(k, list.size()); ++i)
	{
		std::pop_heap(list.begin(), list.end(), cmp);
		res.push_back(list.back());
	}

	return res;
}

int main(int argc, char const *argv[])
{
	std::vector<int> attractions = {10, 20, 15, 30, 40, 80};
	std::list<std::pair<int, int>> edges = {
		{0,1},
		{1,2},
		{1,3},
		{2,3},
		{2,4},
		{4,5},
	};
	auto g = create(edges);
	auto v = neighbours(g, 0, 2);
	for (auto x : v)
	{
		std::cout<<x<<" ";
	}
	std::cout<<std::endl;

	auto a = kWithMostAttractions(v, attractions, 2);

	for(auto x : a)
	{
		std::cout<<x<<" ";
	}
	std::cout<<std::endl;
	return 0;
}
