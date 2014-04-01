#include <cstdio>
#include <algorithm>
double f[21], g[21], a[3][3], b[3], c, ans[3];
int n;
double integrate(double *f, int n, double x) {
	double s = 0;
	for (int i = n; i >= 0; i--)
		s = (s + f[i] / (i+1)) * x;
	return s;
}
double det(double (*a)[3]) {
	return a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1]
		- a[0][2]*a[1][1]*a[2][0] - a[0][1]*a[1][0]*a[2][2] - a[0][0]*a[1][2]*a[2][1];
}
void solve() {
	for (int i = n; i >= 0; i--) scanf("%lf", &f[i]);
	scanf("%lf", &c);
	b[2] = integrate(f, n, 1) - integrate(f, n, -1);
	for (int i = 0; i <= n+1; i++) g[i] = 0;
	for (int i = 0; i <= n; i++)
		g[i] -= c * f[i], g[i+1] += f[i];
	b[0] = integrate(g, n+1, c) - integrate(g, n+1, -1);
	b[1] = integrate(g, n+1, 1) - integrate(g, n+1, c);
	a[0][0] = (c+1)*(c+1)*(c+1)/3, a[0][1] = 0, a[0][2] = -(c+1)*(c+1)/2;
	a[1][0] = 0, a[1][1] = (1-c)*(1-c)*(1-c)/3, a[1][2] = (1-c)*(1-c)/2;
	a[2][0] = -(c+1)*(c+1)/2, a[2][1] = (1-c)*(1-c)/2, a[2][2] = 2;
	double d = det(a);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) std::swap(a[j][i], b[j]);
		ans[i] = det(a) / d;
		for (int j = 0; j < 3; j++) std::swap(a[j][i], b[j]);
	}
	printf("%.3lf %.3lf %.3lf %.3lf\n", ans[0], ans[2]-ans[0]*c, ans[1], ans[2]-ans[1]*c);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
