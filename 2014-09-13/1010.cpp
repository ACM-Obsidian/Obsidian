#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 10010;

struct Edge {
    int y, c; Edge *next;
}*e[MAXN], POOL[MAXN << 3], *data = POOL;

inline void addEdge(int x, int y, int c) {
    Edge *tmp = data++;
    tmp->y = y; tmp->c = c; tmp->next = e[x]; e[x] = tmp;
    tmp = data++;
    tmp->y = x; tmp->c = c; tmp->next = e[y]; e[y] = tmp;
}

int n, m, s, t, N;
int vis[MAXN], u[MAXN];

double a[500][500], b[500][501], w[500];
std::queue<int> q;

void Dfs(int u) {
    vis[u] = N;
    for (Edge *p = e[u]; p; p = p->next) if (p->c == 0 && !vis[p->y]) Dfs(p->y);
}

int main(void) {
    int kase; scanf("%d", &kase); while (kase--) {
        data = POOL; N = 0; memset(vis, 0, sizeof vis); memset(a, 0, sizeof a); memset(b, 0, sizeof b); memset(u, 0, sizeof u); memset(e, 0, sizeof e);
        scanf("%d%d%d%d", &n, &m, &s, &t);
        for (int i = 1; i <= m; i++) {
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            addEdge(x, y, c);
        }
        for (int i = 1; i <= n; i++) if (!vis[i]) N++, Dfs(i);
        for (int i = 1; i <= n; i++) {
            for (Edge *p = e[i]; p; p = p->next) if (vis[i] != vis[p->y] && p->c == 1) {
                a[vis[i]][vis[p->y]]+=1;
            }
        }
        s = vis[s], t = vis[t];
        q.push(s), u[s] = 1;
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 1; i <= N; i++)
                if (a[t][i] > 0 && !u[i]) q.push(i), u[i] = 1;
        }
        if (s == t) puts("0.000000");
        else if (!u[t]) puts("inf");
        else {
            for (int i = 1; i <= N; i++) if (i != s && i != t && u[i])
                for (int j = 1; j <= N; j++)
                    if (i != j && u[j]) {
                        if (j == s) b[i][N+1] -= a[i][j];
                        else if (j == t) ;
                        else b[i][j] = a[i][j];
                        b[i][i] -= a[i][j];
                    }
            u[s] = u[t] = 0;
            for (int i = 1; i <= N; i++) if (u[i]) {
                double max = fabs(b[i][i]); int maxi = i;
                for (int j = i+1; j <= N; j++)
                    if (u[j] && fabs(b[j][i]) > max) max = fabs(b[j][i]), maxi = j;
                if (maxi != i)
                    for (int j = i; j <= N; j++)
                        std::swap(b[i][j], b[maxi][j]);
                for (int j = i+1; j <= N; j++) if (u[j])
                    for (int k = N+1; k >= i; k--)
                        b[j][k] -= b[j][i] / b[i][i] * b[i][k];
            }
            for (int i = N; i; i--) if (u[i]) {
                w[i] = b[i][N+1];
                for (int j = i+1; j <= N; j++)
                    if (u[j]) w[i] -= b[i][j] * w[j];
                w[i] /= b[i][i];
            }
            w[s] = 1, w[t] = 0;
            double e = 0;
            for (int i = 1; i <= N; i++)
                e += w[i] * a[i][t];
            printf("%.6lf\n", 1.0 / e);
        }
    }
    return 0;
}
