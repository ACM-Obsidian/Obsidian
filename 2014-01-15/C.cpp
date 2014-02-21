#include <cstdio>
#include <algorithm>
long long a[17][100000], b[100000];
long long query(int l, int r) {
	int delta = 31-__builtin_clz(r-l+1);
	return std::__gcd(a[delta][l], a[delta][r-(1<<delta)+1]);
}
void solve() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", &b[i]), a[0][i] = b[i];
	for (int i = 1; i < 17; i++)
		for (int j = 0; j+(1<<i) <= n; j++)
			a[i][j] = std::__gcd(a[i-1][j], a[i-1][j+(1<<i-1)]);
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		long long cur = b[i];
		int p = i;
		while (1) {
			int l = p, r = n;
			while (l < r) {
				int mid = l+r>>1;
				if (query(i, mid) == cur) l = mid+1;
				else r = mid;
			}
			if ((l - i) * cur > ans)
				ans = cur * (l - i);
			cur = query(i, l);
			p = l;
			if (l == n) break;
		}
	}
	printf("%lld\n", ans);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
