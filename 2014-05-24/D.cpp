#include <cstdio>
struct rec {
	long long x, y;
} q[20001];
long long f[20001], g[20001];
int n, k, a, d, c;
void solve(int L, int R) {
	if (L == R) {
		if (f[L] != -1 && (g[L] == -1 || f[L] < g[L])) g[L] = f[L];
		return;
	}
	int mid = L+R>>1, p = 20001, r = 0;
	for (int j = mid; j >= L && j > R-c; j--)
		if (f[j] != -1) {
			long long x = j, y = 2*f[j] - 2LL*a*j - 1LL*d*j*j;
			while (r >= 2 && (x - q[r-1].x) * (q[r-1].y - q[r-2].y) < (y - q[r-1].y) * (q[r-1].x - q[r-2].x)) r--;
			q[r].x = x, q[r].y = y, r++;
		}
	for (int j = R; j > mid; j--) {
		if (j-c >= L && j-c <= mid && f[j-c] != -1) {
			long long x = j-c, y = 2*f[j-c] - 2LL*a*(j-c) - 1LL*d*(j-c)*(j-c);
			while (r >= 2 && (x - q[r-1].x) * (q[r-1].y - q[r-2].y) < (y - q[r-1].y) * (q[r-1].x - q[r-2].x)) r--;
			q[r].x = x, q[r].y = y, r++;
		}
		long long k = 1LL * (2*j-1) * d;
		if (r > 0) {
			p++; if (p > r-1) p = r-1;
			while (p > 0 && q[p].x * k + q[p].y > q[p-1].x * k + q[p-1].y) p--;
			long long tmp = (q[p].x * k + q[p].y) / 2 + 1LL*a*j - 1LL*d*j*(j-1)/2;
			if (g[j] == -1 || g[j] > tmp) g[j] = tmp;
		}
	}
	solve(L, mid);
	solve(mid+1, R);
}
int main() {
	scanf("%d%d", &n, &k);
	f[0] = 0;
	for (int i = 1; i <= 20000; i++) f[i] = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &a, &d, &c);
		for (int j = 0; j <= 20000; j++) g[j] = -1;
		solve(0, 20000);
		for (int j = 0; j <= 20000; j++) f[j] = g[j];
	}
	while (k--) {
		int m; scanf("%d", &m);
		printf("%lld\n", f[m]);
	}
	return 0;
}
