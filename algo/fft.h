#pragma once
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

void fft(vector<complex<double>>& a, bool inverse);

vector<int> multiply(vector<int>& a, vector<int>& b);