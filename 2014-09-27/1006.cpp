#include <cstdio>
#include <cstring>
int a[10], b[10], c[10];
void add(int *a, int b, int *c) {
    for (int i = 0, s, g = b; i < 10; i++)
        s = a[i] + g, c[i] = s % 10000, g = s / 10000;
}
void sub(int *a, int b, int *c) {
    for (int i = 0, s, g = b; i < 10; i++)
        s = a[i] - g, c[i] = (s % 10000 + 10000) % 10000, g = (c[i] - s) / 10000;
}
void mul(int *a, int t, int *b) {
    for (int i = 0, s, g = 0; i < 10; i++)
        s = a[i] * t + g, b[i] = s % 10000, g = s / 10000;
}
void mul(int *a, int *b, int *c) {
    for (int i = 0; i < 10; i++)
        c[i] = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0, s, g = 0; j < 10; j++)
            s = a[i] * b[j] + c[i+j] + g, c[i+j] = s % 10000, g = s / 10000;
}
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        long long x; scanf("%I64d", &x);
        printf("Case #%d: ", _);
        if (x == 0) puts("1");
        else if (x == 1) puts("2");
        else {
            for (int i = 0; x; x /= 10000, i++)
                a[i] = x % 10000, b[i] = a[i];
            mul(a, 8, a);
            sub(a, 7, a);
            mul(a, b, c);
            memcpy(a, c, sizeof a);
            add(a, 1, a);
            int i = 9; while (!a[i]) i--;
            printf("%d", a[i]);
            for (i--; i >= 0; i--) printf("%04d", a[i]);
            puts("");
        }
    }
    return 0;
}
