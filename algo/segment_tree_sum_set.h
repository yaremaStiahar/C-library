#pragma once
#include <vector>

using namespace std;

struct segment_sum_set
{
private:
	struct node
	{
		bool to_set;
		long long set;
		long long sum;
	};

	void build(int l, int r, int v, vector<int>& vec);

	void prop(int v, int l, int r);

	void set(int l, int r, int val, int lx, int rx, int v);

	long long sum(int lx, int rx, int v, int l, int r);

	vector<node> t;
	int sz;
public:

	segment_sum_set(int n);

	segment_sum_set(vector<int>& v);


	void set(int l, int r, int val);


	long long sum(int lx, int rx);

	int size();
};