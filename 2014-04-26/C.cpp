#include <cstdio>
#include <algorithm>
#include <cmath>
long long int_sqrt(long long a) {
	long long tmp = (long long)sqrt(a);
	if (tmp * tmp == a) return tmp;
	tmp++;
	if (tmp * tmp == a) return tmp;
	else return -1;
}
long long ans[3];
int main() {
	int p, q, u, v;
	scanf("%d%d%d%d", &p, &q, &u, &v);
	if (q < 0) p = -p, q = -q;
	if (v < 0) u = -u, v = -v;
	if (std::abs(p) >= q || std::abs(u) >= v) {
		puts("-1");
		return 0;
	}
	long long c1 = 1LL*q*q-1LL*p*p, c2 = 1LL*v*v-1LL*u*u;
	long long d = std::__gcd(c1, c2);
	c1 = int_sqrt(c1 / d), c2 = int_sqrt(c2 / d);
	if (c1 == -1 || c2 == -1) {
		puts("-1");
		return 0;
	}
	long long p1 = c1 * v, p2 = c2 * q, p3 = u * c1 + p * c2;
	if (p3 <= 0) {
		puts("-1");
		return 0;
	}
	long long t = std::__gcd(p1, p2);
	t = std::__gcd(t, p3);
	p1 /= t, p2 /= t, p3 /= t;
	ans[0] = p1, ans[1] = p2, ans[2] = p3;
	std::sort(ans, ans + 3);
	printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);
	return 0;
}
