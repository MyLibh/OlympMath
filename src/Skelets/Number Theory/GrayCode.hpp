using ll_t = long long;

ll_t GrayCode(ll_t n)
{
	return n ^ (n >> 1ll);
}

ll_t RevGrayCode(ll_t g) 
{
	ll_t n{};
	for (; g; g >>= 1)
		n ^= g;

	return n;
}