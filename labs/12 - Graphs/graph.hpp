#pragma once

#include <iostream>
#include <vector>
#include <forward_list>

using edge = std::pair<int,int>;
using node = std::vector<edge>;
using graph = std::vector<node>;

#define infinity  -1

std::forward_list<int> path(int s, int t, const std::vector<int>& parent)
{
    std::forward_list<int> path;
    while(t != -1)
    {
        path.push_front(t);
        t = parent[t];
    }

    return path;
}

graph reverse(graph g)
{
    int n = g.size();
    graph reversedGraph(n);
    for(int i = 0 ; i < n ; i ++)
    {
        for(edge e : g[i])
        {
            reversedGraph[e.first].push_back(edge(i, e.second));
        }
    }

    return reversedGraph;
}

void printInfo(int source, int n, const std::vector<int>& distance, const std::vector<int>& parent)
{
	for (int i = 0 ; i < n; i++)
    {
        if(parent[i] != -1 || i == source)
        {
            std::cout<<"The distance from "<<source<<" to "<<i<<" is: "<<distance[i]<<"\nThe path is: ";
            auto p = path(source,i,parent);
            for (auto node : p)
            {
                std::cout<<node<<" ";
            }
            std::cout<<std::endl;
        }
        else std::cout<<"There is no path from "<<source<<" to "<<i<<std::endl;
    }
}
