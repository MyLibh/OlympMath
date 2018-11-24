#include <queue>     // std::queue
#include <vector>    // std::vector
#include <algorithm> // std::reverse

using graph_t = std::vector<std::vector<long long>>;
using T       = graph_t::value_type::value_type;

//====================================================================================================================================
//!
//! \brief   Realization of BFS(breadth - first search) - a method of traversing the graph and finding the path in the graph
//!
//! \param   graph   Graph
//! \param   num     Number of vertices
//! \param   vertex  The vertex to which you need to restore the path
//! \param   start   Starting vertex
//!
//! \return  Shortest path to 'vertex'
//!
//!          O(N + M)
//!
//====================================================================================================================================

std::vector<T> BFS(const graph_t &graph, size_t num, T vertex, size_t start = 0ull)
{
	std::queue<T> q;
	q.push(start);

	std::vector<char> used(num);
	used[start] = true;

	std::vector<T> d(num),
		           p(num);
	p[start] = -1;
	while (!q.empty())
	{
		auto f{ q.front() };
		q.pop();

		for (auto i{ 0ull }; i < graph[f].size(); ++i)
			if (auto t{ graph[f][i] }; !used[t])
			{
				used[t] = true;

				q.push(t);

				d[t] = d[f] + 1;
				p[t] = f;
			}
	}

	if (!used[vertex])
		return {};
	else
	{
		std::vector<T> path;
		for (T i = vertex; i != -1; i = p[i])
			path.push_back(p[i] + 1);

		std::reverse(path.begin(), path.end());

		return (path);
	}
}

