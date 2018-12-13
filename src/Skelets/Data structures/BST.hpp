#include <set>
#include <iostream>

using ll_t = long long;

struct Node
{
	ll_t val;
	ll_t lvl;

	Node *left, *right;
};

class BST
{
private:
	void _add(Node* n, ll_t val)
	{
		if (val < n->val)
		{
			if (!n->left)
				n->left = new Node{ val, n->lvl + 1 };
			else
				_add(n->left, val);
		}
		else
		{
			if (!n->right)
				n->right = new Node{ val, n->lvl + 1 };
			else
				_add(n->right, val);
		}

		m_num++;
	}

	std::set<ll_t> _ans(Node* n, ll_t lvl)
	{
		if (!n || n->lvl > lvl)
			return {};

		if (n->lvl == lvl)
			return { n->val };

		std::set<ll_t> ans;
		if (n->lvl < lvl)
		{
			if(auto ans1 = _ans(n->left, lvl); ans1.size())
				ans.insert(ans1.begin(), ans1.end());

			if (auto ans2 = _ans(n->right, lvl); ans2.size())
				ans.insert(ans2.begin(), ans2.end());
		}

		return ans;
	}

	void _clear(Node *n)
	{
		if (n)
		{
			if (n->left)
				_clear(n->left);

			if (n->right)
				_clear(n->right);

			delete n;

			m_num--;
		}
	}

	void _dump(Node *n, bool is_right)
	{
		if (n)
		{
			std::cout << n->lvl << n->val << std::endl;

			if (n->left)
				_dump(n->left, false);

			if (n->right)
				_dump(n->right, true);
		}
	}

public:
	BST() : 
		m_head{} 
	{};

	~BST()
	{
		if(m_num)
			clear();
	}

	void add(ll_t val)
	{
		if (!m_head)
			m_head = new Node{ val };
		else
			_add(m_head, val);
	}

	std::set<ll_t> ans(ll_t lvl)
	{
		return _ans(m_head, lvl);
	}

	void clear()
	{
		_clear(m_head);
	}

	void dump()
	{
		std::cout << "BST dump" << std::endl;

	}

private:
	Node *m_head;
	ll_t  m_num;
};

using BinarySearchTree = BST;