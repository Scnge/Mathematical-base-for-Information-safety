#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Number 
{
    int base;
    int exponent;
};

vector<Number> Decompose(int n)
{
    vector<Number> num;
    for (int i = 2; i <= n; ++i) 
    {
        if (n % i == 0) 
        {
            Number f = { i, 0 };
            while (n % i == 0) 
            {
                f.exponent++;
                n /= i;
            }
            num.push_back(f);
        }
        if (n == 1) break;
    }
    return num;
}

int mod(int x, int y, int m) 
{
    int result = 1;
    x %= m;
    while (y > 0) 
    {
        if (y & 1) result = (result * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return result;
}

bool judge(const vector<Number>& factors)
{
    if (factors.size() == 1)
        return (factors[0].base == 2 && factors[0].exponent <= 2) || (factors[0].base != 2);
    if (factors.size() == 2)
        return factors[0].base == 2 && factors[0].exponent == 1 && factors[1].base != 2;
    return false;
}

int Euler(int n, const vector<Number>& factors)
{
    for (const auto& f : factors)
        n = n / f.base * (f.base - 1);
    return n;
}

int cal(int n, int e_n) 
{
    auto n_factors = Decompose(e_n);
    vector<int> powerNum;
    for (const auto& f : n_factors)
        powerNum.push_back(e_n / f.base);

    for (int i = 2; i < n; ++i) 
    {
        bool is_primitive_root = true;
        for (int exp : powerNum) 
        {
            if (mod(i, exp, n) == 1)
            {
                is_primitive_root = false;
                break;
            }
        }
        if (is_primitive_root) return i;
    }
    return 0;
}

int main() 
{
    int N;
    cout << "Please input n(n>0): ";
    cin >> N;
    auto factors = Decompose(N);

    if (judge(factors))
    {
        int n = Euler(N, factors);
        int g = cal(N, n);
        cout << "The min primitive root of " << N << ": g=" << g << endl;
        vector<int> ind_map(N, -1);
        for (int r = 0; r < n; ++r)
        {
            int value = mod(g, r, N);
            if (value < N) ind_map[value] = r;
        }
        cout << "The ind_table of " << N << " based on g=" << g << " is:" << endl;
        int tens = N / 10;
        for (int i = 0; i <= tens + 1; i++)
        {
            for (int j = 0; j <= 10; j++)
            {
                if (i == 0 && j == 0)
                    cout << setw(5) << " ";
                else if (i * j == 0)
                    cout << setw(5) << i + j - 1;
                else
                {
                    int t = 10 * (i - 1) + j - 1;
                    if (t < N && ind_map[t] != -1)
                        cout << setw(5) << ind_map[t];
                    else
                        cout << setw(5) << "-";
                }
            }
            cout << endl;
        }
    }

    return 0;
}