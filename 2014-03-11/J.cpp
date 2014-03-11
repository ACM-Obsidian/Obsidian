#include <cstdio>
int mask[30], num[30], a[20], n, k, m, now[20], ans, ansnow[20];
void dfs(int dep, int start) {
	if (dep == 0) {
		int t = 0;
		for (int i = 0; i < k; i++) t |= 1<<now[i];
		int sum = 0;
		for (int i = 0; i < m; i++)
			if (t & mask[i]) sum += num[i];
		if (sum > ans) {
			ans = sum;
			for (int i = 0; i < k; i++) ansnow[i] = now[i];
		}
		return;
	}
	for (int i = start; i <= n-dep; i++) {
		now[dep-1] = i;
		dfs(dep-1, i+1);
	}
}
void solve() {
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		mask[i] = 0;
		int j, x; scanf("%d", &j);
		while (j--) {
			scanf("%d", &x); mask[i] |= 1<<x-1;
		}
		scanf("%d", &num[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (mask[j] & 1<<i) a[i] -= num[j];
		num[m+i] = a[i], mask[m+i] = 1<<i;
	}
	m += n;
	ans = -1;
	dfs(k, 0);
	printf("Number of Customers: %d\nLocations recommended:", ans);
	for (int i = k-1; i >= 0; i--) printf(" %d", ansnow[i]+1);
	printf("\n\n");
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &k), n)
		printf("Case Number  %d\n", ++_), solve();
	return 0;
}
