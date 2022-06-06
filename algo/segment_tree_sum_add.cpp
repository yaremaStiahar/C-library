#include "segment_tree_sum_add.h"

using namespace std;

void segment_sum_add::build(int l, int r, int v, vector<int>& vec)
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

segment_sum_add::segment_sum_add(int n)
{
	sz = 1;
	while (sz < n) sz *= 2;
	t.assign((2 * sz) - 1, { 0, 0 });
}

segment_sum_add::segment_sum_add(vector<int>& v)
{
	int n = v.size();
	sz = 1;
	while (sz < n) sz *= 2;
	t.assign((2 * sz) - 1, { 0, 0 });
	build(0, sz, 0, v);
}


void segment_sum_add::add(int l, int r, int val)
{
	add(l, r, val, 0, sz, 0);
}

void segment_sum_add::add(int l, int r, int val, int lx, int rx, int v)
{
	if (r <= lx || l >= rx)
	{
		return;
	}
	if (r >= rx && l <= lx)
	{
		t[v].add += val;
	}
	else
	{
		int m = (rx + lx) / 2;
		add(l, r, val, lx, m, v * 2 + 1);
		add(l, r, val, m, rx, v * 2 + 2);
		int len = (rx - lx) / 2;
		t[v].sum = (t[v * 2 + 1].sum + t[v * 2 + 1].add * len) + (t[v * 2 + 2].sum + t[v * 2 + 2].add * len);
	}
}

long long segment_sum_add::sum(int lx, int rx)
{
	return sum(lx, rx, 0, 0, sz);
}

long long segment_sum_add::sum(int lx, int rx, int v, int l, int r)
{
	if (lx >= r || rx <= l)
		return 0;
	else if (lx <= l && rx >= r)
		return (t[v].sum + t[v].add * (r - l));
	else
	{
		int mid = (r + l) / 2;
		long long m1 = sum(lx, rx, v * 2 + 1, l, mid);
		long long m2 = sum(lx, rx, v * 2 + 2, mid, r);
		return (m1 + m2) + t[v].add * (min(rx, r) - max(lx, l));
	}
}

int segment_sum_add::size()
{
	return sz;
}