#include "Fenwick.h"

Fenwick::Fenwick(int sz)
{
	n = sz;
	bit.assign(n, 0);
}

Fenwick::Fenwick(vector<int> v)
{
	n = v.size();
	bit.assign(n, 0);

	for (int i = 0; i < n; i++)
	{
		bit[i] += v[i];
		if ((i | (i + 1)) < n)
			bit[i | (i + 1)] += bit[i];
	}
}

Fenwick::Fenwick(vector<long long> v)
{
	n = v.size();
	bit.assign(n, 0);

	for (int i = 0; i < n; i++)
	{
		bit[i] += v[i];
		if ((i | (i + 1)) < n)
			bit[i | (i + 1)] += bit[i];
	}
}

long long Fenwick::sum_on_prefix(int r)
{
	long long res = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
	{
		res += bit[r];
	}
	return res;
}

void Fenwick::increment(int i, long long increment)
{
	for (; i < n; i = (i | (i + 1)))
	{
		bit[i] += increment;
	}
}

long long Fenwick::query(int l, int r)
{
	return sum_on_prefix(r) - sum_on_prefix(l - 1);
}

int Fenwick::sz()
{
	return n;
}

int Fenwick::lower_bound(long long x)
{
	int LOG = 1;
	while ((LOG << 1) < n) LOG <<= 1;
	
	int idx = -1;
	long long query = 0;
	
	for (int i = LOG; i >= 0; i--)
	{
		if (idx + (1 << i) < n && query + bit[idx + (1 << i)] <= x)
		{
			query += bit[idx + (1 << i)];
			idx += (1 << i);
		}
	}
	return idx + 1;
}
