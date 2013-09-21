#include <cstdio>
#include <cstring>
int h[101][101][202][4], a[202][2], k, f[202], e[202], q[202];
char s[101];
inline void add(int &a, int b) {
    a += b;
    if (a >= 1000000007) a -= 1000000007;
}
void solve() {
    int m, n;
    memset(e, 0, sizeof e);
    scanf("%d%d\n", &m, &n);
    k = 1;
    a[0][0] = a[0][1] = -1;
    for (int i = 0; i < 2; i++) {
        gets(s);
        int l = strlen(s), p = 0;
        for (int j = 0; j < l; j++)
            if (a[p][s[j]=='D'] == -1) {
                a[p][s[j]=='D'] = k;
                a[k][0] = a[k][1] = -1;
                p = k++;
            } else p = a[p][s[j]=='D'];
        e[p] |= 1 << i;
    }
    int l = 0, r = 1; q[0] = 0; f[0] = -1;
    for (; l < r; l++)
        for (int i = 0; i < 2; i++)
            if (a[q[l]][i] == -1) {
                int p = f[q[l]];
                for (; p != -1; p = f[p])
                    if (a[p][i] != -1) break;
                if (p != -1) a[q[l]][i] = a[p][i];
                else a[q[l]][i] = 0;
            } else {
                int p = f[q[l]];
                for (; p != -1; p = f[p])
                    if (a[p][i] != -1) break;
                if (p != -1) {
                    f[a[q[l]][i]] = a[p][i];
                    e[a[q[l]][i]] |= e[a[p][i]];
                } else
                    f[a[q[l]][i]] = 0;
                q[r++] = a[q[l]][i];
            }
    int ans = 0;
    h[0][0][0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int t = 0; t < k; t++)
                for (int u = 0; u < 4; u++) if (h[i][j][t][u]) {
                    if (i < n || j < m) {
                        if (i < n) add(h[i+1][j][a[t][1]][u|e[a[t][1]]], h[i][j][t][u]);
                        if (j < m) add(h[i][j+1][a[t][0]][u|e[a[t][0]]], h[i][j][t][u]);
                    }
                    else if (u == 3)
                        add(ans, h[i][j][t][u]);
                    h[i][j][t][u] = 0;
                }
    printf("%d\n", ans);
}
int main() {
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}

