#include <cstdio>
int main() {
	double n, k;
	scanf("%lf%lf", &n, &k);
	if (k == 1) {
		printf("%lf\n", n * (n+1) / 2);
		return 0;
	}
	long double t = 1 / k, ans = n;
	for (int i = 1; n-2*i+1 > 0 && t > 1e-13; i++, t /= k)
		ans += (2*n-4*i+1) * t;
	printf("%.9Lf\n", ans);
	return 0;
}
