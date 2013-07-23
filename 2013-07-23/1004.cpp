#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>
#include <functional>

using namespace std;

inline int ScanInt(void) {
    int r = 0, c, d;
    while (!isdigit(c = getchar()) && c != '-');
    if (c != '-') r = c - '0'; d = c;
    while ( isdigit(c = getchar())) r = r * 10 + c - '0';
    return d=='-'?-r:r;
}

const int MAXN = 100010;
const int inf = 2000000000;

struct Edge {
    int y, c; Edge *next; 
}*a[MAXN], POOL[MAXN << 1], *data;

int n, m;

int d[MAXN], deep[MAXN];

int f[18][MAXN], sum[MAXN], fs[MAXN];

inline int goUp(int y ,int d) {
    for (int i = 0; i <= 17; i++) if (d & (1 << i)) y = f[i][y];
    return y;
}

inline int LCA(int x, int y) {
    if (deep[x] > deep[y]) swap(x, y);
    y = goUp(y, deep[y] - deep[x]);
    if (x == y) return x;
    while (f[0][x] != f[0][y]) {
        for (int i = 17; i >= 0; i--) if (f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
    }
    return f[0][x];
}

inline void cl(void) {
    memset(deep, -1, sizeof deep); memset(sum, 0, sizeof sum); memset(fs, 0, sizeof fs);
    memset(a, 0, sizeof a); memset(f, 0, sizeof f);
}

inline void Bfs(void) {
    int head = 1, tail = 1;
    d[1] = 1; deep[1] = 0;
    while (head <= tail) {
        int now = d[head++];
        for (int i = 1; (1 << i) <= deep[now]; i++) f[i][now] = f[i - 1][f[i - 1][now]];
        for (Edge *p = a[now]; p; p = p->next) if (deep[p->y] == -1) {
            deep[p->y] = deep[now] + 1;
            f[0][p->y] = now; sum[now] += p->c; fs[p->y] = p->c;
            d[++tail] = p->y;
        }
    }
    for (int i = n; i >= 1; i--) sum[f[0][d[i]]] += sum[d[i]];
}

vector<int> c[2][MAXN], _tmp[MAXN];

inline void Init(void) {
    for (int i = 1; i <= n; i++) {
        vector<int>& tmp = _tmp[i];
        tmp.clear(); tmp.push_back(0); c[0][i].clear(); c[1][i].clear();
        for (Edge *p = a[i]; p; p = p->next) if (p->y == f[0][i]) {
            tmp.push_back(sum[1] - sum[i]);
        } else tmp.push_back(sum[p->y] + fs[p->y]);
        sort(tmp.rbegin(), tmp.rend() - 1);
        c[0][i].resize(tmp.size());
        c[1][i].resize(tmp.size());
        for (int j = 1; j < (int)tmp.size(); j++) {
            c[j&1][i][j] = c[j&1][i][j - 1] + tmp[j];
            c[(j&1)^1][i][j] = c[(j&1)^1][i][j - 1];
        }
        //printf("c0 of %d: ", i); for (int j = 0; j < (int)c[0][i].size(); j++) printf("%d ", c[0][i][j]); puts("");
        //printf("c1 of %d: ", i); for (int j = 0; j < (int)c[1][i].size(); j++) printf("%d ", c[1][i][j]); puts("");
        //printf("List of %d: ", i); for (int j = 0; j < (int)tmp.size(); j++) printf("%d ", tmp[j]); puts("");
    }
}

inline int Cal(int u, int d1, int d2) {
    if (d1 < d2) swap(d1, d2);
    if (d1 == -1) {
        return *(c[1][u].end() - 1);
    }
    else if (d2 == -1) {
        int t1 = lower_bound(_tmp[u].rbegin(), _tmp[u].rend() - 1, d1) - _tmp[u].rbegin(); t1 = _tmp[u].size() - 1 - t1;
        int R1 = c[1][u][t1 - 1];
        int R2 = c[0][u][_tmp[u].size() - 1] - c[0][u][t1];
        //assert(R1 >= 0);
        //assert(R2 >= 0);
        return R1 + R2;
    } else {
        int t1 = upper_bound(_tmp[u].rbegin(), _tmp[u].rend() - 1, d1) - _tmp[u].rbegin() - 1; t1 = _tmp[u].size() - 1 - t1;
        int t2 = lower_bound(_tmp[u].rbegin(), _tmp[u].rend() - 1, d2) - _tmp[u].rbegin(); t2 = _tmp[u].size() - 1 - t2;
        //assert(t1 < t2);
        int R1 = c[1][u][t1 - 1];
        int R2 = c[0][u][t2 - 1] - c[0][u][t1]; 
        int R3 = c[1][u][_tmp[u].size() - 1] - c[1][u][t2];
        //assert(R1 >= 0);
        //assert(R2 >= 0);
        //assert(R3 >= 0);
    //    printf("%d %d %d %d\n", u, R1, R2, R3);
        return R1 + R2 + R3;
    }
}

inline void Process(void) {
    for (int i = 1; i <= m; i++) {
        int x = ScanInt(), y = ScanInt(), A = LCA(x, y), dis = deep[x] + deep[y] - 2 * deep[A];
        if (x == y) {
            int t = Cal(x, -1, -1);
            printf("%d\n", t);
            continue;
        }
        int meet;
        if (deep[x] > deep[y]) {
            meet = goUp(x, (dis + 1) >> 1);
        } else {
            meet = goUp(y, dis >> 1);
        } 
    //    printf("Node: %d and %d meet in %d\n", x, y, meet);
        if (meet == y) {
            if (f[0][y] == x) {
                int t = Cal(y, sum[1] - sum[y], -1);
                printf("%d\n", sum[1] - t);
            } else {
                int t = Cal(y, sum[x] + fs[x], -1);
                printf("%d\n", sum[1] - t);
            }
        } else
        if (meet == A) {
            int l1 = goUp(x, deep[x] - deep[A] - 1);
            int l2 = goUp(y, deep[y] - deep[A] - 1);
            int t = Cal(meet, sum[l1] + fs[l1], sum[l2] + fs[l2]);
            if (dis & 1) printf("%d\n", sum[1] - sum[l2] - fs[l2] - t);
            else printf("%d\n", sum[l1] + fs[l1] + t);
        } else {
            if (deep[x] > deep[y]) {
                int l1 = goUp(x, deep[x] - deep[meet] - 1);
                int t = Cal(meet, sum[l1] + fs[l1], sum[1] - sum[meet]);
                if (dis & 1) printf("%d\n", sum[meet] - t);
                else printf("%d\n", sum[l1] + fs[l1] + t);
            } else {
                int l2 = goUp(y, deep[y] - deep[meet] - 1);
                int t = Cal(meet, sum[1] - sum[meet], sum[l2] + fs[l2]);
                if (dis & 1) printf("%d\n", sum[1] - sum[l2] - fs[l2] - t);
                else printf("%d\n", t + sum[1] - sum[meet]);
            }
        }
    }
}

int main(void) {
    //freopen("in", "r", stdin);
//    freopen("ou", "w", stdout);
    int kase; scanf("%d", &kase); while (kase--) {
        //puts("-----------------------");
        data = POOL; n = ScanInt(), m = ScanInt();
        cl();
        for (int i = 1; i < n; i++) {
            int x = ScanInt(), y = ScanInt(), z = ScanInt();
            (data)->next = a[x]; data->y = y; data->c = z; a[x] = data++;
            (data)->next = a[y]; data->y = x; data->c = z; a[y] = data++;
        }
        Bfs();
        Init();
        Process();
    }
    return 0;
}