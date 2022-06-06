#include <vector>

using namespace std;

// A Fenwick tree (binary indexed tree)
struct Fenwick
{
private:
	vector<long long> bit;
	int n;

public:

	Fenwick(int sz);

	Fenwick(vector<int> v);

	Fenwick(vector<long long> v);

	long long sum_on_prefix(int r);

	void increment(int i, long long increment);

	long long query(int l, int r);

	int sz();

	int lower_bound(long long x);
};