#include <cstdio>
#define P 95041567
const int p[5] = {31, 37, 41, 43, 47};
const int q[5] = {55185426, 64217275, 39407479, 11051345, 20221610};
int b[5][300000], c[5][50][50];
int cal_b(int n, int k) {
    if (n < 300000) return b[k][n];
    int t = 0, u = n;
    for (; u >= p[k]; u /= p[k], t++);
    int v = u;
    for (int i = 0; i < t; i++) v *= p[k];
    v = n-v;
    int ans = 0;
    for (int i = u, j = 1; i >= 0; i--, j = (j*t)%p[k])
        ans = (ans + cal_b(v+i, k) * c[k][u][i] * j) % p[k];
    return ans;
}
int main() {
    for (int i = 0; i < 5; i++) {
        c[i][0][0] = 1;
        for (int j = 1; j < 50; j++) {
            c[i][j][0] = c[i][j][j] = 1;
            for (int k = 1; k < j; k++)
                c[i][j][k] = (c[i][j-1][k-1]+c[i][j-1][k])%p[i];
        }
    }
    for (int i = 0; i < 5; i++) {
        b[i][0] = b[i][1] = 1;
        for (int j = 2; j < p[i]; j++) {
            b[i][j] = 0;
            for (int k = 1; k <= j; k++)
                b[i][j] = (b[i][j] + b[i][j-k]*c[i][j-1][k-1]) % p[i];
        }
        for (int j = p[i]; j < 300000; j++)
            b[i][j] = (b[i][j-p[i]] + b[i][j-p[i]+1]) % p[i];
    }
    int T;
    for (scanf("%d", &T); T--; ) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for (int i = 0; i < 5; i++)
            ans = (ans + 1LL*q[i]*cal_b(n, i))%P;
        printf("%d\n", ans%P);
    }
    return 0;
}
