#include <cstdio>
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        int l, r; scanf("%d%d", &l, &r);
        long long s = 0;
        for (int i = l; i <= r; i++)
            s += 1LL * i * i * i;
        printf("Case #%d: %I64d\n", _, s);
    }
    return 0;
}
