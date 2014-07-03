#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 1220;

struct Edge {
	int y, f; Edge *next, *opt;
}*e[MAXN], POOL[MAXN * MAXN], *data = POOL, *c[MAXN];

struct point {
	int x, y, id;
}a[MAXN], stack0[MAXN], stack1[MAXN];

int n;

void AddEdge(int x, int y) {
	Edge *tmp = data++;
	tmp->f = 1; tmp->y = y; tmp->next = e[x]; e[x] = tmp;
	tmp = data++;
	tmp->f = 0; tmp->y = x; tmp->next = e[y]; e[y] = tmp;
	e[x]->opt = e[y]; e[y]->opt = e[x];
}

int vs, vt;
int level[MAXN], d[MAXN];
inline bool Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] =vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		c[now] = e[now];
		for (Edge *p = e[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1) 
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}

inline int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge *p = c[u]; p && r < sum; p = p->next) if (p->f > 0 && level[p->y] == level[u] + 1) {
		t = std::min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t; p->opt->f += t; r += t;
		c[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}

inline int Dinic(void) {
	int r = 0, t;
	while (Bfs()) while ((t = Extend(vs, ~0u>>1))) r += t;
	return r;
}

inline long long dis(const point&i, const point& j) {
	return (i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y);
}

long long cross(const point& a, const point& mid, const point& b) {
	return (a.x - mid.x) * (b.y - mid.y) - (a.y - mid.y) * (b.x - mid.x);
}

int vis[MAXN];
long long maxd;

void Dfs(int u) {
	vis[u] = true;
	for (Edge *p = e[u]; p; p = p->next) if (!vis[p->y] && p->f > 0) {
		Dfs(p->y);
	}
}
int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d%lld", &n, &maxd);maxd *= maxd;
	if (n == 1) {
		puts("1");
		puts("1");
		return 0;
	}
	int Ans = 1; vector<int> ret(1, 1);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y), a[i].id = i;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			long long d = dis(a[i], a[j]);
			if (d > maxd) continue;
			data = POOL; memset(e, 0, sizeof e);
			int top0 = 0, top1 = 0;
			for (int k = 1; k <= n; k++) if (k != i && k != j) {
				if (dis(a[i], a[k]) <= d && dis(a[j], a[k]) <= d) {
					if (cross(a[i], a[j], a[k]) < 0)
						stack0[++top0] = a[k];
					else
						stack1[++top1] = a[k];
				}
			}
			for (int l0 = 1; l0 <= top0; l0++)
				for (int l1 = 1; l1 <= top1; l1++) if (dis(stack0[l0], stack1[l1]) > d) {
					AddEdge(l0, l1 + top0);
				}
			vs = top0 + top1 + 1, vt = vs + 1;
			for (int l0 = 1; l0 <= top0; l0++) AddEdge(vs, l0);
			for (int l1 = top0 + 1; l1 <= top0 + top1; l1++) AddEdge(l1, vt);
			int tmp = top0 + top1 - Dinic() + 2;
			if (tmp > Ans) {
				memset(vis, 0, sizeof vis); Dfs(vs); ret.clear(); Ans = tmp; ret.push_back(i); ret.push_back(j);
				for (int l0 = 1; l0 <= top0; l0++) if (vis[l0]) ret.push_back(stack0[l0].id);
				for (int l1 = top0 + 1; l1 <= top0 + top1; l1++) if (!vis[l1]) ret.push_back(stack1[l1 - top0].id);
			}
		}
	sort(ret.begin(), ret.end());
	printf("%d\n", Ans);
	for (int i = 0; i < ret.size(); i++) printf("%d ", ret[i]); puts("");
	return 0;
}

