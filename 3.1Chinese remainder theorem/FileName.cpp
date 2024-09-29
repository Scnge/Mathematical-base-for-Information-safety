#include<iostream>
#include<cmath>
using namespace std;

int Euclid(int a, int b, int& inv_a, int& inv_b)
{
	if (a < b)
	{
		int tempint = a;
		a = b;
		b = tempint;
		int& tempinv = inv_a;
		inv_a = inv_b;
		inv_b = tempinv;
	}

	int a0 = a, b0 = b, q = 1;
	int s0 = 1, s1 = 0, t0 = 0, t1 = 1;
	while (a % b != 0)
	{
		q = a / b;
		a = a % b;
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
		s0 -= q * s1;
		s0 = s0 ^ s1;
		s1 = s0 ^ s1;
		s0 = s0 ^ s1;
		t0 -= q * t1;
		t0 = t0 ^ t1;
		t1 = t0 ^ t1;
		t0 = t0 ^ t1;
	}

	if (s1 > 0)
		inv_a = s1;
	else
		inv_a = s1 + b0;

	if (t1 > 0)
		inv_b = t1;
	else 
		inv_b = t1 + a0;

	return b;
}

int Chinese(int* b, int* m, int n, int& M)
{
	int* Mn = new int[n];
	int rst = 0;
	M = 1;

	for (int i = 0; i < n; i++)
		M *= m[i];
	for (int i = 0; i < n; i++)
		Mn[i] = M / m[i];
	for (int i = 0; i < n; i++)
	{
		int temp, nop;
		Euclid(Mn[i], m[i], temp, nop);
		rst += temp * Mn[i] * b[i];
	}

	rst %= M;

	return rst;
}

int main()
{
	int n, M = 1;
	cout << "n=";
	cin >> n;

	int* b = new int[n];
	int* m = new int[n];
	for (int i = 0; i < n; i++)
	{
		cout << " b_" << i << "=";
		cin >> b[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << " m_" << i << "=";
		cin >> m[i];
		M *= m[i];
	}

	cout << "x¡Ô" << Chinese(b, m, n, M) << " (mod " << M << ")";
	return 0;
}