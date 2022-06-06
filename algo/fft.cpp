#include "fft.h"

using namespace std;

const double PI = acos(-1); 
#define ALL(a) a.begin(), a.end()

void fft(vector<complex<double>>& a, bool inverse)
{
	int n = a.size();
	if (n == 1)
		return;
	vector<complex<double>> a0(n >> 1), a1(n >> 1);
	for (int i = 0; i < n >> 1; i++)
	{
		a0[i] = a[i << 1];
		a1[i] = a[(i << 1) + 1];
	}
	fft(a0, inverse);
	fft(a1, inverse);
	double angle = 2 * PI / n * (inverse ? -1 : 1);
	complex<double> w(1), wn(cos(angle), sin(angle));
	for (int i = 0; i < n >> 1; i++)
	{
		a[i] = a0[i] + w * a1[i];
		a[i + (n >> 1)] = a0[i] - w * a1[i];
		w *= wn;
		if (inverse)
		{
			a[i] /= 2;
			a[i + (n >> 1)] /= 2;
		}
	}
}

vector<int> multiply(vector<int>& a, vector<int>& b)
{
	vector<complex<double>> a0(ALL(a)), b0(ALL(b));
	int n = 1;
	while (n < a.size() + b.size())
		n <<= 1;
	a0.resize(n);
	b0.resize(n);
	
	fft(a0, 0);
	fft(b0, 0);
	vector<complex<double>> c(n);
	for (int i = 0; i < n; i++)
		c[i] = a0[i] * b0[i];
	fft(c, 1);

	vector<int> result(n);
	for (int i = 0; i < n; i++)
		result[i] = round(c[i].real());
	return result;
}