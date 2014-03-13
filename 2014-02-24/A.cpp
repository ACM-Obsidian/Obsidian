#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
int a[81], f[5001][81], g[5001][81], cnt[5001][81][81], m, fi[5001][81], la[5001][81];
void solve() {
	int n, p;
	for (int i = 0; i <= m; i++) scanf("%d", &a[i]), g[0][i] = a[i];
	scanf("%d%d", &n, &p);
	for (int i = 0; i < m; i++) {
		fi[0][i] = a[i+1], la[0][i] = a[i];
		for (int j = 0; j < m; j++)
			cnt[0][j][i] = 0;
		for (int j = std::min(a[i], a[i+1]); j < std::max(a[i], a[i+1]); j++)
			cnt[0][j][i]++;
		if (abs(a[i] - a[i+1]) != 1) f[0][i] = 0;
		else f[0][i] = a[i+1] - a[i];
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= m; j++)
			g[i][j] = a[g[i-1][j]];
		for (int j = 0; j < m; j++)
			for (int k = 1; k < m; k++)
				cnt[i-1][j][k] = (cnt[i-1][j][k] + cnt[i-1][j][k-1]) % p;
		for (int j = 0; j < m; j++) {
			if (g[i-1][j] != fi[i-1][j])
				fi[i][j] = (g[i-1][j] < fi[i-1][j] ? a[g[i-1][j]+1] : a[g[i-1][j]-1]);
			else
				fi[i][j] = g[i][j];
			if (la[i-1][j] != g[i-1][j+1])
				la[i][j] = (la[i-1][j] < g[i-1][j+1] ? a[g[i-1][j+1]-1] : a[g[i-1][j+1]+1]);
			else
				la[i][j] = g[i][j+1];
			int min = std::min(a[j], a[j+1]), max = std::max(a[j], a[j+1]);
			if (a[j] == a[j+1])
				for (int k = 0; k < m; k++) cnt[i][k][j] = 0;
			else
				for (int k = 0; k < m; k++)
					cnt[i][k][j] = (cnt[i-1][k][max-1] - (min ? cnt[i-1][k][min-1] : 0) + p) % p;
			if (abs(a[j] - a[j+1]) == 1 && f[i-1][min]) f[i][j] = (a[j+1] - a[j]) * f[i-1][min];
			else f[i][j] = 0;
		}
	}
	int ans = 0;
	for (int i = 0; i < m; i++)
		if (f[n-1][i] == 1 && g[n-1][i] == i)
			ans = -1;
	if (ans == -1) puts("Infinity");
	else {
		for (int i = 0; i < m; i++) {
			ans = (ans + cnt[n-1][i][i]) % p;
			if (g[n-1][i] == i && fi[n-1][i] > i) ans--;
			if (g[n-1][i+1] == i+1 && la[n-1][i] < i+1) ans--;
		}
		for (int i = 0; i <= m; i++)
			if (g[n-1][i] == i) ans++;
		ans = (ans % p + p) % p;
		printf("%d\n", ans);
	}
}
int main() {
	while (scanf("%d", &m), m) solve();
	return 0;
}
