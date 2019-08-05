/*
    Algorithms using Depth-First-Search
    Complexity: O(|E| + |V|)
    Topological Order
    Strongly Connected Components
    Shortest Path in Directed Acyclic Graph
*/

#include <forward_list>

#include "graph.hpp"

#define white      0
#define gray       1
#define black      2

bool DFSVisit(const graph& g, int u, std::vector<int>& color, std::forward_list<int>& topOrder);

bool DFS(const graph& g, std::forward_list<int>& topOrder)
{
    bool acyclic = true;
    int n = g.size();
    std::vector<int> color(n, white);
    for(int i = 0; i < n; i++)
    {
        if(color[i] == white)
        {
            acyclic = DFSVisit(g, i, color, topOrder) && acyclic;
        }
    }

    return acyclic;
}

bool DFSVisit(const graph& g, int u, std::vector<int>& color, std::forward_list<int>& topOrder)
{
    bool acyclic = true;
    color[u] = gray;
    for (edge e : g[u])
    {
        int v = e.first;
        if (color[v] == white)
        {
            acyclic = DFSVisit(g, v, color, topOrder) && acyclic;
        }
        else if (color[v] == gray)
        {
            acyclic = false;
        }
    }
    color[u] = black;
    topOrder.push_front(u);

    return acyclic;
}

std::forward_list<std::forward_list<int>> SCC(graph g)
{
    std::forward_list<int> topOrd;
    DFS(g, topOrd);
    graph rev = reverse(g);
    int n = g.size();
    std::vector<int> color(n, white);
    std::forward_list<std::forward_list<int>> comps;
    for (auto node : topOrd)
    {
        if (color[node] == white)
        {
            std::forward_list<int> comp;
            DFSVisit(rev, node, color, comp);
            comps.push_front(comp);
        }
    }

    return comps;
}

void shortestPathDAG(const graph& g, int source, std::vector<int>& distance, std::vector<int>& parent)
{
    int n = g.size();
    std::forward_list<int> topoOrder;
    bool ac = DFS(g, topoOrder);
    std::cout<<"The DAG is "<< (ac ? "" : "NOT ") << "acyclic" <<std::endl;
    std::cout<<"TOPOLOGICAL ORDER: ";
    for (auto x : topoOrder)
    {
        std::cout<<x<<" ";
    }
    std::cout<<std::endl;
    distance = std::vector<int>(n, infinity);
    parent = std::vector<int>(n,-1);
    distance[source] = 0;
    for(int u : topoOrder)
    {
        if (distance[u] != infinity)
        {
            for (edge e : g[u])
            {
                int v = e.first, w = e.second;
                if (distance[v] == infinity || distance[v] > distance[u] + w)
                {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }
            }
        }
    }
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

    std::forward_list<int> tOrd;
    bool ac = DFS(g, tOrd);
    std::cout<<"The graph is "<< (ac ? " " : "NOT ") << "acyclic" <<std::endl;
    std::cout<<"Strongly Connected Components of the graph: \n";
    std::forward_list<std::forward_list<int>> comps = SCC(g);
    std::cout<<std::endl;
    for(const auto& comp : comps)
    {
        std::cout<<"{ ";
        for(auto node : comp)
        {
            std::cout<<node<<" ";
        }
        std::cout<<"}\n";
    }

    std::cout<<"\n\nDAG\n\n";
    graph DAG = {
                    { edge(1, 1), edge(3, 3), edge(4, 5) }, // 0
                    { edge(2, 2), edge(5, 2) },             // 1
                    {},                                     // 2
                    { edge(6, 1) },                         // 3
                    { edge(7, 2) },                         // 4
                    {},                                     // 5
                    { edge(7, 1) },                         // 6
                    { edge(5, 5) }};                        // 7

    std::vector<int> parent;
    std::vector<int> distance;
    int source = 0;
    shortestPathDAG(DAG, source, distance, parent);
 
    printInfo(source, DAG.size(), distance, parent);
    return 0;
}
