#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 10010, M = 1000010;
typedef pair<int, int> pii;
typedef pair<int, pii> ppi;
#define X first
#define Y second

int ufs[N], cnt[N];
int uq (int a)
{
    return a == ufs[a] ? a : (ufs[a] = uq(ufs[a]));
}
ppi edge[M];
long long ans[M];

int main ()
{
    int n, m;
    while (scanf("%d %d", &n, &m) == 2)
    {
        for (int i = 0; i < n; i++) ufs[i] = i, cnt[i] = 1;
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d %d", &edge[i].Y.X, &edge[i].Y.Y, &edge[i].X);
        }
        sort(edge, edge + m);
        long long ls = 0;
        for (int i = 0; i < m; i++)
        {
            int ta = uq(edge[i].Y.X), tb = uq(edge[i].Y.Y);
            if (ta != tb)
            {
                ls += 2LL * cnt[ta] * cnt[tb];
                ufs[ta] = tb;
                cnt[tb] += cnt[ta];
            }
            ans[i] = ls;
        }
        long long mm = (long long)n * (n - 1);
        int q; scanf("%d", &q);
        for (int i = 0; i < q; i++)
        {
            int x; scanf("%d", &x); --x;
            int l = -1, r = m;
            while (r - l > 1)
            {
                int mid = (l + r) >> 1;
                if (edge[mid].X <= x) l = mid;
                else r = mid;
            }
            printf("%I64d\n", mm - (l == -1 ? 0 : ans[l]));
        }
    }
    return 0;
}

