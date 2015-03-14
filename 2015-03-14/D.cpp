#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10010;
const long long inf = 1000000000000000000ll;

struct Edge {
	int y, dir;long long f, ori; Edge *next, *opt;
}*a[MAXN], DATA[(510000 + 20000) << 1], *data = DATA, *e[MAXN];

inline void Add(int x, int y, long long c) {
	Edge *tmp = data++;
	tmp->y = y; tmp->f = c, tmp->next = a[x]; a[x] = tmp;
	tmp = data++; tmp->y = x; tmp->f = 0; tmp->next = a[y]; a[y] = tmp;
	a[x]->opt = a[y]; a[y]->opt = a[x];
	a[x]->dir = 1; a[y]->dir = -1;
	a[x]->ori = c; a[y]->ori = 0;
}
int n, m, vs, vt, L;
int level[MAXN], d[MAXN];
inline bool Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] = vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		e[now] = a[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->f > 0&& level[p->y] == -1)
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}
inline long long Extend(int u, long long sum) {
	if (u == vt) return sum;
	long long r = 0, t;
	for (Edge *p = e[u]; p && r < sum; p = p->next) if (level[p->y] == level[u] + 1 && p->f > 0) {
		t = std::min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t, p->opt->f += t, r += t;
		e[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}
inline long long Dinic(void) {
	long long r = 0, t;
	while (Bfs()) {
		while ((t = Extend(vs, inf))) r += t;
	}
	return r;
}

long long S = 0;

int main(void) {
	freopen("flow.in", "r", stdin);
	freopen("flow.out", "w", stdout);
	scanf("%d%d", &n, &m);
	vs = n + 1, vt = vs + 1;
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x); 
		if (x > 0) Add(vs, i, x), S += x;
		if (x < 0) Add(i, vt, -x);
	}
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		Add(x, y, 0);
	}
	int l = 0, r = 10000000;
	while (l <= r) {
		int mid = (l + r) >> 1;
		for (int i = 1; i <= vt; i++) {
			for (Edge *p = a[i]; p; p = p->next) {
				p->f = p->ori;
				if (p->y != vs && i != vs && p->y != vt && i != vt && p->dir == 1) {
					p->f = mid;
				}
			}
		}
		long long tmp = Dinic();
		if (tmp == S) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", l);
	return 0;
}

