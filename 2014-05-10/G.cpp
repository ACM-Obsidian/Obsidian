#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
int f[36][25][25], f2[36][25][25], f3[36][25][25];
std::vector<std::pair<int, int> > g[25], g_[25];
void solve() {
	int n, m, d; scanf("%d%d%d", &n, &m, &d);
	for (int i = 0; i < n; i++) g[i].clear(), g_[i].clear();
	while (m--) {
		int x, y, t; scanf("%d%d%d", &x, &y, &t);
		g[x].push_back(std::make_pair(y, t));
		g_[y].push_back(std::make_pair(x, t));
	}
	memset(f, 0, sizeof f);
	memset(f2, 0, sizeof f2);
	memset(f3, 0, sizeof f3);
	for (int i = 0; i < n; i++) f[0][i][i] = f2[0][i][i] = f3[0][i][i] = 1;
	int ans = 0;
	for (int i = 1; i <= d; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				if (i >= 2)
					for (int p = 0; p < g[j].size(); p++)
						for (int q = 0; q < g_[k].size(); q++)
							if (g[j][p].second > 0 && g[j][p].second + g_[k][q].second == 0)
								f2[i][j][k] += f3[i-2][g[j][p].first][g_[k][q].first];
				f3[i][j][k] = f2[i][j][k];
				for (int q = 1; q < i; q++)
					for (int p = 0; p < n; p++)
						f3[i][j][k] += f2[q][j][p] * f3[i-q][p][k];
				for (int p = 0; p < g[j].size(); p++)
					if (g[j][p].second == 0)
						f3[i][j][k] += f3[i-1][g[j][p].first][k];
				f[i][j][k] = f2[i][j][k];
				for (int q = 1; q < i; q++)
					for (int p = 0; p < n; p++)
						f[i][j][k] += f2[q][j][p] * f[i-q][p][k];
				for (int p = 0; p < g[j].size(); p++)
					if (g[j][p].second >= 0)
						f[i][j][k] += f[i-1][g[j][p].first][k];
				if (i == d) ans += f[i][j][k];
			}
	printf("%d\n", ans & 32767);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
