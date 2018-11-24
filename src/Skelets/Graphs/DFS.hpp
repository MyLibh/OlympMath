#include <vector> // std::vector

using graph_t = std::vector<std::vector<long long>>;

//====================================================================================================================================
//!
//! \brief   Realization of DFS(depth - first search) - a method of traversing the graph
//!
//! \param   graph  Graph
//! \param   num    Number of vertices
//! \param   i      Node index
//!
//!			 O (N + M)
//!
//====================================================================================================================================

void DFS(const graph_t &graph, size_t num, size_t i)
{
	std::vector<char> used(num);
	used[i] = true;

	for (const auto &v : graph[i])
		if (!used[v])
			;//	DFS(v);
}

