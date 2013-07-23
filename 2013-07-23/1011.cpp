#include <cstdio>
#include <cmath>
#include <algorithm>
int n, k, a[1000], b[1000], c[1000], tmp[1000], e[4];
int issqr(int x) {
    int t = sqrt(x)+0.5;
    return t*t == x;
}
int prime(int x) {
    if (x == 1) return 0;
    for (int j = 2; j*j <= x; j++)
        if (!(x%j)) return 0;
    return 1;
}
int cmp(int x, int y) {
    return c[x] > c[y];
}
void solve() {
    scanf("%d%d", &n, &k);
    for (int i = 0, x; i < n; i++) {
        scanf("%d%d", &x, &b[i]);
        a[i] = c[i] = 0;
        if (x > 1) {
            int f=1, d=2, s=x+1;
            for (int j = 2; j*j <= x; j++)
                if (!(x%j)) {
                    f = 0;
                    d++, s += j;
                    if (j*j < x) d++, s += x/j;
                }
            if (f) a[i] |= 1, c[i]++;
            if (prime(d)) a[i] |= 2, c[i]++;
            if (prime(s)) a[i] |= 4, c[i]++;
            if (!(d&3) || !(d&1) && issqr(x) || d&1 && issqr(x) && issqr(sqrt(x)+0.5)) a[i] |= 8, c[i]++;
        } else a[i] = 8, c[i] = 1;
        printf(i?" %d":"%d", c[i]);
    }
    puts("");
    scanf("%d%d%d%d", &e[0], &e[1], &e[2], &e[3]);
    int max = -1000000000;
    for (int i = 0; i < 16; i++) {
        int l = 0, ex = 0;
        for (int j = 0; j < n; j++)
            if ((a[j] & i) == a[j]) tmp[l++] = j;
        for (int j = 0; j < 4; j++)
            if (!(i&1<<j)) ex += e[j];
        std::sort(tmp, tmp+l, cmp);
        for (int t = k>3?k-3:0; t <= k; t++) {
            int cnt = 0, sum = 0, mask = 0, j = 0, flag = 1;
            if (t) {
                for (; j < l; j++) {
                    mask |= a[tmp[j]];
                    if (cnt + b[tmp[j]] >= t) {
                        sum += (t-cnt) * c[tmp[j]];
                        break;
                    } else {
                        sum += b[tmp[j]] * c[tmp[j]];
                        cnt += b[tmp[j]];
                    }
                }
                if (j == l) flag = 0;
            }
            for (int p = t; p < k && flag; p++) {
                for (; j < l; j++)
                    if ((a[tmp[j]] & mask) != a[tmp[j]]) {
                        mask |= a[tmp[j]];
                        sum += c[tmp[j]];
                        break;
                    }
                if (j == l) flag = 0;
            }
            if (flag && mask == i && ex + sum > max)
                max = ex + sum;
        }
    }
    printf("%d\n", max);
}
int main() {
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}