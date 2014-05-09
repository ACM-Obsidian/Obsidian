#include <cstdio>
#include <cstring>
int g[20][20];
int f1[262144][20], f2[262144][20], n, m;
void solve() {
	memset(g, 0x1F, sizeof g);
	memset(f1, 0x1F, sizeof f1);
	memset(f2, 0x1F, sizeof f2);
	while (m--) {
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		g[x][y] = g[y][x] = v;
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (k != i && k != j && i != j && g[i][k] + g[k][j] < g[i][j])
					g[i][j] = g[i][k] + g[k][j];
	f1[0][0] = 0;
	for (int i = 1; i < 1<<n-2; i++)
		for (int j = 1; j < n-1; j++) if (i & 1<<j-1)
			for (int k = 0; k < n-1; k++)
				if (f1[i-(1<<j-1)][k] + g[k][j] < f1[i][j])
					f1[i][j] = f1[i-(1<<j-1)][k] + g[k][j];
	f2[0][n-1] = 0;
	for (int i = 1; i < 1<<n-2; i++)
		for (int j = 1; j < n-1; j++) if (i & 1<<j-1)
			for (int k = 1; k < n; k++)
				if (f2[i-(1<<j-1)][k] + g[k][j] < f2[i][j])
					f2[i][j] = f2[i-(1<<j-1)][k] + g[k][j];
	int ans = ~0U>>1;
	for (int i = 0; i < 1<<n-2; i++)
		if (__builtin_popcount(i) == (n-2)/2) {
			int ans1 = ~0U>>2, ans2 = ~0U>>2, i2 = (1<<n-2)-1-i;
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					if (f1[i][j] + f2[i2][k] + g[j][k] < ans1)
						ans1 = f1[i][j] + f2[i2][k] + g[j][k];
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					if (f1[i2][j] + f2[i][k] + g[j][k] < ans2)
						ans2 = f1[i2][j] + f2[i][k] + g[j][k];
			if (ans1 + ans2 < ans)
				ans = ans1 + ans2;
		}
	printf("%d\n", ans);
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &m) != EOF)
		printf("Case %d: ", ++_), solve();
	return 0;
}
