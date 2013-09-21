#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

inline int ScanInt(void) { 
    int r = 0, c, d; 
    while (!isdigit(c = getchar()) && c != '-'); 
    if (c != '-') r = c - '0'; d = c; 
    while ( isdigit(c = getchar())) r = r * 10 + c - '0'; 
    return d=='-'?-r:r; 
} 

struct Node {
    int cnt; Node *ch[2];
    Node();
}Tnull, *null = &Tnull, *root[MAXN], POOL[3500000], *data = POOL;

Node::Node():cnt(0){ch[0] = ch[1] = null;}

int n, q;

Node *insert(Node *now, int p, int x) {
    Node *ret = data++; ret->cnt = 0; ret->ch[0] = ret->ch[1] = null;
    ret->cnt = now->cnt + 1; bool d = x & p;
    if (!p) return ret;
    ret->ch[d] = insert(now->ch[d], p >> 1, x);
    ret->ch[!d] = now->ch[!d];
    return ret;
}

struct Edge {
    int y, z; Edge *next;
}*a[MAXN], POOL_[MAXN << 1], *data_;

int f[20][MAXN], father[MAXN], deep[MAXN];

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

int value[MAXN], d[MAXN];

int L = 16;

inline void Bfs(void) {
    int head = 1, tail = 1; d[1] = 1; deep[1] = 0;
    root[1] = insert(root[0], 1 << L, value[1]);
    while (head <= tail) {
        int now = d[head++];
        for (int k = 1; (1 << k) <= deep[now]; k++) f[k][now] = f[k - 1][f[k - 1][now]];
        for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
            d[++tail] = p->y;
            deep[p->y] = deep[now] + 1;
            f[0][p->y] = father[p->y] = now;
            root[p->y] = insert(root[now], 1 << L, value[p->y]);
        }
    }
}

inline void clear(void) {
    memset(f, 0, sizeof f);
    memset(father, 0, sizeof father);
    memset(deep, 0, sizeof deep);
    memset(a, 0, sizeof a);
}

int main(void) {
    //freopen("in", "r", stdin);
    int n, m; while (scanf("%d%d", &n, &m) == 2) {
        data_ = POOL_; data = POOL;
        clear();
        for (int i = 1; i <= n; i++) value[i] = ScanInt(), root[i] = null; root[0] = null;
        for (int i = 1;  i < n; i++) {
            int x = ScanInt(), y = ScanInt(); Edge *tmp = a[x];
            a[x] = data_++; a[x]->y = y; a[x]->next = tmp;
            tmp = a[y];
            a[y] = data_++; a[y]->y = x; a[y]->next = tmp;
        }
        Bfs();
        for (int i = 1; i <= m; i++) {
            int x = ScanInt(), y = ScanInt(), z = ScanInt(); int last = 1;
            int A = LCA(x, y), Ans = 0; Node *X = root[x], *Y = root[y], *Z = root[A];
            for (int j = L; j >= 0; j--) {
                int dir = !((z >> j) & 1);
                int t = X->ch[dir]->cnt + Y->ch[dir]->cnt - 2 * Z ->ch[dir]->cnt + last * (((value[A] >> j) & 1) == dir);
                if (t > 0) {
                    Ans |= 1 << j;
                    X = X->ch[dir];
                    Y = Y->ch[dir];
                    Z = Z->ch[dir];
                } else {
                    X = X->ch[!dir];
                    Y = Y->ch[!dir];
                    Z = Z->ch[!dir];
                    dir = !dir;
                }
                if (dir != ((value[A] >> j) & 1)) last = 0;
            }
            printf("%d\n", Ans);
        }
    }
}

