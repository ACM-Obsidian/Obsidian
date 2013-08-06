#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main ()
{
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        double ans = 1.0;
        int p, n, k; scanf("%d %d %d", &p, &n, &k);
        for (int i = 0; i <= k; i++)
        {
            ans = ans * (p * (n - i)) / (p * (n - i) + 1);
        }
        printf("%.9f\n", ans);
    }
    return 0;
}
