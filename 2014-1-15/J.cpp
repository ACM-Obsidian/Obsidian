#include <cstdio>
int a[4001], f[4000];
void solve() {
	int k, m; scanf("%d%d", &k, &m);
	f[0] = 1, f[1] = 2;
	for (int i = 2; i < k; i++)
		f[i] = (f[i-2]+f[i-1]) % m;
	for (int i = 0; i <= k; i++) a[i] = 0;
	a[0] = 1;
	for (int i = 0; i < k; i++)
		for (int j = i+1; j >= 0; j--)
			a[j] = (((j == 0 ? 0 : a[j-1]) - 1LL*a[j]*f[i]) % m + m) % m;
	int ans = 0;
	for (int i = 0; i < k; i++) {
		int x; scanf("%d", &x);
		ans = ((ans - 1LL*x*a[i]) % m + m) % m;
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
