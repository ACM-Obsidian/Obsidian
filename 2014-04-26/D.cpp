#include <cstdio>
#include <algorithm>
int x1, y1, x2, y2, px, py;
long long floor(long long x, long long d) {
	if (!(x%d)) return ~0ULL>>1;
	if (d < 0) x = -x, d = -d;
	if (x < 0) return x / d - 1;
	else return x / d;
	return x;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &px, &py);
		long long x3 = 1LL*y2*px-1LL*x2*py, y3 = 1LL*x1*py-1LL*y1*px;
		long long d = 1LL*x1*y2-1LL*x2*y1;
		x3 = floor(x3, d), y3 = floor(y3, d);
		if (x3 == ~0ULL>>1 || y3 == ~0ULL>>1) puts("-1");
		else printf("%lld\n", 4*(std::abs(x3)+std::abs(y3)));
	}
	return 0;
}
