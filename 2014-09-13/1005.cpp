#include <cstdio>
#include <vector>
#include <cstring>
long double a[50][50], b[50][50], c[50][50];
int n, m, d;
std::vector<int> g[50];
void mul(long double a[50][50], long double b[50][50]) {
    long double c[50][50];
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 50; k++)
                c[i][j] += b[i][k]*a[k][j];
        }
    memcpy(a, c, sizeof c);
}
void solve() {
    scanf("%d%d%d", &n, &m, &d);
    for (int i = 0; i < n; i++) g[i].clear();
    for (int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y), x--, y--;
        g[x].push_back(y), g[y].push_back(x);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) c[j][i] = 0;
        for (int j = 0; j < g[i].size(); j++)
            c[g[i][j]][i] = 1.0L / g[i].size();
    }
    for (int i = 0; i < n; i++) {
        memcpy(a, c, sizeof a);
        for (int j = 0; j < n; j++) a[i][j] = 0;
        memset(b, 0, sizeof b);
        for (int j = 0; j < n; j++) b[j][j] = 1;
        for (int t = d; t; t>>=1, mul(a, a))
            if (t & 1) mul(b, a);
        long double p = 0;
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (k != i)
                    p += b[j][k];
        p /= n;
        printf("%.8lf\n", (double)p);
    }
}
int main() {
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}
