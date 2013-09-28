#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <algorithm>

#define OK(a) cerr<<"OK at "<<a<<"!"<<endl; 

using namespace std;

inline int ScanInt(void) { 
    int r = 0, c, d; 
    while (!isdigit(c = getchar()) && c != '-'); 
    if (c != '-') r = c - '0'; d = c; 
    while ( isdigit(c = getchar())) r = r * 10 + c - '0'; 
    return d=='-'?-r:r; 
} 

const int MAXN = 100010;
const int inf = ~0U>>1;

struct Edge {
    int y, z; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data;

int d[MAXN], father[MAXN];

int f[18][MAXN], deep[MAXN];
int n, m;

struct Node {
    int l, r; Node *ch[2]; int cnt; long long sum;
}POOL_[3000000], *root[MAXN], *data_seg;

Node* Build(int l, int r) {
    Node *ret = data_seg++;
    ret->l = l, ret->r = r, ret->ch[0] = ret->ch[1] = 0; ret->cnt = ret->sum = 0;
    if (l == r) return ret;
    register int mid = (l + r) >> 1;
    ret->ch[0] = Build(l, mid);
    ret->ch[1] = Build(mid + 1, r);
    return ret;
}

Node* Insert(Node *now, int h) {
    Node* ret = data_seg++;
    *ret = *now;
    ret->cnt++; ret->sum += h;
    if (now->l == now->r) return ret;
    register int mid = (now->l + now->r) >> 1;
    if (h <= mid) {
        ret->ch[0] = Insert(now->ch[0], h);
    } else {
        ret->ch[1] = Insert(now->ch[1], h);
    }
    return ret;
}

int Cal_cnt(Node* X, Node *Y, Node *A, int limit) {
    if (X->l == X->r) {
        if (X->cnt + Y->cnt - A->cnt * 2 <= limit) return X->l + 1;
        else return X->l;
    }
    int t = X->ch[0]->cnt + Y->ch[0]->cnt - A->ch[0]->cnt * 2;
    if (t <= limit) return Cal_cnt(X->ch[1], Y->ch[1], A->ch[1], limit - t);
    else return Cal_cnt(X->ch[0], Y->ch[0], A->ch[0], limit);
}

long long Cal_sum(Node *X, Node *Y, Node *A, long long limit, long long d, long long left_sum, long long left_cnt) {
    if (X->l == X->r) {
        long long cnt = (X->cnt + Y->cnt - 2 * A->cnt + left_cnt);
        long long sum = (X->sum + Y->sum - 2 * A->sum + left_sum);
        long long tmp = (cnt) * X->l - sum;
        if (tmp * d > limit) return X->l - 1; else return X->l;
    }
    long long cnt = (X->ch[0]->cnt + Y->ch[0]->cnt - 2 * A->ch[0]->cnt + left_cnt);
    long long sum = (X->ch[0]->sum + Y->ch[0]->sum - 2 * A->ch[0]->sum + left_sum);
    int mid = (X->l + X->r) >> 1;
    long long tmp =  cnt * mid - sum;
    if (tmp * d > limit) return Cal_sum(X->ch[0], Y->ch[0], A->ch[0], limit, d, left_sum, left_cnt);
    else return Cal_sum(X->ch[1], Y->ch[1], A->ch[1], limit, d, sum, cnt);
}

int Cal(Node *X, int h) {
    if (X->l == X->r) {
        if (X->l <= h) return X->cnt; else return 0;
    }
    int mid = (X->l + X->r) >> 1;
    if (h <= mid) return Cal(X->ch[0], h); else return Cal(X->ch[1], h) + X->ch[0]->cnt;
}

long long CalS(Node *X, int h) {
    if (X->l == X->r) {
        if (X->l <= h) return X->sum; else return 0;
    }
    int mid = (X->l + X->r) >> 1;
    if (h <= mid) return CalS(X->ch[0], h); else return CalS(X->ch[1], h) + X->ch[0]->sum;
}

inline void GoUP(int &y, int d) {
    for (int j = 17; j >= 0; j--) if (d & (1 << j)) y = f[j][y];
}

inline int LCA(int x, int y) {
    if (deep[x] > deep[y]) swap(x, y);
    GoUP(y, deep[y] - deep[x]);
    if (x == y) return x;
    for (int j = 17; j >= 0; j--) if (f[j][x] != f[j][y]) {
        x = f[j][x];
        y = f[j][y];
    }
    return f[0][y];
}

inline void Bfs(void) {
    int head = 1, tail = 1; d[1] = 1; deep[1] = 0;
    while (head <= tail) {
        int now = d[head++];
        for (int k = 1; (1 << k) <= deep[now]; k++) f[k][now] = f[k - 1][f[k - 1][now]];
        for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
            d[++tail] = p->y;
            deep[p->y] = deep[now] + 1;
            f[0][p->y] = father[p->y] = now;
            root[p->y] = Insert(root[now], p->z);
        }
    }
}

inline void clear(void) {
    memset(f, 0, sizeof f); 
    memset(a, 0, sizeof a);
    memset(POOL, 0, sizeof POOL);
    data = POOL; data_seg = POOL_;
}

inline int getNum(int x, int y, int lca, int mid) {
    int C1 = Cal(root[x], mid);
    int C2 = Cal(root[y], mid);
    int C = Cal(root[lca], mid);
    return C1 + C2 - C * 2;
}

inline int getSum(int x, int y, int lca, int mid) {
    long long K1 = CalS(root[x], mid);
    long long K2 = CalS(root[y], mid);
    long long K = CalS(root[lca], mid);
    long long sum = K1 + K2 - 2ll * K;
    long long cnt = getNum(x, y, lca, mid);
    long long ret = (cnt * mid - sum);
    return ret;
}

inline int get1(int x, int y, int lca, int k) {
    int ret = Cal_cnt(root[x], root[y], root[lca], k);
    return ret;
}

inline long long get2(int x, int y, int lca, int k, int A, int money) {
    long long ret = Cal_sum(root[x], root[y], root[lca], money, A, 0, 0);
    return ret;
}

int main(void) {
  //  freopen("in", "r", stdin);
 //   freopen("out", "w", stdout);
    int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) { printf("Case #%d:\n", _);
        clear();
        scanf("%d%d", &n, &m);
        root[1] = Build(0, 10000);
        for (int i = 1;  i < n; i++) {
            int x = ScanInt(), y = ScanInt(), z = ScanInt(); Edge *tmp = a[x];
            a[x] = data++; a[x]->y = y; a[x]->z = z; a[x]->next = tmp;
            tmp = a[y];
            a[y] = data++; a[y]->y = x; a[y]->z = z; a[y]->next = tmp;
        }
        Bfs();
        for (int i = 1; i <= m; i++) {
            int x = ScanInt(), y = ScanInt();long long money = ScanInt(), B = ScanInt(), A = ScanInt();
            int k = B / A;
            int lca = LCA(x, y);
            long long c1 = get1(x, y, lca, k);
            long long c2 = get2(x, y, lca, k, A, money);
            if (money == 0) {
                printf(LL "\n", c2);
                continue;
            }
            long long c3 = get2(x, y, lca, k, A, 0);
            long long Ans = (money >= B ? (money - B ) / A + 1 : 0) + c3;
            long long fact = min(c1, c2);
            long long used = getSum(x, y, lca, fact);
            money -= used * A;
            Ans = max(Ans, fact + max(money / B, (money >= B ? (money - B) / A + 1 : 0)));
            printf(LL "\n", Ans);
        }
    }
    return 0;
}