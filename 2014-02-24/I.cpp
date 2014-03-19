#include <cstdio>
#include <cstring>
#include <queue>
std::queue<int> q;
std::vector<int> g[500];
int d[500], s[500];
std::pair<int, int> a[20000];
void solve() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) g[i].clear();
	memset(a, 0, sizeof a);
	for (int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
		a[i] = std::pair<int, int>(x, y);
	}
	int min = 0x3FFFFFFF;
	for (int i = 0; i < n; i++) {
		memset(d, -1, sizeof d);
		d[i] = 0; q.push(i);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int j = 0; j < g[u].size(); j++)
				if (d[g[u][j]] == -1) {
					d[g[u][j]] = d[u]+1;
					if (u == i) s[g[u][j]] = g[u][j];
					else s[g[u][j]] = s[u];
					q.push(g[u][j]);
				}
		}
		for (int j = 0; j < m; j++)
			if (a[j].first != i && a[j].second != i && s[a[j].first] != s[a[j].second] && d[a[j].first] + d[a[j].second] + 1 < min)
				min = d[a[j].first] + d[a[j].second] + 1;
	}
	if (min > n) puts("impossible");
	else printf("%d\n", min);
}
int main() {
	int T; scanf("%d", &T);
	for (int i = 0; i < T; i++) printf("Case %d: ", i+1), solve();
	return 0;
}
