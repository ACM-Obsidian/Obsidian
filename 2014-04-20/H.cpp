#include <cstdio>
#include <algorithm>
int n, k, p;
int main() {
	scanf("%d%d%d", &n, &k, &p);
	if (p == 100) p = 50;
	else if (p == 50) p = 100;
	p = 50 - p; int q = 50;
	if (p < 0) {
		puts("0");
		return 0;
	}
	int d = std::__gcd(p, q);
	p /= d, q /= d;
	if (p > k || q - p > k * (n-1)) {
		puts("0");
		return 0;
	}
	printf("1\n%d ", p);
	q -= p;
	for (int i = 1; i < n; i++) {
		int t = std::min(q, k);
		printf("%d%c", t, " \n"[i == n-1]);
		q -= t;
	}
	return 0;
}
