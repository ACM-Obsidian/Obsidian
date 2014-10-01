#include <cstdio>
#include <vector>
#define N 200000
#pragma GCC optimize("O3")
#pragma comment (linker, "/STACK:1024000000,1024000000")
int l[N], r[N], l1[N], r1[N], u[N], d[N], p[N][18], t;
long long a[2*N+1], b[2*N+1];
std::vector<std::pair<int, int> > g[N];
void dfs(int n) {
    l[n] = t++, u[n] = 1;
    for (int i = 0; i < g[n].size(); i++)
        if (!u[g[n][i].first]) {
            l1[g[n][i].second] = t;
            int x = g[n][i].first;
            d[x] = d[n]+1;
            p[x][0] = n;
            for (int j = 1; p[x][j-1] != -1 && j < 18; j++)
                p[x][j] = p[p[x][j-1]][j-1];
            dfs(x);
            r1[g[n][i].second] = t-1;
        }
    r[n] = t++;
}
inline void parent(int &u, int d) {
    for (int i = 0; d; d>>=1, i++)
        if (d&1) u = p[u][i];
}
inline int lca(int u, int v) {
    if (d[u] < d[v]) parent(v, d[v] - d[u]); else if (d[u] > d[v]) parent(u, d[u] - d[v]);
    if (u == v) return u;
    for (int i = 17; i >= 0; i--)
        if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    return p[u][0];
}
int getint() {
    int s = 0, f = 0;
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') f = 1, ch = getchar();
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return f ? -s : s;
}
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        memset(p, -1, sizeof p);
        int n, m; n = getint(), m = getint();
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 0; i < n-1; i++) {
            int x, y; x = getint(), y = getint(), x--, y--;
            g[x].push_back(std::make_pair(y, i)), g[y].push_back(std::make_pair(x, i));
        }
        t = 0;
        memset(u, 0, sizeof u);
        dfs(0);
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        char op[6];
        for (int i = 0; i < m; i++) {
            int u, v, w;
            char ch; while (ch != 'A') ch = getchar();
            getchar(), getchar(), ch = getchar();
            u = getint(), v = getint(), w = getint(), u--, v--;
            int p = lca(u, v);
            if (ch == '1') {
                a[l[u]+1] -= w;
                a[l[v]+1] -= w;
                a[l[p]] += w, a[l[p]+1] += w;
            } else {
                b[l[u]+1] -= w;
                b[l[v]+1] -= w;
                b[l[p]+1] += 2*w;
            }
        }
        for (int i = 1; i < 2*n; i++) a[i] += a[i-1];
        for (int i = 1; i < 2*n; i++) b[i] += b[i-1];
        printf("Case #%d:\n", _);
        for (int i = 0; i < n; i++) printf("%I64d%c", a[l[i]]-a[r[i]], " \n"[i == n-1]);
        if (n == 1) puts("");
        else for (int i = 0; i < n-1; i++) printf("%I64d%c", b[l1[i]]-b[r1[i]], " \n"[i == n-2]);
    }
    return 0;
}
