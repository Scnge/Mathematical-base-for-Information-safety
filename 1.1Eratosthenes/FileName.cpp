#include<iostream>
#include<cmath>
using namespace std;

bool is_prime(long long n)
{
	if (n < 2)
		cout << "ERROR";

	for (long long i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

void find_prime(long long n)
{
	if (n < 2)
		cout << "ERROR";

	bool* result = new bool[n];
	for (long long i = 0; i < n; i++)
		result[i] = true;

	for (int i = 2; i < sqrt(n); i++)
	{
		if (is_prime(i))
		{
			for (long long temp = 2 * i; temp <= n; temp += i)
				result[temp] = false;
		}
	}

	for (long long i = 2; i <= n; i++)
	{
		if (result[i])
		{
			cout << i << " ";
		}
	}
}

int main()
{
	cout << "Please input the range:1-";
	long long n;
	cin >> n;

	cout << "----------------------------------------------------------------" << endl;
	find_prime(n);
	cout << endl;
	cout << "----------------------------------------------------------------";

	return 0;
}