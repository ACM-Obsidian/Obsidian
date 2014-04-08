#include <cstdio>
#include <cmath>
const double pi = 3.14159265358979324;
double d[4], d2[4], a[4], x[4], y[4], ans;
int num[4];
void check(int mask) {
	int m = 0;
	for (int i = 0; i < 4; i++)
		if (mask & 1 << i) num[i] = m, a[m++] = d2[i];
	double l = 0, r = 1e8;
	for (int i = 0; i < m; i++)
		if (a[i] + a[(i+1)%m] > l) l = a[i] + a[(i+1)%m];
	while (l < r*(1-1e-10)) {
		double mid = (l+r)/2;
		double th = 0;
		for (int i = 0; i < m; i++) {
			int j = (i+1)%m;
			th += acos(((mid-a[i])*(mid-a[i])+(mid-a[j])*(mid-a[j])-(a[i]+a[j])*(a[i]+a[j]))/(2*(mid-a[i])*(mid-a[j])));
		}
		if (th > 2*pi) l = mid;
		else r = mid;
	}
	double th = 0;
	for (int i = 0; i < m; i++) {
		int j = (i+1)%m;
		x[i] = (l-a[i])*cos(th), y[i] = (l-a[i])*sin(th);
		th += acos(((l-a[i])*(l-a[i])+(l-a[j])*(l-a[j])-(a[i]+a[j])*(a[i]+a[j]))/(2*(l-a[i])*(l-a[j])));
	}
	if (th < 2*pi-1e-8) return;
	for (int i = 0; i < m; i++)
		for (int j = i+1; j < m; j++)
			if (((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/((a[i]+a[j])*(a[i]+a[j])) < 1 - 1e-8) return;
	for (int i = 0; i < 4; i++)
		if (~mask & 1 << i) {
			if (d2[i] > l-1e-8) return;
			int j = num[(i+3)%4], k = num[(i+1)%4];
			double th = -acos(((d2[i]+a[j])*(d2[i]+a[j])+(a[j]+a[k])*(a[j]+a[k])-(d2[i]+a[k])*(d2[i]+a[k]))/(2*(d2[i]+a[j])*(a[j]+a[k])));
			double dx = (x[k]-x[j])*cos(th)-(y[k]-y[j])*sin(th), dy = (x[k]-x[j])*sin(th)+(y[k]-y[j])*cos(th);
			dx *= (d2[i]+a[j])/(a[j]+a[k]), dy *= (d2[i]+a[j])/(a[j]+a[k]);
			dx += x[j], dy += y[j];
			if ((dx * dx + dy * dy) / ((l-d2[i]) * (l-d2[i])) > 1 + 1e-8) return;
		}
	if (l < ans) ans = l;
}
void process(int x1, int x2, int x3, int x4) {
	d2[0] = d[x1], d2[1] = d[x2], d2[2] = d[x3], d2[3] = d[x4];
	check(15), check(7), check(11), check(13), check(14), check(5), check(10);
}
void solve() {
	scanf("%lf%lf%lf", &d[1], &d[2], &d[3]);
	ans = 1e30;
	process(0, 1, 2, 3);
	process(0, 1, 3, 2);
	process(0, 2, 1, 3);
	printf("%.0lf\n", ans);
}
int main() {
	int _ = 0;
	while (scanf("%lf", &d[0]), d[0] > 0)
		printf("Case %d: ", ++_), solve();
	return 0;
}
