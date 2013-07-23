#include <cstdio>
#include <cmath>
int sum[15001];
int main() {
	sum[1] = 3;
	for (int i = 2; i <= 15000; i++) {
		int t = i, x = i;
		for (int j = 2; j * j <= t; j++)
			if (! (t % j)) {
				x = x / j * (j-1);
				for (; ! (t % j); t /= j);
			}
		if (t > 1) x = x / t * (t-1);
		sum[i] = sum[i-1] + x;
	}
	for (long long n; scanf("%lld", &n), n >= 0; ) {
		if (n == 0) {
			puts("1 1");
			continue;
		}
		int i = 1;
		long long t;
		for (; i <= 15000; i++) {
			t = (sum[i] + sqrt((sum[i] - 4.0) * (sum[i] - 4) + 8.0 * (sum[i] - 2) * n)) / (2 * (sum[i] - 2)) + 0.5;
			if (t <= 15000 && ((sum[i] - 2) * t - sum[i]) * t + 2 == 2 * n) break;
		}
		if (i <= 15000 && t <= 15000) printf("%d %lld\n", i, t);
		else puts("NOT FOUND");
	}
	return 0;
}