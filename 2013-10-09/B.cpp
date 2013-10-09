#include <cstdio>
int calc(int n, int m) {
	int ret = 0;
	for (; n; n /= m)
		ret += (n % m) * (n % m);
	return ret;
}
int main() {
	int n, m, bit[40], l;
	while (scanf("%d%d", &n, &m) != EOF) {
		int ans = 0;
		for (int i = 1; i * i <= n; i++) if (! (n%i)) {
			ans += calc(i, m);
			if (i * i < n) ans += calc(n/i, m);
		}
		l = 0;
		for (; ans; ans /= m, l++)
			bit[l] = ans % m;
		if (l > 0) l--;
		for (; l >= 0; l--)
			if (bit[l] < 10) printf("%c", bit[l]+48);
			else printf("%c", bit[l]+55);
		puts("");
	}
	return 0;
}