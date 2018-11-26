using ll_t = long long;

// Complexity: O(sqrt(N))

ll_t phi(ll_t n)
{
	ll_t res{ n };
	for (ll_t i{ 2 }; i * i <= n; ++i)
		if (n % i == 0) 
		{
			while (n % i == 0)
				n /= i;

			res -= res / i;
		}

	if (n > 1)
		res -= res / n;

	return res;
}