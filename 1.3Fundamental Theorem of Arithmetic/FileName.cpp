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

void FTofA(int n)
{
	int count[1000] = { 0 };
	int temp = n;
	int MAX = 2;

	for (int i = 2; i <= n;)
	{
		if (is_prime(i))
		{
			if (temp % i == 0)
			{
				temp /= i;
				count[i]++;
				MAX = i;
			}
			else
			{
				i++;
				continue;
			}
		}
		else
		{
			i++;
			continue;
		}
	}

	cout << n << "=";
	for (int i = 2; i <= n; i++)
	{
		if (count[i] != 0)
		{
			cout << i << "^" << count[i];
			if (i != MAX)
				cout << "*";
			else
				cout << endl;
		}
	}
}

int main()
{
	cout << "Please input n(n>0): ";
	int n;
	cin >> n;

	if (n == 1)
		cout << "n=1" << endl;
	else
		FTofA(n);

	return 0;
}
