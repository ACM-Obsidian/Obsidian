#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long LL;
const int mod = 1000000007;
int pwr (int a, int b)
{
    int ans = 1, t = a;
    while (b)
    {
        if (b & 1) ans = (LL)ans * t % mod;
        t = (LL)t * t % mod;
        b >>= 1;
    }
    return ans;
}

int main ()
{
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        int n, k; scanf("%d %d", &n, &k);
        if (k > n) printf("0\n");
        else if (k == n) printf("1\n");
        else if (k == n - 1) printf("2\n");
        else
        {
            int ans = pwr(2, n - k - 2);
            ans = (LL)ans * (n - k - 1) % mod;
            ans = (ans + pwr(2, n - k)) % mod;
            printf("%d\n", ans);
        }
    }
    return 0;
}