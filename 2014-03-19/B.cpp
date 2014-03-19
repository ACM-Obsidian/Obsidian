#include <cstdio>
#include <cstring>
#include <algorithm>
struct edge {
	int y, f;
	double c;
	edge *next, *opt;
	edge() {}
	edge(int y, int f, double c, edge *next):y(y), f(f), c(c), next(next){}
}*a[200], pool[100000];
int top;
inline void addedge(int x, int y, int f, double c) {
	pool[top] = edge(y, f, c, a[x]), a[x] = &pool[top++];
	pool[top] = edge(x, 0, -c, a[y]), a[y] = &pool[top++];
	a[x]->opt = a[y], a[y]->opt = a[x];
}
int d[200], vis[200], vs, vt;
double dis[200];
edge *path[200];
inline std::pair<int,double> spfa(void) {
	int flow = 0;
	double cost = 0;
	while (1) {
		memset(vis, 0, sizeof vis);
		memset(dis, 0x60, sizeof dis);
		memset(path, 0, sizeof path);
		int head = 1, tail = 1, sum = 1; d[1] = vs, vis[vs] = true; dis[vs] = 0;
		while (sum) {
			int now = d[head++]; if (head == 200) head = 1; sum--;
			vis[now] = false;
			for (edge *p = a[now]; p; p = p->next)
				if (p->f > 0 && dis[p->y] > dis[now] + p->c + 1e-8) {
					dis[p->y] = dis[now] + p->c;
					path[p->y] = p;
					if (!vis[p->y]) {
						++tail; if (tail == 200) tail = 1; sum++;
						d[tail] = p->y;
						vis[p->y] = true;
					}
				}
		}
		if (dis[vt] == dis[0]) return std::make_pair(flow, cost);
		int tmp = vt, min = ~0U>>1;
		while (path[tmp]) {
			min = std::min(min, path[tmp]->f);
			tmp = path[tmp]->opt->y;
		}
		flow += min;
		tmp = vt;
		while (path[tmp]) {
			path[tmp]->f -= min;
			path[tmp]->opt->f += min;
			cost += min * path[tmp]->c;
			tmp = path[tmp]->opt->y;
		}
	}
	return std::make_pair(flow, cost);
}
int n, m;
void solve() {
	top = 0;
	for (int i = 1; i <= n+m+2; i++) a[i] = NULL;
	for (int i = 0; i < n; i++) {
		int c; scanf("%d", &c);
		addedge(n+m+1, i+1, c, 0);
	}
	for (int i = 0; i < m; i++) {
		int c; scanf("%d", &c);
		addedge(i+n+1, n+m+2, c, 0);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			double c; scanf("%lf", &c);
			if (c != -1)
				addedge(i+1, j+n+1, ~0U>>2, c);
		}
	vs = n+m+1, vt = n+m+2;
	double ans1 = spfa().second;
	for (int i = 1; i <= n+m+2; i++)
		for (edge *p = a[i]; p; p = p->next)
			if (p->y != n+m+1 && p->y > i || i == n+m+1) {
				p->f = p->f + p->opt->f;
				p->opt->f = 0;
				p->c = -p->c;
				p->opt->c = -p->opt->c;
			}
	double ans2 = -spfa().second;
	printf("%.2lf to %.2lf\n", ans1, ans2);
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &m), n)
		printf("Problem %d: ", ++_), solve();
}
