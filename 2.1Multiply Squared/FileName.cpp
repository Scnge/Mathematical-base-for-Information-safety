#include<iostream>
#include<cmath>
using namespace std;

int cal(int a, int n, int m) 
{
    int result = 1;
    while (n > 0) 
    {
        if (n & 1)
            result = (result * a) % m;
        a = (a * a) % m;
        n >>= 1;
    }
    return result;
}


int main()
{
    cout << "Calculate a^n(mod m)..." << endl << "Please input:" << endl;
    int a, n, m;
    cout << "  a=";
    cin >> a;
    cout << "  n=";
    cin >> n;
    cout << "  m=";
    cin >> m;

    int result = cal(a, n, m);

    cout << a << "^" << n << "(mod " << m << ")=" << result;

    return 0;
}