#include <cstdio>
#include <cmath>
#include <algorithm>
int a[15], x, y, f[32768], g[32768][101], n;
void solve() {
	scanf("%d%d", &x, &y);
	if (x > y) std::swap(x, y);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	int ans = 0;
	for (int i = 1; i < 1<<n; i++) {
		int cnt = 0;
		f[i] = 0;
		for (int j = 0; j < n; j++)
			if (i & 1<<j) f[i] += a[j], cnt++;
		int l = f[i] / y; if (f[i] % y) l++;
		int r = sqrt(f[i] + 1e-8); if (x < r) r = x;
		for (int j = l; j <= r; j++)
			if (!(f[i] % j)) {
				if (cnt == 1) g[i][j] = 1;
				else {
					g[i][j] = 0;
					int x1 = j, y1 = f[i] / j;
					for (int k = (i-1)&i; k; (--k) &= i) {
						if (!(f[k] % x1)) {
							int x2 = x1, y2 = f[k] / x1;
							int x3 = x1, y3 = y1 - y2;
							if (x2 > y2) std::swap(x2, y2);
							if (x3 > y3) std::swap(x3, y3);
							g[i][x1] |= g[k][x2] && g[i-k][x3];
						}
						if (!(f[k] % y1)) {
							int x2 = f[k] / y1;
							g[i][x1] |= g[k][x2] && g[i-k][x1 - x2];
						}
					}
				}
				if (f[i] == x * y && j == x && g[i][j]) ans = 1;
			}
	}
	puts(ans ? "Yes" : "No");
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
