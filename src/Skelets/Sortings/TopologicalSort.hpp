#include <vector>    // std::vector
#include <algorithm> // std::reverse

using graph_t = std::vector<std::vector<long long>>;
using T       = graph_t::value_type::value_type;

//====================================================================================================================================
//!
//! \brief   Topological sorting - ordering of vertices of a contour-oriented oriented graph according to the partial order,
//!          given by the edges of the digraph on the set of its vertices
//!
//! \param   graph  Graph
//! \param   num    Number of vertices
//!
//! \return  Permutation of vertices (topological order) corresponding to the order given by all edges of the graph.
//!
//!          T(N) = O(N)
//!			 M(N) = O(N)
//!
//====================================================================================================================================

std::vector<T> TopologicalSort(const graph_t &graph, size_t num)
{
	std::vector<char> used(num);
	std::vector<T>    res;
	auto DFS = [&](size_t v) 
	{
		used[v] = true;
		for (auto i{ 0ull }; i < graph[v].size(); ++i)
			if (auto t{ graph[v][i] }; !used[t])
				DFS(t);

		res.push_back(v);
	}

	for (auto i{ 0ull }; i < num; ++i)
		if (!used[i])
			DFS(i);

	std::reverse(res.begin(), res.end());

	return (res);
}