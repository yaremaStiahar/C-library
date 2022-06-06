#pragma once
#include <vector>

using namespace std;

struct segment_sum_add
{
private:
	struct node
	{
		long long add;
		long long sum;
	};

	void build(int l, int r, int v, vector<int>& vec);

	long long sum(int lx, int rx, int v, int l, int r);

	void add(int l, int r, int val, int lx, int rx, int v);

	vector<node> t;
	int sz;
public:

	segment_sum_add(int n);

	segment_sum_add(vector<int>& v);

	void add(int l, int r, int val);

	long long sum(int lx, int rx);

	int size();
};