#include <cstdio>
#include <cmath>
#include <algorithm>
int a[101], b[3], c[101], n, m;
bool divides() {
	for (int i = 0; i <= n; i++)
		c[i] = a[i];
	for (int i = n-m; i >= 0; i--) {
		int div = c[i+m] / b[m];
		int mod = c[i+m] - b[m] * div;
		if (mod)
			return false;
		for (int j = 0; j <= m; j++) {
			c[i+j] -= div * b[j];
			if (abs(c[i+j]) > 10000)
				return false;
		}
	}
	for (int j = 0; j < m; j++)
		if (c[j])
			return false;
	return true;
}
bool check(int x, int y) {
	m = 1;
	b[1] = x, b[0] = y;
	if (divides())
		return true;
	m = 2;
	b[2] = x, b[0] = y;
	int i = 0;
	if (4 * b[2] * b[0] >= 0) {
		i = sqrt(4 * b[2] * b[0]);
		if (i * i <= 4 * b[2] * b[0])
			i++;
	}
	for (; i <= 1400; i++) {
		b[1] = i;
		if (divides())
			return true;
		if (i) {
			b[1] = -i;
			if (divides())
				return true;
		}
	}
	return false;
}
void outfrac(int n, int d) {
	int g = std::__gcd(std::abs(n), std::abs(d));
	n /= g, d /= g;
	printf("%d/%d", n, d);
}
int main() {
	freopen("poly.in", "r", stdin);
	freopen("poly.out", "w", stdout);
	for (int _ = 1; scanf("%d", &n) == 1; _++) {
		for (int i = n; i >= 0; i--)
			scanf("%d", &a[i]);
		if (n == 0 && a[0] == 0) {
			m = 1;
			b[1] = 1, b[0] = 0;
			goto out;
		}
		for (int i = 1; i * i <= std::abs(a[n]); i++)
			for (int j = (a[0] == 0 ? 0 : 1); j * j <= std::abs(a[0]); j++) {
				if (check(i, j)) goto out;
				if (check(i, -j)) goto out;
				if (check(a[n]/i, j)) goto out;
				if (check(a[n]/i, -j)) goto out;
				if (!j) continue;
				if (check(i, a[0]/j)) goto out;
				if (check(i, -a[0]/j)) goto out;
				if (check(a[n]/i, a[0]/j)) goto out;
				if (check(a[n]/i, -a[0]/j)) goto out;
			}
		printf("Case #%d: Polynomial does not have such roots\n", _);
		continue;
out:
		if (m == 1)
			printf("Case #%d: Polynomial has rational root ", _), outfrac(-b[0], b[1]), printf("\n");
		else
			printf("Case #%d: Polynomial has root ", _), outfrac(-b[1], 2*b[2]), printf("+sqrt("), outfrac(b[1]*b[1]-4*b[0]*b[2], 4*b[2]*b[2]), printf(")\n");
	}
	return 0;
}
