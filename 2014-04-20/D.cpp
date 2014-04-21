#include <cstdio>
long long n, k;
int x, y, q;
int main() {
	scanf("%lld%d%d%d", &n, &x, &y, &q);
	while (q--) {
		scanf("%lld", &k), k--;
		int t = 0;
		long long a = 0, b = 0;
		while (k) {
			if (((t + n) & 1) ^ (k & 1)) a++;
			else b++;
			k >>= 1, t++;
		}
		if ((t + n) & 1) a += (n - t) / 2 + 1, b += (n - t) / 2;
		else a += (n - t) / 2, b += (n - t) / 2;
		printf("%lld %lld\n", a, b);
	}
	return 0;
}
