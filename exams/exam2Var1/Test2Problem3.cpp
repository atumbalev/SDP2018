// Mega BRUTE FORCE
// Find all paths between the 2 nodes
// Check if there is a node which is in every path
// Do NOT try this at home

// Alternative solution:
// For every node n that is not a and b (or first use a bfs to find the shortest path and only test the nodes in the shortest path)
// Remove n from the graph
// Use BFS / DFS to check if b is reachable from a
// If not -> return true (n was on every path from a to b) 

#include <iostream>
#include <vector>
#include <algorithm>

using edge = std::pair<int,int>;
using node = std::vector<edge>;
using graph = std::vector<node>;

// Copy Pasta 
void way(const graph& g, int source, int target, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& paths);

std::vector<std::vector<int>> allWays(const graph& g, int source, int target)
{
    std::vector<std::vector<int>> paths = {};
    std::vector<bool> visited(g.size(), false);
    std::vector<int> path = {};
    way(g, source, target, visited, path, paths);

    return paths; 
}

void way(const graph& g, int source, int target, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& paths)
{
    visited[source] = true;
    path.push_back(source);

    if (source == target)
    {
        paths.push_back(path);
    }
    else
    {
        for (const auto& edge : g[source])
        {
            auto next = edge.first;
            if (!visited[next])
            {
                way(g, next, target, visited, path, paths);
            }
        }
    }

    visited[source] = false;
    path.pop_back();
}

// You had to implement all_of and find on your own, I don't because it's 12AM
bool allPathsGoThroughOneNode(const graph& g, int source, int target)
{
	auto paths = allWays(g, source, target);
	for (int i = 0 ; i < g.size(); ++i)
	{
		if (std::all_of(paths.cbegin(), paths.cend(), [i](const std::vector<int>& v) {
			return std::find(v.cbegin() + 1, v.cend() - 1, i) != v.cend() - 1;
		}))
		{
			return true;
		}
	}
    return false;
}

int main(int argc, char const *argv[])
{
    graph g = {
        {edge(1, 1), edge(2, 1), edge(3, 1), edge(4, 1)}, // 0
        {edge(2, 1), edge(4, 1)},                         // 1
        {edge(4, 1)},                                     // 2
        {edge(4, 1)},                                     // 3
        {edge(5,1)},                                      // 4
        {}                                                // 5
    };
    std::cout<<std::boolalpha<<allPathsGoThroughOneNode(g, 0, 5);
    return 0;
}
