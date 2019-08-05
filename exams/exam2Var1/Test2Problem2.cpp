#include <vector>
#include <iostream>
#include <queue>

void bfs(const std::vector<std::vector<bool>>& graph, int size, int source)
{
	std::vector<bool> marked(size, false);
	std::queue<int> q;
	q.push(source);
	marked[source] = true;

	while(!q.empty())
	{
		std::cout<<q.front();
		for (int i = 0; i < size; i++)
		{
			if (!marked[i] && graph[q.front()][i])
			{
				q.push(i);
				marked[i] = true;
			}
		}
		q.pop();
	}
}

int main(int argc, char const *argv[])
{
	std::vector<std::vector<bool>> graph(6, std::vector<bool>(6,false));
	graph[0][1] = true;
	graph[0][2] = true;
	graph[1][5] = true;
	graph[2][3] = true;
	graph[2][4] = true;
	graph[3][5] = true;
	graph[4][5] = true;

	bfs(graph, 6, 0);
	return 0;
}