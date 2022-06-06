#pragma once
#include <vector>

using namespace std;

struct dsu
{
private:
	int n;
	int diff;
	vector<int> p;
	vector<int> r;

public:
	dsu(int sz);

	int sz();

	int query(int x);

	void union_set(int a, int b);

	int different();
};