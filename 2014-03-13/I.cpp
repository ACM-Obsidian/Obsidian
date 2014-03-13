#include <cstdio>
#include <algorithm>
int x[100000], y[100000];
int main() {
	freopen("semi-cool.in", "r", stdin);
	freopen("semi-cool.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
	long long s = 0;
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n;
		s += 1LL*x[i]*y[j]-1LL*x[j]*y[i];
	}
	s = std::abs(s);
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n, dx = std::abs(x[j]-x[i]), dy = std::abs(y[j]-y[i]);
		int t = std::__gcd(dx, dy);
		dx /= t, dy /= t;
		if (dx&1 && dy&1) s += t;
	}
	printf("%lld\n", s/2);
	return 0;
}
