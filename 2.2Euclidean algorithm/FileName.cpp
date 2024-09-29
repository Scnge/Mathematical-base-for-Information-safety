#include<iostream>
#include<cmath>
using namespace std;

int gcd(int a, int b)
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

int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}

int euclidean(int a,int b)
{
	int r, q, s1 = 1, s2 = 0, s3, t1 = 0, t2 = 1, t3 = 1;
	int atemp = a % b;
	int btemp = b;

	while (1) 
	{
		r = btemp % atemp;
		q = btemp / atemp;
		if (!r) 
			break;

		btemp = atemp; atemp = r;
		s3 = s1 - q * s2;	
		t3 = t1 - q * t2;	
		s1 = s2; s2 = s3;		
		t1 = t2; t2 = t3;
	}

	if (t3 < 0)
		t3 += b;

	return t3;
}

int main()
{
	int a, b;
	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;

	cout << "gcd(a,b)=" << gcd(a, b) << endl;
	cout << "lcm(a,b)=" << lcm(a, b) << endl;

	cout << "a^(-1)=" << euclidean(a, b) << "(mod " << b << ")" << endl;
	cout << "b^(-1)=" << euclidean(b, a) << "(mod " << a << ")";

	return 0;
}