//{ SQRT-Decomposition

class SQRTDecomposition
{
public:
	using type_t = long long;
	using ull_t  = unsigned long long;

public:
	SQRTDecomposition(ull_t n, type_t array[]) :
		m_size { static_cast<ull_t>(sqrt(n + .0)) + 1 },
		m_array{ new type_t[m_size]{ } }
		}
	{
		for (ull_t i{}; i < m_size; ++i)
			b[i / len] += a[i];
	}

	type_t query(ull_t l, ull_t r)
	{
		int sum = 0;
		int c_l = l / len,   c_r = r / len;
		if (c_l == c_r)
		for (int i=l; i<=r; ++i)
			sum += a[i];

		else {
		for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
			sum += a[i];
		for (int i=c_l+1; i<=c_r-1; ++i)
			sum += b[i];
		for (int i=c_r*len; i<=r; ++i)
			sum += a[i];
		return sum;
	}

	void update()
	{
	}

private:
	ull_t   m_size;
	type_t *m_array;
};

using SQRTDEPOS = SQRTDecomposition;

//}
