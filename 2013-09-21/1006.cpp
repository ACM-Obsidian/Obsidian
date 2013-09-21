#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

inline int query (int a, int b)
{
    if (a > b) swap(a, b);
    if (b - a == 1)
    {
        if (a <= 3) return a - 1;
        else if (a <= 7) return a - 2;
        else if (a <= 11) return a - 3;
        return a - 4;
    }
    else
    {
        return a + 11;
    }
}
int square[9];

inline int frm (int s, int ts)
{
    int score = 0;
    for (int j = 0; j < 9; j++)
    {
        if ((square[j] & s) != square[j] && (square[j] & ts) == square[j])
            ++score;
    }
    return score;
}

map<int, int> dfs;

int calc (int cs)
{
    if (cs == (1 << 24) - 1)
    {
        dfs[cs] = 0;
        return 0;
    }
    else if (dfs.find(cs) != dfs.end())
    {
        return dfs[cs];
    }
    int res;
    int tt = (__builtin_popcount(cs) & 1);
    if (tt == 0) res = -100;
    else res = 100;
    for (int i = 0; i < 24; i++) if ((cs & (1 << i)) == 0)
    {
       int tcs = cs | (1 << i);
       int tscore = frm(cs, tcs) * (tt ? -1 : 1) + calc(tcs);
       if (tt == 0) res = max(res, tscore);
       else res = min(res, tscore);
    }
    return dfs[cs] = res;
}

int main ()
{
    int sqmr = 0;
    for (int i = 1; i <= 11; i++)
    {
        if (i == 4 || i == 8) continue;
        int s = (1 << query(i, i + 1)) | (1 << query(i, i + 4)) | (1 << query(i + 1, i + 5)) | (1 << query(i + 4, i + 5));
        square[sqmr++] = s;
    }
    int kase, _ = 1; for (scanf("%d", &kase); _ <= kase; ++_)
    {
        int n; scanf("%d", &n);
        int s = 0, score = 0;
        for (int i = 0; i < n; i++)
        {
            int x, y; scanf("%d %d", &x, &y);
            int ts = (s | (1 << query(x, y)));
            score += frm(s, ts) * (i & 1 ? -1 : 1);
            s = ts;
        }
        dfs.clear();
        int add = calc(s);
        printf("Case #%d: %s\n", _, add + score > 0 ? "Tom200" : "Jerry404");
    }
    return 0;
}

