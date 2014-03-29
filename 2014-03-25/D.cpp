#include <cstdio>
#include <algorithm>
int n, m, x[1000], y[1000], u[1000];
void solve() {
	int scale = 0;
	for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]), u[i] = 1;
	for (int i = 0; i < n; i++)
		if (x[i] == x[(i+1)%n] && y[i] == y[(i+1)%n]) u[i] = 0;
	int i = 0;
	for (int j = 0; ; j++) {
		while (j < n && !u[j]) j++;
		if (j == n) break;
		x[i] = x[j], y[i] = y[j]; i++;
	}
	n = i;
	for (int i = 0; i < n; i++) u[i] = 1;
	for (int i = 0; i < n; i++) {
		int j = (i+n-1)%n, k = (i+1)%n;
		if (1LL*(x[i]-x[j])*(y[i]-y[k]) == 1LL*(x[i]-x[k])*(y[i]-y[j]) && 1LL*(x[i]-x[j])*(x[i]-x[k])+1LL*(y[i]-y[j])*(y[i]-y[k]) <= 0)
			u[i] = 0;
	}
	i = 0;
	for (int j = 0; ; j++) {
		while (j < n && !u[j]) j++;
		if (j == n) break;
		x[i] = x[j], y[i] = y[j]; i++;
	}
	n = i;
	if (n <= 2) {
		puts("0");
		return;
	}
	for (int i = 1; i < n; i++) scale = std::__gcd(x[i] - x[0], scale), scale = std::__gcd(y[i] - y[0], scale);
	scale = std::abs(scale);
	long long area = 0, edge = 0;
	for (int i = 0; i < n; i++) {
		area += 1LL*x[i]*y[(i+1)%n]-1LL*x[(i+1)%n]*y[i];
		edge += std::abs(std::__gcd(x[(i+1)%n]-x[i], y[(i+1)%n]-y[i]));
	}
	area = std::abs(area)/(1LL*scale*scale);
	edge = edge/scale;
	printf("%llu\n", (1ULL*m*(m+1)*(2*m+1)/6*area-1ULL*m*(m+1)/2*edge+2*m)/2);
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &m), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
