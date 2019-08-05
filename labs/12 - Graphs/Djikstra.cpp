/*
    Djikstra's Shortest Path algorithm (One source all targets)
    Complexity: O(|E|log|V|)
    O(|V|log|V|) can be achieved using a Fibonacci Heap and a slight modification to the algorithm,
    generally better (IN THEORY) as interesting graphs tend to have more edges than vertices (in practice binary heap outperforms other heaps due to cache optimization)
*/

#include <queue>
#include <functional>

#include "graph.hpp"

struct cmp
{
    bool operator()(const std::pair<edge, size_t>& lhs, const std::pair<edge, size_t>& rhs)
    {
        return lhs.first.second > rhs.first.second;
    }
};

void Djikstra(const graph& g, int s, std::vector<int>& distance, std::vector<int>& parent)
{
    int n = g.size();
    std::vector<bool> marked(n, false);
    distance = std::vector<int>(n, infinity);
    parent = std::vector<int>(n, -1);

    std::priority_queue<
        std::pair<edge, size_t>,
        std::vector<std::pair<edge, size_t>>,
        cmp
    > q;

    q.push(std::make_pair(edge(s, 0), -1)); // Fictive edge with 0 weight
    while(!q.empty())
    {
        auto t = q.top();
        q.pop();
        int d = t.first.second;
        int p = t.second;
        int u = t.first.first;
        if (!marked[u])
        {
            marked[u] = true;
            distance[u] = d;
            parent[u] = p;

            for(edge e : g[u])
            {
                e.second += d;
                q.push(std::make_pair(e, u));
            }
        }
    }
}

int main()
{
    graph g = {
            { edge(1, 1), edge(3, 3), edge(4, 5) },             //0
            { edge(0, 1), edge(2, 2), edge(5, 2) },             //1
            { edge(1, 2), edge(4, 6) },                         //2
            { edge(0, 3), edge(6, 10) },                        //3
            { edge(0, 5), edge(2, 6), edge(6, 7), edge(7, 2) }, //4
            { edge(1, 2), edge(7, 5) },                         //5
            { edge(3, 10), edge(4, 7), edge(7, 20) },           //6
            { edge(4, 2), edge(5, 5), edge(6, 20) } };          //7

    std::vector<int> distance, parent;
    int source = 0;
    Djikstra(g, source, distance, parent);
    printInfo(source, g.size(), distance, parent);
}
