#include <vector>
#include <iostream>

struct Node
{
	using ll_t = long long;

	ll_t val;

	static Node merge(const Node &lhv, const Node &rhv)
	{
		return { lhv.val + rhv.val };
	}
};

class RSQ
{
public:
	using ll_t = long long;

private:
	void _build(ll_t node, ll_t start, ll_t end)
	{
		if (start == end)
		{
			m_tree[node] = 
			{ 
				m_ref_arr[start] 
			};
		}
		else
		{
			auto mid = (start + end) / 2;

			_build(2 * node, start, mid);
			_build(2 * node + 1, mid + 1, end);

			m_tree[node] =
			{
				m_tree[2 * node].val + m_tree[2 * node + 1].val
			};
		}
	}

	void _update(ll_t pos, ll_t val, ll_t node, ll_t start, ll_t end)
	{
		if (start == end)
		{
			m_tree[node].val += val;
		}
		else
		{
			auto mid = (start + end) / 2;
			if (start <= pos && pos <= mid)
				_update(pos, val, 2 * node, start, mid);
			else
				_update(pos, val, 2 * node + 1, mid + 1, end);

			m_tree[node] =
			{
				m_tree[2 * node].val + m_tree[2 * node + 1].val
			};
		}
	}

	ll_t _query(ll_t l, ll_t r, ll_t node, ll_t start, ll_t end) const
	{
		if (r < start || end < l || r < l)
			return 0;

		if (l == start && end == r)
			return m_tree[node].val;

		auto mid = (start + end) / 2;
		return _query(l, r, 2 * node, start, mid) + _query(l, r, 2 * node, mid + 1, end);
	}

public:
	RSQ(const std::vector<ll_t> &arr) :
		m_tree   { },
		m_ref_arr{ arr },
		m_arr_end{ static_cast<ll_t>(arr.size() - 1) }
	{
		m_tree.resize(arr.size() * 2);
	}

	void build()
	{
		_build(1, 0, m_arr_end);
	}

	void update(ll_t pos, ll_t val)
	{
		_update(pos, val, 1, 0, m_arr_end);
	}

	ll_t query(ll_t l, ll_t r) const
	{
		return _query(l, r, 1, 0, m_arr_end);
	}

	void dump() const 
	{
		std::cout << "RSQ dump" << std::endl;
		for (ll_t i{}; i < m_tree.size(); ++i)
			std::cout << i << " " << m_tree[i].val << std::endl;
	}

private:
	std::vector<Node>        m_tree;
	const std::vector<ll_t> &m_ref_arr;
	ll_t                     m_arr_end;
};