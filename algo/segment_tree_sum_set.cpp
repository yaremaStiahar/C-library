#include "segment_tree_sum_set.h"

using namespace std;


void segment_sum_set::build(int l, int r, int v, vector<int>& vec)
{
	if (l >= vec.size())
	{
		return;
	}
	if (l + 1 == r)
	{
		t[v].sum = vec[l];
	}
	else
	{
		int m = (l + r) / 2;
		build(l, m, v * 2 + 1, vec);
		build(m, r, v * 2 + 2, vec);
		t[v].sum = (t[v * 2 + 1].sum + t[v * 2 + 2].sum);
	}
}

segment_sum_set::segment_sum_set(int n)
{
	sz = 1;
	while (sz < n) sz *= 2;
	t.assign((2 * sz) - 1, { false, 0, 0 });
}


segment_sum_set::segment_sum_set(vector<int>& v)
{
	int n = v.size();
	sz = 1;
	while (sz < n) sz *= 2;
	t.assign((2 * sz) - 1, { false, 0, 0 });
	build(0, sz, 0, v);
}

void segment_sum_set::prop(int v, int l, int r)
{
	if (!t[v].to_set) return;
	if (r - l == 1)return;
	int len = (r - l) / 2;
	t[v * 2 + 1].set = t[v].set;
	t[v * 2 + 1].set = t[v].to_set = true;
	t[v * 2 + 1].sum = t[v].set * len;
	t[v * 2 + 2].set = t[v].set;
	t[v * 2 + 2].set = t[v].to_set = true;
	t[v * 2 + 2].sum = t[v].set * len;
	t[v].set = 0;
	t[v].to_set = false;
}

void segment_sum_set::set(int l, int r, int val)
{
	set(l, r, val, 0, sz, 0);
}

void segment_sum_set::set(int l, int r, int val, int lx, int rx, int v)
{
	prop(v, lx, rx);
	if (r <= lx || l >= rx)
		return;
	if (r >= rx && l <= lx)
	{
		t[v].to_set = true;
		t[v].set = val;
		t[v].sum = 1ll * val * (rx - lx);
	}
	else
	{
		int m = (rx + lx) / 2;
		set(l, r, val, lx, m, v * 2 + 1);
		set(l, r, val, m, rx, v * 2 + 2);
		t[v].sum = t[v * 2 + 1].sum + t[v * 2 + 2].sum;
	}
}

long long segment_sum_set::sum(int lx, int rx)
{
	return sum(lx, rx, 0, 0, sz);
}

long long segment_sum_set::sum(int lx, int rx, int v, int l, int r)
{
	prop(v, l, r);
	if (lx >= r || rx <= l)
		return 0;
	else if (lx <= l && rx >= r)
		return t[v].sum;
	else
	{
		int mid = (r + l) / 2;
		long long m1 = sum(lx, rx, v * 2 + 1, l, mid);
		long long m2 = sum(lx, rx, v * 2 + 2, mid, r);
		return m1 + m2;
	}
}

int segment_sum_set::size()
{
	return sz;
}