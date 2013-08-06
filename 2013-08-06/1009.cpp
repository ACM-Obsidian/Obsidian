#include <cstdio>
#define P 1000000007
int p[100001];
int main() {
    p[0] = p[1] = 1, p[2] = 2;
    for (int i = 3; i <= 100000; i++) {
        p[i] = 0;
        for (int j = 1, s = 1; j*(3*j-1)/2 <= i; j++, s = -s) {
            if (j*(3*j+1)/2 <= i) p[i] = (p[i] + s * p[i-j*(3*j+1)/2]) % P;
            p[i] = (p[i] + s * p[i-j*(3*j-1)/2]) % P;
        }
        if (p[i] < 0) p[i] += P;
    }
    int T;
    for (scanf("%d", &T); T--; ) {
        int x;
        scanf("%d", &x);
        printf("%d\n", p[x]);
    }
    return 0;
}
