using ll_t = long long;

// Complexity: O(plog[p, n])

ll_t factmod(ll_t n, ll_t p)
{
	ll_t res{ 1 };
	while (n > 1) 
	{
		res = (res * ((n / p) & 1 ? p - 1 : 1)) % p;

		for (ll_t i{ 2 }; i <= n % p; ++i)
			res = (res * i) % p;

		n /= p;
	}

	return (res % p);
}