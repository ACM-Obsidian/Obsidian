#include <cstdio>
#include <cstring>
int a[2001][2001], x, y, n, q;
void solve() {
	memset(a, 0, sizeof a);
	for (int i = 0; i < n; i++) {
		int tx, ty; scanf("%d%d", &tx, &ty);
		a[tx+ty][tx-ty+y]++;
	}
	for (int i = 1; i <= x+y; i++)
		for (int j = 1; j <= x+y; j++)
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
	while (q--) {
		int m; scanf("%d", &m);
		int ans = -1, ansx = 0, ansy = 0;
		for (int i = 1; i <= x; i++)
			for (int j = 1; j <= y; j++) {
				int ir = i+j+m, il = i+j-m, jr = i-j+y+m, jl = i-j+y-m;
				if (ir > x+y) ir = x+y;
				if (il < 1) il = 1;
				if (jr > x+y) jr = x+y;
				if (jl < 1) jl = 1;
				int tmp = a[ir][jr] - a[il-1][jr] - a[ir][jl-1] + a[il-1][jl-1];
				if (tmp > ans || tmp == ans && (j < ansy || j == ansy && i < ansx))
					ans = tmp, ansx = i, ansy = j;
			}
		printf("%d (%d,%d)\n", ans, ansx, ansy);
	}
}
int main() {
	int _ = 0;
	while (scanf("%d%d%d%d", &x, &y, &n, &q), x)
		printf("Case %d:\n", ++_), solve();
	return 0;
}
