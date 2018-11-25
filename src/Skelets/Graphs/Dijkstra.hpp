#include <vector>
#include <climits>
#include <set>
#include <functional>

using ll_t    = long long;

struct Edge
{
	ll_t to;
	ll_t length;
};

using graph_t = std::vector<std::vector<Edge>>;

int dijkstra(const graph_t &graph, ll_t start, ll_t finish)
{
	std::vector<ll_t> min_distance(graph.size(), LLONG_MAX);
	min_distance[start] = 0ll;

	std::set<std::pair<ll_t, ll_t>> active_vertices;
	active_vertices.insert({ 0, start });
	while (!active_vertices.empty())
	{
		ll_t current = active_vertices.begin()->second;
		if (current == finish)
			return min_distance[current];

		active_vertices.erase(active_vertices.begin());
		for(auto &&edge : graph[current])
			if (auto dist{ min_distance[current] + edge.length }; min_distance[edge.to] > dist)
			{
				active_vertices.erase({ min_distance[edge.to], edge.to });

				min_distance[edge.to] = dist;

				active_vertices.insert({ min_distance[edge.to], edge.to });
			}
	}

	return LLONG_MAX;
}