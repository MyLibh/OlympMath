//{ Binary indexed tree

#ifndef _ALGORITHM_
	#ifdef __has_include
		#if __has_include(<algorithm>)
			#include <algorithm>
		#else
			#error "Missing <algorithm>"
		#endif /* if __has_include(<algorithm>) */
	#else
		#include <algorithm>
	#endif /* ifdef __has_include */
#endif /* ifndef _ALGORITHM_ */

#define F(x) ((x) & (x + 1))
#define H(x) ((x) | (x + 1))

template<typename T>
class BinaryIndexedTree
{
public:
	using type_t = T;
	using ll_t   = long long;
	using ull_t  = unsigned long long;

public:
	BinaryIndexedTree(ull_t n) :
		m_size { n },
		m_array{ new type_t[m_size] },
		m_tree { new type_t[m_size] }
	{
		std::fill(m_array, m_array + m_size, type_t{});
		std::fill(m_tree, m_tree + m_size, type_t{});
	}

	BinaryIndexedTree(type_t arr[], ull_t n) :
		m_size { n },
		m_array{ new type_t[m_size] },
		m_tree { new type_t[m_size] }
	{
		std::fill(m_array, m_array + m_size, type_t{});
		std::fill(m_tree, m_tree + m_size, type_t{});

		for (ull_t i{ }; i < m_size; ++i)
		{
			m_array[i] += arr[i];

			if (auto h{ H(i) }; h < m_size)
				m_array[h] += m_array[i];
		}
	}

	~BinaryIndexedTree()
	{
		delete[] m_tree;
		delete[] m_array;
	}

	void add_range(ull_t r, type_t value) noexcept
	{
		for (ull_t i{ r }; static_cast<ll_t>(i); i = F(i) - 1)
			m_tree[i] += value;

		for (ull_t i{ H(r) }; i < m_size; i |= i + 1)
			m_array[i] += value * (r - F(i) + 1);
	}

	void add_range(ull_t l, ull_t r, type_t value) noexcept
	{
		add_range(r, value);

		if (l)
			add_range(l - 1, -value);
	}

	type_t sum(ull_t r) noexcept
	{
		type_t res{ };
		for (ull_t i{ r }; static_cast<ll_t>(i); i = F(i) - 1)
			res += m_array[i] + m_tree[i] * (i - F(i) + 1);

		for (ull_t i = H(r); i < m_size; i |= i + 1)
			res += m_tree[i] * (r - F(i) + 1);

		return res;
	}

	__forceinline type_t sum(ull_t l, ull_t r) noexcept { return (sum(r) - (l ? sum(l - 1) : type_t{})); }

private:
	ull_t   m_size;
	type_t *m_array,
		   *m_tree;
};

template<typename T>
using Fenwick = BinaryIndexedTree<T>;

template<typename T>
using BID = BinaryIndexedTree<T>;

#undef H
#undef F

//}
