#pragma once
#include <utility>
#include <ctime>
#include <vector>

using namespace std;

// Cartesian tree
template <class T, class _Pr = less<T>>
struct treap
{
private:
	struct node
	{
		node* left;
		node* right;
		T val;
		int sz;

		node(T x)
		{
			left = nullptr;
			right = nullptr;
			val = x;
			sz = 1;
		}

	};
	node* root;

	int get_size(node* p)
	{
		if (p == nullptr)
			return 0;
		return p->sz;
	}

	pair<node*, node*> split(node* r, T x)
	{
		if (r == nullptr)
		{
			return { nullptr, nullptr };
		}
		if (r->val < x)
		{
			r->sz -= get_size(r->right);
			auto p = split(r->right, x);
			r->right = p.first;
			r->sz += get_size(p.first);
			return { r, p.second };
		}
		else
		{
			r->sz -= get_size(r->left);
			auto p = split(r->left, x);
			r->left = p.second;
			r->sz += get_size(p.second);
			return { p.first, r };
		}
	}

	node* merge(node* l, node* r)
	{
		if (l == nullptr)
			return r;
		if (r == nullptr)
			return l;
		int x = rand() % (l->sz + r->sz);
		if (x < l->sz)
		{
			l->sz += r->sz;
			l->right = merge(l->right, r);
			return l;
		}
		else
		{
			r->sz += l->sz;
			r->left = merge(l, r->left);
			return r;
		}
	}

	bool contains(node* r, T x)
	{
		if (r == nullptr)
			return false;
		if (r->val == x)
			return true;
		if (r->val > x)
			return contains(r->left, x);
		else
			return contains(r->right, x);
	}

	int find_kth(node* r, int k)
	{
		if (get_size(r->left) == k - 1)
			return r->val;
		if (get_size(r->left) > k - 1)
			return find_kth(r->left, k);
		else
			return find_kth(r->right, k - get_size(r->left) - 1);
	}

	void get_all(vector<T>& v, node* r)
	{
		if (r == nullptr)
			return;
		get_all(v, r->left);
		v.push_back(r->val);
		get_all(v, r->right);
	}

public:

	treap()
	{
		root = nullptr;
		srand(time(NULL));
	}

	bool contains(T x)
	{
		return contains(root, x);
	}

	void insert(T x)
	{
		if (root == nullptr)
		{
			root = new node(x);
			return;
		}
		if (contains(root, x))
		{
			return;
		}
		auto p = split(root, x);
		node* nod = new node(x);
		root = merge(p.first, nod);
		root = merge(root, p.second);
	}

	void erase(T x)
	{
		if (root == nullptr)
		{
			root = new node(x);
			return;
		}
		if (!contains(root, x))
		{
			return;
		}
		auto p = split(root, x);
		auto p2 = split(p.second, x + 1);
		root = merge(p.first, p2.second);
	}

	int find_kth(int k)
	{
		if (get_size(root) < k)
		{
			throw "out of range\n";
		}
		return find_kth(root, k);
	}

	vector<T> get_all()
	{
		vector<T> vec;
		get_all(vec, root);
		return vec;
	}
};