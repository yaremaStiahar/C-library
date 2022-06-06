#include "suffix_array.h"


void count_sort(vector<int>& p, vector<int>& c)
{
	int n = p.size();
	vector<int> cnt(n);
	for (int i = 0; i < n; i++)
	{
		cnt[c[i]]++;
	}
	vector<int> pos(n);
	for (int i = 1; i < n; i++)
	{
		pos[i] = pos[i - 1] + cnt[i - 1];
	}
	vector<int> p2(n);
	for (auto& x : p)
	{
		int i = c[x];
		p2[pos[i]++] = x;
	}
	p = p2;
}


vector<int> suffix_array(string& s)
{
	s += "$";
	int n = s.size();
	vector<int> p(n), c(n);
	for (int i = 0; i < n; i++) p[i] = i;
	sort(p.begin(), p.end(), [&](int& i, int& j)
		{
			return s[i] < s[j];
		});
	int x = 0;
	c[p[0]] = 0;
	for (int i = 1; i < n; i++)
	{
		if (s[p[i]] != s[p[i - 1]])
			x++;
		c[p[i]] = x;
	}
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++)
		{
			p[i] = (p[i] - (1 << k) + n) % n;
		}

		count_sort(p, c);

		vector<int> c2(n);
		for (int i = 1; i < n; i++)
		{
			pair<int, int> pr = { c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n] };
			pair<int, int> nx = { c[p[i]], c[(p[i] + (1 << k)) % n] };
			if (pr == nx)
				c2[p[i]] = c2[p[i - 1]];
			else
				c2[p[i]] = c2[p[i - 1]] + 1;
		}
		c = c2;
		k++;
	}
	return p;
}
