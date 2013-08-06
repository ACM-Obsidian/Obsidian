#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxn = 110;
const int mi = 1993111700;
int mat[maxn][maxn], tmat[maxn][maxn], dis[maxn], v[maxn];
bool sch[maxn];
int ufs[maxn]; bool cut[maxn];
int uq (int a)
{
    return ufs[a] == a ? a : (ufs[a] = uq(ufs[a]));
}
int ans, tot;
int stoer_wagner (int n)
{
    int res = mi;
    for (int i = 0; i < tot; i++) ufs[i] = i;
    while (n > 1)
    {
        int maxp = 1, prev = 0;
        for (int i = 1; i < n; i++)
        {
            dis[v[i]] = mat[v[0]][v[i]];
            if (dis[v[i]] > dis[v[maxp]]) maxp = i;
        }
        memset(sch, false, sizeof sch);
        sch[v[0]] = true;
        for (int i = 1; i < n - 1; i++)
        {
            sch[v[maxp]] = true;
            prev = maxp, maxp = -1;
            for (int i = 0; i < n; i++) if (!sch[v[i]])
            {
                dis[v[i]] += mat[v[prev]][v[i]];
                if (maxp == -1 || dis[v[i]] > dis[v[maxp]]) maxp = i;
            }
        }
        if (dis[v[maxp]] < res)
        {
            res = dis[v[maxp]];
            for (int i = 0; i < tot; i++)
            {
                cut[i] = (uq(i) == uq(v[maxp]));    
            }
        }
        for (int i = 0; i < n; i++)
        {
            mat[v[prev]][v[i]] += mat[v[maxp]][v[i]];
            mat[v[i]][v[prev]] = mat[v[prev]][v[i]];
        }
        ufs[uq(v[maxp])] = uq(v[prev]);
        v[maxp] = v[--n];
    }
    return res;
}
bool togo[maxn];
void calc (int k)
{
    int n = 0;
    for (int i = 0; i < tot; i++)
    {
        if (togo[i]) v[n++] = i;
    }
    memcpy(mat, tmat, sizeof mat);
    int cutc = stoer_wagner(n);
    if (cutc < k)
    {
        char tt[maxn];
        for (int i = 0; i < tot; i++)
        {
            if (!togo[i]) tt[i] = 0;
            else if (cut[i]) tt[i] = 1;
            else tt[i] = 2;
        }
        for (int i = 1; i <= 2; i++)
        {
            for (int j = 0; j < tot; j++) togo[j] = (tt[j] == i);
            calc(k);
        }
    }
    else ++ans;
}
int main ()
{
    int n, m, k; while (scanf("%d %d %d", &n, &m, &k) == 3)
    {
        tot = n;
        memset(mat, 0, sizeof mat);
        for (int i = 0; i < m; i++)
        {
            int x, y, z; scanf("%d %d", &x, &y); --x, --y;
            mat[x][y] += 1;
            mat[y][x] += 1;
        }
        memcpy(tmat, mat, sizeof mat);
        for (int i = 0; i < n; i++) togo[i] = true;
        ans = 0;
        calc(k);
        printf("%d\n", ans);
    }
    return 0;
}
