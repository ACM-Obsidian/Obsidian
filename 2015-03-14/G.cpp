#include <cstdio>
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		long long n; scanf("%I64d", &n);
		if (n == 1) puts("2");
		else {
			long long ans = n;
			for (int k = 2; 1LL * k * k <= n; k++)
				if (!(n % k)) {
					ans /= k, ans *= k-1;
					for (; !(n % k); n /= k);
				}
			if (n > 1)
				ans /= n, ans *= n-1;
			printf("%I64d\n", ans);
		}
	}
	return 0;
}
