#include <cstdio>
#include <cstring>
#define P 10000007
int a[12][12], b[12][12], n, m;
void mul(int a[12][12], int b[12][12]) {
    int c[12][12];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % P;
        }
    memcpy(a, c, sizeof c);
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(a, 0, sizeof a);
        a[0][0] = 1;
        for (int i = 1; i < n+2; i++) {
            a[i][0] = 3, a[i][1] = 10;
            for (int j = 2; j <= i; j++)
                a[i][j] = 1;
        }
        n += 2;
        memset(b, 0, sizeof b);
        for (int i = 0; i < n; i++)
            b[i][i] = 1;
        for (; m; m>>=1, mul(a, a))
            if (m & 1) mul(b, a);
        int ans = (b[n-1][0] + 23LL*b[n-1][1]) % P;
        for (int i = 2; i < n; i++) {
            int x; scanf("%d", &x);
            ans = (ans + 1LL*x*b[n-1][i]) % P;
        }
        printf("%d\n", ans);
    }
    return 0;
}
