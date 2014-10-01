#include <cstdio>
#include <cstring>
#include <cmath>
long double f[16][17][17], g[16][17][17];
long double pr[16][16], h[16][16];
int n, m;
int main() {
    while (scanf("%d%d", &m, &n) != EOF) {
        for (int i = 0; i < m; i++) {
            pr[i][0] = 1;
            double t; scanf("%lf", &t), pr[i][1] = t;
            for (int j = 2; j < n; j++)
                pr[i][j] = pr[i][j-1] * pr[i][1];
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                double t; scanf("%lf", &t), h[i][j] = t;
            }
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        long double ans = 0;
        for (int j = 1; j < n; j++) {
            f[j][0][0] = 1;
            for (int k = 0; k < m; k++)
                for (int p = m; p >= 0; p--)
                    for (int q = p; q >= 0; q--) {
                        f[j][p][q] *= 1 - pr[k][j-1];
                        if (p > 0) f[j][p][q] += f[j][p-1][q] * pr[k][j-1] * (1-pr[k][1]);
                        if (p > 0 && q > 0) f[j][p][q] += f[j][p-1][q-1] * pr[k][j];
                        g[j][p][q] *= 1 - pr[k][j-1];
                        if (p > 0) g[j][p][q] += g[j][p-1][q] * pr[k][j-1] * (1-pr[k][1]);
                        if (p > 0 && q > 0) g[j][p][q] += g[j][p-1][q-1] * pr[k][j]
                            + f[j][p-1][q-1] * pr[k][j] * h[k][j];
                    }
            for (int p = 1; p <= m; p++)
                for (int q = 1; q <= p; q++)
                    ans += g[j][p][q] * ((double)q / p + 1);
        }
        for (int i = 0; i < m; i++)
            ans += h[i][0];
        printf("%.8lf\n", (double)ans);
    }
    return 0;
}
