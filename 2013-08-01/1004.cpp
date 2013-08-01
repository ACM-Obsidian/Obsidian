#include <cstdio>
#include <cstring>
#include <vector>
using std::vector;
vector<int> g[100000], g_[100000];
int a[100000], b[100000], d1[100000], d2[100000], s[100000], u[100000], n, m, k;
void dfs1(int n, int &t) {
	u[n] = 1;
	for (int i = 0; i < g[n].size(); i++)
		if (!u[g[n][i]]) dfs1(g[n][i], t);
	a[t++] = n;
}
void dfs2(int n, int c) {
	u[n] = 1;
	b[n] = c, s[c]++;
	for (int i = 0; i < g_[n].size(); i++)
		if (!u[g_[n][i]]) dfs2(g_[n][i], c);
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y), x--, y--;
		g[x].push_back(y), g_[y].push_back(x);
	}
	int t = 0;
	memset(u, 0, sizeof u);
	for (int i = 0; i < n; i++)
		if (!u[i]) dfs1(i, t);
	memset(u, 0, sizeof u);
	memset(s, 0, sizeof s);
	k = 0;
	for (int i = n-1; i >= 0; i--)
		if (!u[a[i]]) dfs2(a[i], k++);
	memset(d1, 0, sizeof d1);
	memset(d2, 0, sizeof d2);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < g[i].size(); j++)
			if (b[i] != b[g[i][j]])
				d1[b[g[i][j]]] = 1, d2[b[i]] = 1;
	int min = n;
	for (int i = 0; i < k; i++)
		if ((d1[i] == 0 || d2[i] == 0) && s[i] < min) min = s[i];
	if (min == n) puts("-1");
	else printf("%d\n", n*(n-1)-min*(n-min)-m);
	for (int i = 0; i < n; i++) g[i].clear(), g_[i].clear();
}
int main() {
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; printf("Case %d: ", _), _++, solve());
	return 0;
}
