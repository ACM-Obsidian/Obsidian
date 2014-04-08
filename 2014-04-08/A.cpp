#include <cstdio>
#include <cmath>
struct itv {
	int l, r;
} a[8];
int now[8], u[8], n;
double ans;
void dfs(int dep) {
	if (dep == n) {
		double min = 1e30;
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++)
				if (1.0*(a[now[j]].r-a[now[i]].l)/(j-i) < min)
					min = 1.0*(a[now[j]].r-a[now[i]].l)/(j-i);
		if (min > ans) ans = min;
	} else {
		for (int i = 0; i < n; i++)
			if (!u[i]) {
				u[i] = 1;
				now[dep] = i;
				dfs(dep+1);
				u[i] = 0;
			}
	}
}
void solve() {
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	ans = 0;
	dfs(0);
	int sec = round(ans*60);
	printf("%d:%02d\n", sec/60, sec%60);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
