#include <cstdio>
int ans[7];
int main() {
    int m, n, t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d%d", &m, &n);
        for (int i = 0; i < 7; i++) ans[i] = 0;
        ans[0] = 1;
        for (int i = 1; i < n; i++)
            for (int j = 0, s, g = 0; j < 7; j++)
                s = ans[j]*m+g, ans[j] = s%10000, g = s/10000;
        int i = n;
        for (; i > 1; i--)
            if (!(n%i)) {
                int g = 0;
                for (int j = 6; j >= 0; j--)
                    g = (g*10000+ans[j])%i;
                if (g == 0) break;
            }
        for (int j = 6, s, g = 0; j >= 0; j--)
            s = g*10000+ans[j], ans[j] = s/i, g = s%i;
        printf("%d/", n/i);
        int j = 6;
        for (; j; j--)
            if (ans[j]) break;
        printf("%d", ans[j]);
        for (j--; j >= 0; j--) {
            if (ans[j] < 10) putchar(48);
            if (ans[j] < 100) putchar(48);
            if (ans[j] < 1000) putchar(48);
            printf("%d", ans[j]);
        }
        puts("");
    }
    return 0;
}
