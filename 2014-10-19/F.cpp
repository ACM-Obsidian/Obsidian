#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

struct Edge {
	int y, z; Edge *next;
	Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
}*a[MAXN];

pair<int, pair<int, int> > e[MAXN];

int n, m, f[MAXN];
inline int get(int x) {return x == f[x] ? f[x] : (f[x] = get(f[x]));}

int father[MAXN], selected[MAXN], deep[MAXN], value[MAXN];

void Dfs(int now, int last = -1) {
	for (Edge *p = a[now]; p; p = p->next) if (p->y != last) {
		father[p->y] = now;
		deep[p->y] = deep[now] + 1;
		value[p->y] = p->z;
		Dfs(p->y, now);
	}
}

int Ans[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e[i].first = z;
		e[i].second = make_pair(x, y);
	}
	for (int i = 1; i <= n; i++) f[i] = i;
	sort(e + 1, e + m + 1);
	for (int i = 1; i <= m; i++) {
		int x = e[i].second.first, y = e[i].second.second;
		int fx = get(x), fy = get(y);
		if (fx != fy) {
			selected[i] = true;
			f[fx] = fy;
			a[x] = new Edge(y, e[i].first, a[x]);
			a[y] = new Edge(x, e[i].first, a[y]);
		}
	}
	Dfs(1);
	for (int i = 1; i <= m; i++) if (!selected[i]) {
		int x = e[i].second.first, y = e[i].second.second;
		if (deep[x] > deep[y]) swap(x, y);
		while (deep[y] > deep[x]) {
			if (value[y] == e[i].first) Ans[y] = true;
			y = father[y];
		}
		while (x != y) {
			if (value[y] == e[i].first) Ans[y] = true;
			if (value[x] == e[i].first) Ans[x] = true;
			x = father[x], y = father[y];
		}
	}
	int cnt = 0, sum = 0;
	for (int i = 2; i <= n; i++) if (!Ans[i]) {
		cnt++, sum += value[i];
	}
	printf("%d %d\n", cnt, sum);
	return 0;
}

