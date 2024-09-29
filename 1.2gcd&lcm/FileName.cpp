#include<iostream>
#include<cmath>
using namespace std;

int zzxc(int a, int b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	int temp = a;
	while (temp != 0)
	{
		temp = a % b;
		a = b;
		b = temp;
	}

	return a;
}

int main()
{
	int a, b;

	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;

	int gcd = zzxc(a, b);
	int lcm = a * b / gcd;

	cout << "gcd(a,b)=" << gcd << endl;
	cout << "lcm(a,b)=" << lcm;

	return 0;
}