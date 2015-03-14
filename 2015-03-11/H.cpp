#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20010;

struct Edge {
	Edge *next, *opt; int y, f; int dir;
}*a[MAXN], POOL[400010], *data = POOL, *e[MAXN];

void AddEdge(int x, int y, int c) {
	Edge *tmp = data++;
	tmp->y = y; tmp->f = c; tmp->next = a[x]; a[x] = tmp; tmp->dir = 0;
	tmp = data++;
	tmp->y = x; tmp->f = 0; tmp->next = a[y]; a[y] = tmp; tmp->dir = 1;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
}

int n, m;
int vis[MAXN], cur, link[MAXN], hash[MAXN];

int find(int u) {
	hash[u] = cur;
	for (Edge *p = a[u]; p; p = p->next) if (p->dir == 0 && vis[p->y] != cur) {
		vis[p->y] = cur;
		if (link[p->y] == -1 || find(link[p->y])) {
			link[p->y] = u;
			return true;
		}
	}
	return false;
}

int stack[MAXN], top, vs, vt;

int level[MAXN], d[MAXN];
bool Bfs(void) {
	memset(level, -1, sizeof level);
	int head = 1, tail = 1;
	d[1] = vs; level[vs] = 0;
	while (head <= tail) {
		int now = d[head++];
		e[now] = a[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1) {
			level[d[++tail] = p->y] = level[now] + 1;
		}
	}
	return level[vt] != -1;
}

int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge *p = e[u]; p && r < sum; p =p ->next) if (p->f > 0 && level[p->y] == level[u] + 1) {
		t = min(p->f, sum - r);
		t = Extend(p->y, t);
		r += t; p->f -= t; p->opt->f += t;
		e[u] = p;
	}
	if (r == 0) level[u] = -1;
	return r;
}

int Dinic(void) {
	int r = 0, t;
	while (Bfs()) {
		while ((t = Extend(vs, 0x7fffffff))) r += t;
	}
	return r;
}

inline int ScanInt(void) {
	int r = 0, c;
	while (!isdigit(c = getchar()));
	r = c - 48;
	while ( isdigit(c = getchar())) r = r * 10 + c - 48;
	return r;
}

int main(void) {
	freopen("sociology.in", "r", stdin);
	freopen("sociology.out", "w", stdout);
	int t;
	int _ = 0; while (scanf("%d%d%d", &m, &n, &t) == 3) {
		data = POOL; memset(a, 0, sizeof a);
		printf("Case #%d: ", ++_);
		memset(link, -1, sizeof link);
		for (int i = 1; i <= t; i++) {
			int x, y; y = ScanInt(), x = ScanInt(); y += n;
			AddEdge(x, y, 1);
		}
		vs = n + m + 1, vt = vs + 1;
		for (int i = 1; i <= n; i++) AddEdge(vs, i, 1);
		for (int i = n + 1; i <= n + m; i++) AddEdge(i, vt, 1);
		int match = Dinic();
		int w = -1;
		for (Edge *p = a[vs]; p; p = p->next) if (p->dir == 0 && p->f == 1) {
			w = p->y;
			break;
		}
		for (int i = n + 1; i <= n + m; i++) {
			for (Edge *p = a[i]; p; p = p->next) if (p->dir == 1 && p->f == 1) {
				link[i] = p->y;
				break;
			}
		}
		cur++;
		if (w != -1) {
			find(w);
			top = 0;
			for (int j = 1; j <= n; j++) if (hash[j] == cur) {
				stack[++top] = j;
			}
			printf("Manager"); if (top != 1) putchar('s'); putchar(' ');
			for (int j = 1; j <= top; j++) {
				printf("%d", stack[j]);
				if (j < top - 1) printf(", ");
				if (j == top - 1) printf(" and ");
				if (j == top) printf(" ");
			}
			printf("form"); if (top == 1) putchar('s'); putchar(' ');
			puts("an excessive subset."); 
		} else {
			puts("There is no excessive subset of managers.");
		}
	}
	return 0;
}

