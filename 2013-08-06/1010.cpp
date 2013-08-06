#include <cstdio>
#include <cmath>
int main() {
    int T;
    for (scanf("%d", &T); T--; ) {
        int k, m, n;
        scanf("%d%d%d", &k, &n, &m);
        long double ans = 0;
        if (k == 0) {
            long double t = 1;
            for (int i = 0; i < m; i++, t *= n) ans += t;
        } else {
            long double t = 0, u = 0, f = 0, g = 0;
            for (int i = 1; i < m; t += log(n), u += log(n-m+i), i++)
                f += (m-i)*exp(u-t)/n, g += exp(u-t);
            ans = (1-f+g)/(1-f);
        }
        printf("%.10lf\n", (double) ans);
    }
    return 0;
}
