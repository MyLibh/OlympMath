using ll_t = long long;

// Complexity: O(log(N))

ll_t binpow(ll_t a, ll_t n) 
{
	ll_t res{ 1 };
	while (n) 
	{
		if (n & 1)
			res *= a;

		a *= a;
		n >>= 1;
	}

	return res;
}