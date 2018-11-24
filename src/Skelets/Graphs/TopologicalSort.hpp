#include <vector>    // std::vector
#include <algorithm> // std::reverse

using graph_t = std::vector<std::vector<long long>>;
using T       = graph_t::value_type::value_type;

void DFS(const graph_t &graph, std::vector<char> &used, std::vector<T> &res, size_t v)
{
	used[v] = true;
	for (auto i{ 0ull }; i < graph[v].size(); ++i)
		if (auto t{ graph[v][i] }; !used[t])
			DFS(graph, used, res, t);

	res.push_back(v);
}

std::vector<T> TopologicalSort(const graph_t &graph, size_t num)
{
	std::vector<char> used(num);
	std::vector<T>    res;
	for (auto i{ 0ull }; i < num; ++i)
		if (!used[i])
			DFS(graph, used, res, i);

	std::reverse(res.begin(), res.end());

	return (res);
}