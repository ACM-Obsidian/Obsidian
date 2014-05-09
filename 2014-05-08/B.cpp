#include <cstdio>
const double pi = 3.14159265358979324;
double a[22], b[11], xl, xr, d, res[8];
int an, n;
double eval(double x) {
	double s = 0;
	for (int i = an; i >= 0; i--)
		s = s * x + a[i];
	return s;
}
void solve() {
	for (int i = 0; i <= n; i++) scanf("%lf", &b[i]);
	for (int i = 0; i <= 2*n; i++) a[i] = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			a[i+j] += b[i] * b[j];
	for (int i = 2*n; i >= 0; i--)
		a[i+1] = a[i]/(i+1);
	an = 2*n+1;
	scanf("%lf%lf%lf", &xl, &xr, &d);
	d /= pi;
	int l = 0;
	double vl = eval(xl), vr = eval(xr);
	printf("%.2lf\n", pi*(vr-vl));
	for (; l < 8; l++) {
		if (vr-vl < (l+1)*d-1e-8) break;
		double ll = xl, rr = xr;
		while (ll+1e-10 < rr) {
			double mid = (ll+rr)/2;
			if (eval(mid)-vl > (l+1)*d) rr = mid;
			else ll = mid;
		}
		res[l] = (ll+rr)/2;
	}
	if (l == 0) puts("insufficient volume");
	else
		for (int i = 0; i < l; i++) printf("%.2lf%c", res[i]-xl, " \n"[i==l-1]);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n) == 1)
		printf("Case %d: ", ++_), solve();
	return 0;
}
