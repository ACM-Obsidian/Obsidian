#include <cstdio>
#include <cstring>
#include <algorithm>
double f[1001][1024];
double p[1000][10];
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%lf", &p[j][i]);
        memset(f, 0xcd, sizeof f);
        f[0][0] = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < 1<<n; j++)
                if (f[i][j] >= 0)
                    for (int k = 0; k < n; k++)
                        if (!(j&1<<k)) {
                            int t = j|1<<k; if (t == (1<<n)-1) t = 0;
                            if (f[i][j] + p[i][k] > f[i+1][t])
                                f[i+1][t] = f[i][j] + p[i][k];
                        }
        double ans = 0;
        for (int i = 0; i < 1<<n; i++)
            if (f[m][i] > ans) ans = f[m][i];
        printf("Case #%d: %.5lf\n", _, ans);
    }
    return 0;
}
