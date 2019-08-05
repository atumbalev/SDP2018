#include <iostream>
#include <vector>
#include <algorithm>

using edge = std::vector<unsigned>;
using graph = std::vector<edge>;

int main(int argc, char const *argv[])
{
	graph g = {
        {1, 2}, // 0
        {2, 3}, // 1
        {3},	// 2
        {2,4},  // 3
        {5},    // 4
        {6},    // 5
        {5}     // 6
    };

    std::vector<std::vector<bool>> connected(g.size(), std::vector<bool>(g.size(), false));

    // Modified Floyd-Warshal (alternatively, start a BFS for every node in the graph, that would be better for sparse graphs)
    // If connected[i][j] then there is a path from j to i (this is a transposed version of the regular connected matrix, to make the last part of the problem easier)
    for (int i = 0 ; i < g.size() ; i++)
    {
    	connected[i][i] = true;
    }

    for (int i = 0 ; i < g.size() ; i++)
    {
    	for (auto e : g[i])
    	{
    		connected[e][i] = true;
    	}
    }

    for (int k = 0; k < g.size(); k++)
    {
        for(int i = 0; i < g.size() ; i++)
        {
            for(int j = 0; j < g.size(); j++)
            {
            	if (connected[k][i] && connected[j][k])
            	{
            		connected[j][i] = true;
            	}
            }
        }
    }

    for (int i = 0 ; i < g.size() ; i++)
    {
    	// You had to do this by yourselves
    	if (std::all_of(connected[i].cbegin(), connected[i].cend(), [](bool b) { return b ;}))
    	{
    		std::cout << i << " ";
    	}
    }
    std::cout << std::endl;

	return 0;
}