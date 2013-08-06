#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int prime[15], pmr;
int phi (int a)
{
    int res = a; pmr = 0;
    for (int i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            res = res / i * (i - 1);
            prime[pmr++] = i;
            while (a % i == 0) a /= i;
        } 
    }
    if (a > 1)
    {
        res = res / a * (a - 1);
        prime[pmr++] = a;
    }
    return res;
}

int gcd (int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main ()
{
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        int n; scanf("%d", &n);
        if (n % 2 == 0) printf("0\n");
        else
        {
            int b = (n + 3) / 2;
            int tt = phi(b);
            if (b % 3 == 0) printf("0\n");
            else
            {
                int c = 0;
                int mx = b / 3;
                for (int i = 0; i < (1 << pmr); i++)
                {
                    int q = 1, r = 1;
                    for (int j = 0; j < pmr; j++) if (i & (1 << j))
                    {
                        q *= -1, r *= prime[j];
                    }
                    c += q * (mx / r);
                }
                printf("%d\n", tt - c * 2);
            }
        }
    }
    return 0;
}

