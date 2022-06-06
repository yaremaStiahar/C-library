#include <vector>

using namespace std;

template <typename T>
struct sparse_table
{
private:
	size_t n;
	vector<int> lg;
	vector<vector<T>> table;
	T (*f)(T a, T b);
public:
	sparse_table(const vector<T>& vec, T (*func)(T a, T b))
	{
		n = vec.size();
		f = func;
		lg = vector<int>(n + 1);
		lg[1] = 0;
		for (int i = 2; i <= n; i++)
		{
			lg[i] = lg[i >> 1] + 1;
		}

		table = vector<vector<T>>(lg.back() + 1, vector<T>(n));
		for (int i = 0; i < n; i++) table[0][i] = vec[i];
		for (int i = 1; i < lg.back() + 1; i++)
		{
			int len = 1 << i;
			for (int j = 0; j < n - len + 1; j++)
			{
				table[i][j] = f(table[i - 1][j], table[i - 1][j + (len >> 1)]);
			}
		}
	}

	T get(int l, int r)
	{
		int len = r - l + 1;
		return f(table[lg[len]][l], table[lg[len]][r - (1 << lg[len]) + 1]);
	}
	
	int sz()
	{
		return n;
	}

	void set_function(T(*func)(T a, T b))
	{
		f = func; 
		for (int i = 1; i < lg.back() + 1; i++)
		{
			int len = 1 << i;
			for (int j = 0; j < n - len; j++)
			{
				table[i][j] = f(table[i - 1][j], table[i - 1][j + (len >> 1)]);
			}
		}
	}
};