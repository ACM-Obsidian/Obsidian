#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const int MAXN = 1012;
const int inf = 1000000;
 
int n, m, vs, vt, now[MAXN];
 
vector<int> c[MAXN];
 
struct Edge {
    int y, f, c; Edge *next, *opt;
    Edge(int y, int f, int c, Edge *next):y(y), f(f), c(c), next(next){}
}*a[MAXN];
 
inline void AddEdge(int x, int y, int f, int c) {
 // printf("X = %d, Y = %d, F = %d, C = %d\n", x, y, f, c);
    a[x] = new Edge(y, f, c, a[x]);
    a[y] = new Edge(x, 0, -c, a[y]);
    a[x]->opt = a[y]; a[y]->opt = a[x];
}
 
int d[MAXN], vis[MAXN], dis[MAXN]; Edge *path[MAXN];
 
inline pair<int, int> Spfa(void) {
    int Flow = 0, Cost = 0;
    while (true) {
        memset(vis, 0, sizeof vis);
        memset(dis, 0x7f, sizeof dis);
        memset(path, 0, sizeof path);
        int head = 1, tail = 1, sum = 1; d[1] = vs; vis[vs] = true; dis[vs] = 0;
        while (sum) {
            int now = d[head++]; if (head == MAXN) head = 1; sum--;
            for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
                dis[p->y] = dis[now] + p->c;
                path[p->y] = p;
                if (!vis[p->y]) {
                    ++tail; if (tail == MAXN) tail = 1; sum++;
                    d[tail] = p->y;
                    vis[p->y] = true;
                }
            }
            vis[now] = false;
        }
        if (dis[vt] == dis[0]) return make_pair(Flow, Cost);
        int tmp = vt, Min = ~0U>>1;
        while (path[tmp]) {
            Min = min(Min, path[tmp]->f);
            tmp = path[tmp]->opt->y;
        }
        Flow += Min;
        tmp = vt;
        while (path[tmp]) {
            path[tmp]->f -= Min;
            path[tmp]->opt->f += Min;
            Cost += Min * path[tmp]->c;
            tmp = path[tmp]->opt->y;
        }
    }
    return make_pair(Flow, Cost);
}
 
bool is[MAXN];
 
int main(void) {
    freopen("keeper.in", "r", stdin);
    freopen("keeper.out", "w", stdout);
    scanf("%d%d", &m, &n);
    int cnt = 0;
    for (int i = 1, x; i <= m; i++) {
        int t; scanf("%d", &t); while (t--) {
            scanf("%d", &x);
            c[i].push_back(x);
        }
    }
    for (int i = 1; i <= m; i++) scanf("%d", now + i), is[now[i]] = true, cnt += !!now[i];
    vs = n + m + 1, vt = vs + 1;
    for (int i = 1; i <= m; i++) {
        AddEdge(vs, i, 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        AddEdge(i + m, vt, 1, 0);
    }
    for (int i = 1; i <= m; i++) {
		for (vector<int>::iterator it = c[i].begin(); it != c[i].end(); ++it)
			AddEdge(i, *it + m, 1, -(*it == now[i]));
    }
    pair<int, int> Ans = Spfa();
    printf("%d %d\n", Ans.first, cnt + Ans.second);
    for (int i = 1; i <= m; i++) {
        int now = m;
        for (Edge *p = a[i]; p; p = p->next) if (p->y != vs && p->f == 0) {
            now = p->y;
            break;
        }
        printf("%d%c", now - m, " \n"[i == m]);
    }
    return 0;
}
