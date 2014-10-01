#include <cstdio>
#include <cmath>
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        int n, b, q; scanf("%d%d%d", &n, &b, &q);
        printf("Case #%d: ", _);
        if (q == 1) {
            bool flag = false;
            for (; b; b /= 10)
                if (n == b) flag = true;
            printf(flag ? "1.00000\n" : "0.00000\n");
        } else if (q == 10 || q == 100 || q == 1000) {
            bool flag = false;
            while (!(b%10)) b /= 10;
            for (int t = b; t; t /= 10)
                if (n == t) flag = true;
            for (; ; n /= 10) {
                if (n == b) flag = true;
                if (n % 10) break;
            }
            printf(flag ? "1.00000\n" : "0.00000\n");
        } else
            printf("%.5lf\n", log(1+1.0/n) / log(10));
    }
    return 0;
}
