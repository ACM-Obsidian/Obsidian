#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 105010;

struct Edge {
	int y, z; Edge *next;
}*a[25010], POOL[MAXN << 1], *data = POOL;

inline void AddEdge(int x, int y, int z) {
	Edge *tmp = data++;
	tmp->y = y; tmp->next = a[x]; tmp->z = z; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->next = a[y]; tmp->z = z; a[y] = tmp;
}

struct Edge_f {
	int y, f, ori; Edge_f *next, *opt;
}*e[25010], *cur[25010], POOL2[MAXN << 1], *data_f = POOL2, *T[25010];

inline void AddEdge_f(int x, int y, int f) {
	Edge_f *tmp = data_f++;
	tmp->y = y; tmp->next = e[x]; tmp->ori = tmp->f = f; e[x] = tmp;
	tmp = data_f++;
	tmp->y = x; tmp->next = e[y]; tmp->ori = tmp->f = 0; e[y] = tmp;
	e[x]->opt = e[y]; e[y]->opt = e[x];
}

int n, m, k, dis[25010], vs, vt;

priority_queue<pair<int, int> > Q;

int list[25010], value[25010];

inline int cmp(int x, int y) {return dis[x] < dis[y];}

int level[25010], d[25010];
inline int Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] = vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		cur[now] = e[now];
		for (Edge_f *p = e[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1) 
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}

inline int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge_f *p = cur[u]; p && r < sum; p = p->next) if (p->f > 0 && level[p->y] == level[u] + 1) {
		t = min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t, p->opt->f += t, r += t;
		cur[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}

inline int Dinic(void) {
	int r = 0, t;
	while (Bfs())
		while ((t = Extend(vs, ~0u>>1))) r += t;
	return r;
}

inline void clear(void) {
	while (!Q.empty()) Q.pop();
	memset(a, 0, sizeof a);
	data = POOL;
	memset(e, 0, sizeof e);
	data_f = POOL2;
	memset(value, 0, sizeof value);
}

int main(void) {
	//freopen("in", "r", stdin);
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		clear();
		for (int i = 1; i <= m; i++) {
			int x, y, z; scanf("%d%d%d", &x, &y, &z);
			AddEdge(x, y, z);
		}
		for (int i = 1, x; i <= k; i++) scanf("%d", &x), value[x]++;
		memset(dis, 0x3f, sizeof dis); Q.push(make_pair(dis[1] = 0, 1));
		for (int i = 1; i < n; i++) {
			while (!Q.empty() && Q.top().first != -dis[Q.top().second]) Q.pop();
			if (Q.empty()) break;
			int now = Q.top().second; Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (dis[p->y] > dis[now] + p->z)
				Q.push(make_pair(-(dis[p->y] = dis[now] + p->z), p->y));
		}
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next) {
				if (dis[p->y] == dis[i] + p->z) AddEdge_f(p->y, i, 1);
			}
		int top = 0;
		for (int i = 1; i <= n; i++) if (value[i]) list[++top] = i;
		sort(list + 1, list + top + 1, cmp);
		int Ans = 0; vs = n + 1, vt = 1;
		Edge_f *backup = data_f;
		memcpy(T, e, sizeof e);
		for (int i = 1, j; i <= top; i = j) {
			data_f = backup;
			j = i + 1; memcpy(e, T, sizeof T);
			while (j <= top && dis[list[j]] == dis[list[i]]) j++;
			for (int k = 1; k <= n; k++)
				for (Edge_f *p = e[k]; p; p = p->next) p->f = p->ori;
			for (int k = i; k < j; k++) {
				AddEdge_f(vs, list[k], value[list[k]]);
			}
			Ans += Dinic();
		}
		printf("%d\n", Ans);
	}
	return 0;
}

