#include <cstdio>
#include <cstring>
#include <algorithm>
struct segt {
    int n1, d1, n2, d2;
    int l, r;
    segt *lc, *rc;
} *T[200001], stack[10000000];
int n, top, l[100000], r[100000], v[100000], w[100000], s[100000][2], p[100000];
segt *build(int l, int r) {
    segt *T = &stack[top++];
    T->n1 = T->d1 = T->n2 = T->d2 = 0;
    T->l = l, T->r = r;
    if (l+1 < r) {
        int mid = l+r>>1;
        T->lc = build(l, mid), T->rc = build(mid, r);
    } else T->lc = T->rc = NULL;
    return T;
}
segt *update(segt *t, int k, int n1, int d1, int n2, int d2) {
    segt *T = &stack[top++];
    T->n1 = t->n1+n1, T->d1 = t->d1+d1, T->n2 = t->n2+n2, T->d2 = t->d2+d2;
    T->l = t->l, T->r = t->r;
    T->lc = t->lc, T->rc = t->rc;
    if (t->l+1 < t->r) {
        int mid = t->l+t->r>>1;
        if (k < mid) T->lc = update(t->lc, k, n1, d1, n2, d2);
        else T->rc = update(t->rc, k, n1, d1, n2, d2);
    }
    return T;
}
void query(segt *t, int l, int r, int &n1, int &d1, int &n2, int &d2) {
    if (l == r) return;
    if (t->l == l && t->r == r) n1 += t->n1, d1 += t->d1, n2 += t->n2, d2 += t->d2;
    else {
        int mid = t->l+t->r>>1;
        if (r <= mid) query(t->lc, l, r, n1, d1, n2, d2);
        else if (l >= mid) query(t->rc, l, r, n1, d1, n2, d2);
        else query(t->lc, l, mid, n1, d1, n2, d2), query(t->rc, mid, r, n1, d1, n2, d2);
    }
}
void dfs(int n, int &t) {
    if (n > 0) {
        l[n] = t;
        if (s[p[n]][0] == n)
            T[t] = update(T[t-1], w[p[n]], 0, 1, 0, 3);
        else
            T[t] = update(T[t-1], w[p[n]], 0, 1, 1, 3);
        t++;
    }
    if (s[n][0] != -1) dfs(s[n][0], t), dfs(s[n][1], t);
    if (n > 0) {
        r[n] = t;
        if (s[p[n]][0] == n)
            T[t] = update(T[t-1], w[p[n]], 0, -1, 0, -3);
        else
            T[t] = update(T[t-1], w[p[n]], 0, -1, -1, -3);
        t++;
    }
}
void solve() {
    top = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]), w[i] = v[i];
    std::sort(v, v+n); int m = std::unique(v, v+n) - v;
    for (int i = 0; i < n; i++) w[i] = std::lower_bound(v, v+m, w[i]) - v;
    memset(p, -1, sizeof p);
    memset(s, -1, sizeof s);
    int q; scanf("%d", &q);
    for (int i = 0, u, a, b; i < q; i++)
        scanf("%d%d%d", &u, &a, &b), u--, a--, b--, s[u][0] = a, s[u][1] = b, p[a] = p[b] = u;
    int t = 1;
    T[0] = build(0, m);
    dfs(0, t);
    for (scanf("%d", &q); q--; ) {
        int u, x;
        scanf("%d%d", &u, &x), u--;
        if (u == 0) {
            puts("0 0");
            continue;
        }
        int n1=0, d1=0, n2=0, d2=0, x_ = std::lower_bound(v, v+m, x) - v;
        if (x_ < m && v[x_] == x) {
            query(T[l[u]], x_, x_+1, n1, d1, n2, d2);
            if (d1 > 0) {
                puts("0");
                continue;
            }
            n1=d1=n2=d2=0;
        }
        query(T[l[u]], 0, x_, n1, d1, n2, d2);
        int n1_=0, d1_=0, n2_=0, d2_=0;
        query(T[l[u]], x_, m, n1_, d1_, n2_, d2_);
        printf("%d %d\n", n2+n1_, d2+d1_);
    }
}
int main() {
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}