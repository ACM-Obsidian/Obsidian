#include <cstdio>
#include <vector>
#include <algorithm>
std::vector<std::pair<int, std::pair<int, int> > > e;
std::vector<std::pair<int, int> > g[200000];
int u[200000], f[200000];
void dfs(int n) {
	for (int i = 0; i < g[n].size(); i++) {
		if (!u[g[n][i].first]) {
			u[g[n][i].first] = 1;
			dfs(g[n][i].first);
		}
		if (g[n][i].first > n)
			e.push_back(std::make_pair(-g[n][i].second, std::make_pair(n, g[n][i].first)));
	}
}
int find_root(int x) {
	int r = x;
	for (; f[r] != r; r = f[r]);
	for (int y; f[x] != x; y = f[x], f[x] = r, x = y);
	return r;
}
int main() {
	int n, m; scanf("%d%d", &n, &m);
	long long ans = 0;
	while (m--) {
		int x, y, v; scanf("%d%d%d", &x, &y, &v), x--, y--;
		if (v > 0) {
			g[x].push_back(std::make_pair(y, v));
			g[y].push_back(std::make_pair(x, v));
		}
		ans += v;
	}
	for (int i = 0; i < n; i++) f[i] = i;
	for (int i = 0; i < n; i++)
		if (!u[i]) {
			u[i] = 1;
			e.clear();
			dfs(i);
			std::sort(e.begin(), e.end());
			for (int i = 0; i < e.size(); i++) {
				int x = e[i].second.first, y = e[i].second.second;
				int rx = find_root(x), ry = find_root(y);
				if (rx != ry) {
					ans += e[i].first;
					f[rx] = ry;
				}
			}
		}
	printf("%lld\n", ans);
	return 0;
}
