#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
int n, m, x[400], y[400], z[400], k[400], t[400], u[400], u2[400], q[400], v[400], c[400], map[400][400], num[400];
double f[400], w[400][400];
int wmax[400][400], wmax2[400][400];
void solve() {
	memset(map, 0, sizeof map);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &x[i], &y[i], &z[i], &k[i]), t[i] = z[i];
	}
	while (m--) {
		int x, y; scanf("%d%d", &x, &y); x--, y--;
		map[x][y] = map[y][x] = 1;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j) w[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]))-1;
	std::sort(t, t + n);
	m = std::unique(t, t + n) - t;
	double res = 1e30;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) u[j] = (z[j] <= t[i]);
		if (!u[0] || !u[n-1]) continue;
		double ans = 1e30;
		memset(u2, 0, sizeof u2);
		int cnt = 0;
		for (int j = 0; j < n; j++)
			if (u[j] && !u2[j]) {
				u2[j] = 1;
				c[j] = cnt;
				num[cnt] = 0;
				int l = 0, r = 0; q[0] = j;
				while (l <= r) {
					int k = q[l]; l++;
					for (int p = 0; p < n; p++)
						if (map[k][p] && u[p] && !u2[p]) u2[p] = 1, q[++r] = p, c[p] = cnt;
				}
				cnt++;
			}
		for (int j = 0; j < n; j++)
			if (u[j]) num[c[j]] += k[j];
		if (c[0] == c[n-1]) {
			if (num[c[0]] * 0.5 < res) res = num[c[0]] * 0.5;
			continue;
		}
		memset(wmax, -1, sizeof wmax);
		memset(wmax2, -1, sizeof wmax2);
		for (int i = 0; i < n; i++) if (u[i] && k[i] > 0)
			for (int j = 0; j < n; j++) if (u[j] && c[i] != c[j] && k[j] > 0)
				if (wmax[i][c[j]] == -1 || w[i][j] < w[i][wmax[i][c[j]]]) wmax2[i][c[j]] = wmax[i][c[j]], wmax[i][c[j]] = j;
				else if (wmax2[i][c[j]] == -1 || w[i][j] < w[i][wmax2[i][c[j]]]) wmax2[i][c[j]] = j;
		memset(v, 0, sizeof v);
		memset(f, 0x52, sizeof f);
		for (int i = 0; i < n; i++)
			if (u[i] && c[i] == c[0] && k[i] > 0) f[i] = num[c[0]] * 0.5;
		while (1) {
			int i = -1;
			double min = 1e30;
			for (int p = 0; p < n; p++) if (u[p] && k[p] > 0)
				if (!v[p] && f[p] < min)
					min = f[p], i = p;
			if (i == -1) break;
			v[i] = 1;
			for (int p = 0; p < n; p++)
				if (u[p] && k[p] > 0 && c[p] != c[i]) {
					int choice = (wmax[p][c[i]] == i && k[i] == 1 && c[i] != c[0] ? wmax2[p][c[i]] : wmax[p][c[i]]);
					if (choice == -1) continue;
					double tmp = f[i] + w[p][choice] + num[c[p]] * 0.5;
					if (tmp < f[p]) f[p] = tmp;
				}
		}
		for (int i = 0; i < n; i++)
			if (u[i] && c[i] == c[n-1] && k[i] > 0 && f[i] < ans) ans = f[i];
		if (ans < res) res = ans;
	}
	if (res > 1e20) puts("impossible");
	else printf("%.4lf\n", res);
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &m) == 2)
		printf("Case %d: ", ++_), solve();
	return 0;
}
