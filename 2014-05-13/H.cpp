#include <cstdio>
int f[500][500], g[500], min[500][500], minl[500][500], a[500], hash[501], n;
void solve() {
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= 500; j++) hash[j] = 0;
		int m = ~0U>>1;
		for (int j = i; j < n; j++) {
			if (hash[a[j]]) {
				for (int k = j; k < n; k++) min[i][k] = -1;
				break;
			}
			hash[a[j]] = 1;
			if (a[j] < m) m = a[j];
			min[i][j] = m;
			int t = m; while (t <= 500 && hash[t]) t++;
			minl[i][j] = t-m;
		}
	}
	for (int i = 0; i < n; i++) f[i][i] = 0;
	for (int len = 1; len < n; len++)
		for (int i = 0; i < n-len; i++) {
			int j = i+len;
			f[i][j] = ~0U>>3;
			if (min[i][j] == -1) continue;
			for (int k = i; k < j; k++) {
				int tmp = f[i][k] + f[k+1][j] + j-i+1;
				if (min[i][k] < min[k+1][j]) tmp -= minl[i][k];
				else tmp -= minl[k+1][j];
				if (tmp < f[i][j]) f[i][j] = tmp;
			}
		}
	for (int i = 0; i < n; i++) {
		g[i] = ~0U>>3;
		if (min[0][i] == 1 && minl[0][i] == i+1) g[i] = f[0][i];
		for (int j = 0; j < i; j++)
			if (min[j+1][i] == 1 && minl[j+1][i] == i-j && g[j] + f[j+1][i] < g[i])
				g[i] = g[j] + f[j+1][i];
	}
	if (g[n-1] > 100000000) puts("impossible");
	else printf("%d\n", g[n-1]);
}
int main() {
	while (scanf("%d", &n) != EOF) solve();
	return 0;
}
