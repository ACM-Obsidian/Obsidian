#include <cstdio>
#include <algorithm>
long long a[1000000];
int main() {
	int l = 0;
	for (; ; l++) {
		long long tmp = 3LL*l*l+3*l+1;
		if (tmp > 1000000000000LL) break;
		a[l] = tmp;
	}
	while (1) {
		long long x; scanf("%lld", &x);
		if (!x) break;
		if (x % 6 != 1 && x % 6 != 2)
			printf("%d\n", (int)((x-1) % 6 + 1));
		else if (x % 6 == 1) {
			int p = std::upper_bound(a, a+l, x) - a - 1;
			puts(a[p] == x ? "1" : "7");
		} else {
			int p = std::upper_bound(a, a+l, x) - a - 1, q = 0, flag = 0;
			for (; p >= 0 && a[p]*2 >= x; p--) {
				while (q < l && a[p] + a[q] < x) q++;
				if (q < l && a[p] + a[q] == x) {
					flag = 1;
					break;
				}
			}
			puts(flag ? "2" : "8");
		}
	}
	return 0;
}
