#include <cstdio>
#include <cstring>
#include <bitset>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

struct Edge {
	int y, f; Edge *next, *opt;
}*a[MAXN], POOL[MAXN * MAXN], *data = POOL, *e[MAXN];

inline void AddEdge(int x, int y) {
//	printf("%d %d\n", x, y);
	Edge *tmp = data++;
	tmp->y = y; tmp->f = 1; tmp->next = a[x]; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->f = 0; tmp->next = a[y]; a[y] = tmp;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
}

int n, m, vs, vt;
int level[MAXN], d[MAXN];

inline int Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] = vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		e[now] = a[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1)
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}

inline int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge *p = e[u]; p && r < sum; p = p->next) if (p->f > 0 && level[p->y] == level[u] + 1) {
		t = min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t, p->opt->f += t, r += t;
		e[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}

inline int Dinic(void) {
	int r = 0, t;
	while (Bfs()) while ((t = Extend(vs, ~0u>>1))) r += t;
	return r;
}

struct Node {
	vector<int> a; int type; //0 for less, 1 for greater
	bitset<1024> bit;
}c[MAXN];

vector<int> List;

int vis[MAXN];
void Dfs(int u) {
	vis[u] = 1;
	for (Edge *p = a[u]; p; p = p->next) if (p->f > 0 && !vis[p->y]) Dfs(p->y);
}

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++) {
		int x, t; scanf("%d", &x); while (x--) scanf("%d", &t), c[i].a.push_back(t), c[i].bit.set(t - 1);
		char ch[10]; scanf("%s", ch); c[i].type = (ch[1] == 'o');
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) if (i != j) {
			if (c[i].type == 0 && c[j].type == 1 && (c[i].bit & c[j].bit) == c[j].bit) {
				AddEdge(i, j);
			}
		}
	}
	vs = n + 1, vt = vs + 1;
	for (int i = 1; i <= n; i++) {
		if (c[i].type == 0) AddEdge(vs, i); else AddEdge(i, vt);
	}
	int Ans = Dinic();
	printf("%d\n", Ans);
	Dfs(vs);
	for (int i = 1; i <= n; i++) if (c[i].type == vis[i]) printf("%d ", i); puts("");
	return 0;
}

