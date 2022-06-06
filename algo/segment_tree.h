#pragma once
#include <vector>

using namespace std;

template <typename T>
struct segment_tree
{
private:
	int n;
	vector<T> tree;
	T(*combine)(T left, T right);
	T null;

	void build(const vector<T>& values, int x, int l, int r)
	{
		if (r - l == 1)
		{
			if (l < values.sz())
				tree[x] = values[l];
		}
		else
		{
			int m = (r + l) / 2;
			build(values, x * 2 + 1, l, m);
			build(values, x * 2 + 2, m, r);
			tree[x] = combine(tree[x * 2 + 1], tree[x * 2 + 2]);
		}
	}

	void set(int i, T val, int x, int l, int r)
	{
		if (r - l == 1)
		{
			tree[x] = val;
			return;
		}
		int m = (r + l) / 2;
		if (i < m)
			set(i, val, x * 2 + 1, l, m);
		else
			set(i, val, x * 2 + 2, m, r);
		tree[x] = combine(tree[x * 2 + 1], tree[x * 2 + 2]);
	}

	T query(int l, int r, int x, int lx, int rx)
	{
		if (l >= rx || r <= lx)
			return null;
		if (l <= lx && r >= rx)
			return tree[x];
		else
		{
			int m = (rx + lx) / 2;
			T s1 = query(l, r, x * 2 + 1, lx, m);
			T s2 = query(l, r, x * 2 + 2, m, rx);
			return combine(s1, s2);
		}
	}

public:

	segment_tree(int sz, T(*f)(T left, T right), T zero)
	{
		null = zero;
		n = 1;
		combine = f;
		while (n < sz) n <<= 1;
		tree.assign((2 * n) - 1, null);
	}

	segment_tree(const vector<T>& v, T(*f)(T left, T right), T zero)
	{
		null = zero;
		n = 1;
		combine = f;
		while (n < v.sz()) n <<= 1;
		tree.assign((2 * n) - 1, null);
		build(v, 0, 0, n);
	}

	void set(int i, T val)
	{
		set(i, val, 0, 0, n);
	}

	// get func on segment [l, r)
	T query(int l, int r)
	{
		return query(l, r, 0, 0, n);
	}

	int sz()
	{
		return n;
	}
};