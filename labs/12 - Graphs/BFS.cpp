/*
    Algorithms using Breadth-First-Search
    Complexity: O(|V| + |E|)
    Check if the graph is bipartite
        False when there is a path between 2 nodes in the same layer
    Find the shortest path between the source and every node (in edges)
*/

#include <queue>

#include "graph.hpp"

/*
    returns true when the graph is bipartite
    distance[x] == distance (in edges) from s to x
    if (parent[x] == -1) => there is no path between s and x (unless s == x)
    shortest path from s to x can be found by following parent[x]
    d[x] = layer
*/

bool BFS(const graph& g, int s, std::vector<int>& distance, std::vector<int>& parent)
{
    bool bipartite = true;
    int n = g.size();
    distance = std::vector<int>(n, infinity);
    parent = std::vector<int>(n, -1);
    std::queue<int> q;
    q.push(s);
    distance[s] = 0;
    int u;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for (const edge& e : g[u])
        {
            int v = e.first;
            if (parent[v] != -1 && distance[v] % 2 == distance[u] % 2) bipartite = false;
            if (parent[v] == -1)
            {
                distance[v] = distance[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    return bipartite;
}

int main()
{
    graph g = {
        {edge(1,1), edge(2,1)},
        {edge(2,1), edge(3,1)},
        {edge(3,1)},
        {edge(2,1)},
        {edge(5,1)},
        {}
    };

    std::vector<int> distance, parent;
    int source = 0;

    bool bipartite = BFS(g, source, distance, parent);

    printInfo(source, g.size(), distance, parent);

    std::cout << "The graph is "<< (bipartite ? "" : "NOT ") << "bipartite!" << std::endl;

    return 0;
}
