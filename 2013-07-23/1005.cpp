#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100010;
inline int lb (int a) { return a & (-a); }

typedef pair<int, int> pii;
#define X first
#define Y second

struct bit
{
    int arr[N];
    void clear ()
    {
        memset(arr, 0, sizeof arr);
    }
    void update (int a, int v)
    {
        while (a < N) arr[a] = max(arr[a], v), a += lb(a);
    }
    int query (int a)
    {
        int res = 0;
        while (a > 0) res = max(res, arr[a]), a -= lb(a);
        return res;
    }
};
bit fq, gq;

int arr[N], dpf[N], dpg[N], idx[N]; pii tmp[N];
int prev[N];

inline int bf (int a, int n)
{
    int l = 0, r = n;
    while (r - l > 1)
    {
        int mid = (l + r) >> 1;
        if (tmp[mid].X > a) r = mid;
        else l = mid;
    }
    return idx[l];
}

int maxg[N];

int main ()
{
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        int n; scanf("%d", &n); 
        for (int i = n - 1; i >= 0; i--)
        {
            scanf("%d", &arr[i]);
            tmp[i] = pii(arr[i], i);
        }
        sort(tmp, tmp + n); int mr = 1;
        for (int i = 0; i < n; i++)
        {
            if (i == 0 || tmp[i].X != tmp[i - 1].X) idx[i] = mr++;
            else idx[i] = idx[i - 1];
            if (i == 0) prev[tmp[i].Y] = -1;
            else if (tmp[i].X != tmp[i - 1].X) prev[tmp[i].Y] = tmp[i - 1].Y;
            else prev[tmp[i].Y] = prev[tmp[i - 1].Y];
        }
        for (int i = 0; i < n; i++) arr[i] = bf(arr[i], n);
        fq.clear(), gq.clear();
        for (int i = 0; i < n; i++)
        {
            int kk = mr - arr[i];
            dpf[i] = fq.query(kk) + 1;
            fq.update(kk, dpf[i]);
        }
        memset(maxg, 0, sizeof maxg);
        for (int i = 0; i < n; i++)
        {
            int kk = arr[i];
            dpg[i] = gq.query(kk) + 1;
            gq.update(kk, dpg[i]);
            maxg[arr[i]] = dpg[i];
        }
        for (int i = 1; i < mr; i++) maxg[i] = max(maxg[i], maxg[i - 1]);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dpf[i] + (arr[i] == 0 ? 0 : maxg[arr[i] - 1]));
            ans = max(ans, dpg[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}