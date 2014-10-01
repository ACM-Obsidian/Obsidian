#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAXN = 100010;
const int MAXM = 100010;

// string is 1-base, sa is 1-base
int w[MAXM];
inline void Sort(int a[], int ret[], int n, int m = MAXM - 1) {
    for (int i = 0; i <= m; i++) w[i] = 0;
    for (int i = 1; i <= n; i++) w[a[i]]++;
    for (int i = 1; i <= m; i++) w[i] += w[i - 1];
    for (int i = n; i >= 1; i--) ret[w[a[i]]--] = i;
}
int wa[MAXN], wb[MAXN], tmp[MAXN];
inline void getSA(int ch[], int sa[], int n) {
    int *x = wa, *y = wb;
    for (int i = 1; i <= n; i++) x[i] = ch[i];
    Sort(ch, sa, n);
    for (int j = 1, p = 1, m = MAXN - 1; p < n; m = p, j <<= 1) {
        p = 0;
        for (int i = n - j + 1; i <= n; i++) y[++p] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > j) y[++p] = sa[i] - j;
        for (int i = 1; i <= n; i++) tmp[i] = x[y[i]];
        Sort(tmp, sa, n, m);
        for (int i = 1; i <= n; i++) sa[i] = y[sa[i]];
        swap(x, y); x[sa[1]] = p = 1;
        for (int i = 2; i <= n; i++) {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p;
            else x[sa[i]] = ++p;
        }
    }
    sa[0] = n + 1; // for calculate height.
}
int rank[MAXN];
inline void getHeight(int ch[], int sa[], int height[], int n) {
    for (int i = 1; i <= n; i++) rank[sa[i]] = i;
    for (int i = 1, t = 0; i <= n; i++) {
        if (t > 0) t--;
        while (ch[i + t] == ch[sa[rank[i] - 1] + t]) t++;
        height[rank[i]] = t;
    }
}

char ch[MAXN]; int a[MAXN], n, sa[MAXN], height[MAXN];
long long sum[MAXN];

int f[20][MAXN], g[20][MAXN];

int main(void) {
    while (scanf("%s", ch + 1) == 1) {
        memset(sa, 0, sizeof sa); memset(height, 0, sizeof height); memset(rank, 0, sizeof rank); memset(a, 0, sizeof a);
        memset(wa, 0, sizeof wa); memset(wb, 0, sizeof wb); memset(tmp, 0, sizeof tmp); memset(w, 0, sizeof w);
        n = strlen(ch + 1);
        for (int i = 1; i <= n; i++) a[i] = ch[i]  - 'a' + 1;
        getSA(a, sa, n);
        getHeight(a, sa, height, n);
        for (int i = 1; i <= n; i++) f[0][i] = sa[i], g[0][i] = height[i];
        for (int i = 1; i < 20; i++)
            for (int j = 1; j <= n && j + (1 << i) - 1 <= n; j++)
                f[i][j] = min(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]),
                g[i][j] = min(g[i - 1][j], g[i - 1][j + (1 << (i - 1))]);

        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (n - sa[i] + 1ll) - height[i];
        int Ansl = 0, Ansr = 0, q; scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            long long v; scanf("%I64d", &v);
            long long k = (v ^ Ansl ^ Ansr) + 1;
            if (k > sum[n]) {Ansl = Ansr = 0; puts("0 0"); continue;}
            int l = 1, r = n;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (sum[mid] < k) l = mid + 1; else r = mid - 1;
            }
            long long len = k - sum[r] + height[l]; int next = l + 1;
            for (int k = 19; k >= 0; k--) if (next + (1 << k) - 1 <= n && g[k][next] >= len) {
                next += (1 << k);
            }
            next--;
            int lg = 0, dyf = next - l + 1; 
            while (dyf) lg++, dyf >>= 1; lg--;
            Ansl = min(f[lg][l], f[lg][next - (1 << lg) + 1]);
            Ansr = Ansl + len - 1;
            printf("%d %d\n", Ansl, Ansr);
        }
        memset(ch, 0, sizeof ch);
    }
    return 0;
}
