#include "graph.hpp"

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

int main(int argc, char const *argv[])
{
    graph g = {
        {edge(1,1),edge(2,1),edge(4,1)}, // 0
        {edge(2,1), edge(3,1)}, // 1
        {edge(3,1), edge(5,1)}, // 2
        {edge(2,1), edge(5,1)}, // 3
        {edge(5,1), edge(0,1)}, // 4
        {edge(2,1), edge(3,1)} // 5
    };

    auto paths = allWays(g, 0, 3);
    for (const auto& path : paths)
    {
        for (auto n : path)
        {
            std::cout<<n<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
