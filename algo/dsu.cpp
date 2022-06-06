#include "dsu.h"
#include <set>

dsu::dsu(int sz)
{
	n = sz;
	diff = sz;
	for (int i = 0; i < n; i++)
	{
		p.push_back(i);
		r.push_back(0);
	}
}

int dsu::sz()
{
	return n;
}

int dsu::query(int x)
{
	if (p[x] == x)
		return x;
	return p[x] = query(p[x]);
}

void dsu::union_set(int a, int b)
{
	a = query(a);
	b = query(b);
	if (a != b)
	{
		diff--;
		if (r[a] < r[b])
			swap(a, b);
		p[b] = a;
		if (r[a] == r[b])
			r[a]++;
	}
}

int dsu::different()
{
	return diff;

}