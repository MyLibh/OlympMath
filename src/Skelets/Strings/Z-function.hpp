#include <vector>
#include <algorithm> // std::min
#include <string_view>
#include <string>
using ll_t = long long;

// Complexity: O(n) 

std::vector<ll_t> z_function(std::string_view str)
{
	ll_t n = str.length();

	std::vector<ll_t> z(n);
	for (ll_t i{ 1 }, l{}, r{}; i < n; ++i)
	{
		if (i <= r)
			z[i] = std::min(r - i + 1, z[i - l]);

		while (i + z[i] < n && str[z[i]] == str[i + z[i]])
			++z[i];

		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}

	return z;
}