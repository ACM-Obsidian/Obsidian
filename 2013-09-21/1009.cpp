#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#pragma GCC optimize("O2")

typedef long long Int64;

inline int ScanInt(void) { 
    int r = 0, c; 
    while (!isdigit(c = getchar())); 
    r = c - '0'; 
    while ( isdigit(c = getchar())) r = r * 10 + c - '0'; 
    return r; 
} 

const int MAXN = 1010, inf = ~0U>>1;

struct Point {
    int x, y;
}c[MAXN];

struct Pair {
    int x, y; Int64 z; bool in;
    inline friend bool operator <(const Pair& a, const Pair& b) {
        return a.z < b.z;
    }
}E[MAXN * MAXN]; int top = 0;

struct Edge {
    int y; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data;

Int64 Dis[MAXN][MAXN];

inline Int64 dis2(const Point& a, const Point& b) {
    return (Int64) (a.x - b.x) * (a.x - b.x) + (Int64) (a.y - b.y) * (a.y - b.y);
}

int n, f[MAXN], father[MAXN], deep[MAXN];

inline int get(int x) {return x == f[x] ? x : (f[x] = get(f[x]));}

inline void Dfs(int u) {
    for (Edge *p = a[u]; p; p = p->next) if (p->y != father[u]) {
        father[p->y] = u;
        deep[p->y] = deep[u] + 1;
        Dfs(p->y);
    }
}

double Ans = 0, Sum = 0;

inline void MST(void) {
    for (int i = 1; i <= n; i++) f[i] = i;
    sort(E + 1, E + top + 1);
    for (int i = 1; i <= top; i++) {
        int x = E[i].x, y =  E[i].y;
        if (get(x) != get(y)) {
            E[i].in = true;
            f[get(x)] = y;
            Edge *tmp = a[x]; a[x] = data++; a[x]->y = y; a[x]->next = tmp;
            tmp = a[y]; a[y] = data++; a[y]->y = x; a[y]->next = tmp;
            Sum += sqrt(Dis[x][y]);
        }
    }
}

bool vis[MAXN]; int LCA[MAXN][MAXN];

inline void getLCA(void) {
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t) vis[t] = true, t = father[t];
        for (int j = i; j <= n; j++) {
            int u = j;
            while (!vis[u]) u = father[u];
            LCA[i][j] = LCA[j][i] = u;
        }
        t = i;
        while (t) vis[t] = false, t = father[t];
    }
}

Int64 color[MAXN];

inline void Color(int x, int A, Int64 cur) {
    while (deep[x = get(x)] > deep[A]) {
        color[x] = cur;
        f[x] = father[x];
    }
}

inline void clear(void) {
    top = 0, Ans = 0, Sum = 0;
    data = POOL;
    memset(a, 0, sizeof a);
    memset(father, 0, sizeof father);
    memset(color, 0, sizeof color);
    memset(deep, 0, sizeof deep);
}

int main(void) {
    //freopen("in", "r", stdin);
    int kase; scanf("%d", &kase); while (kase--) {
        clear();
        n = ScanInt(); int k = ScanInt();
        for (int i = 1; i <= n; i++) c[i].x = ScanInt(), c[i].y = ScanInt();
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                Dis[i][j] = Dis[j][i] = dis2(c[i], c[j]);
                E[++top].x = i, E[top].y = j; E[top].z = Dis[i][j], E[top].in = false;
            }
        }
        MST();
        for (int i = 1; i <= n; i++) f[i] = i;
        Dfs(1);
        getLCA();
        for (int i = 1; i <= top; i++) if (!E[i].in) {
            int A = LCA[E[i].x][E[i].y];
            Color(E[i].x, A, E[i].z);
            Color(E[i].y, A, E[i].z);
        }
        for (int i = 2; i <= n; i++) if (color[i] > 0 && father[i] != 1) {
            double t1 = sqrt(Dis[i][father[i]]);
            double t2 = sqrt(color[i]);
            Ans = max(Ans, t2 - t1);
        }
        printf("%.2lf\n", (Sum + Ans) * k);
    }
    return 0;
}

