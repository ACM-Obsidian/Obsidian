#include <cstdio>
#include <cmath>
struct intv {
	double xl, xr, yl, yr;
} a[10000];
int n, m;
double r, h[10000], x[10000], y[10000], ans[10000], ansh;
int main() {
	freopen("green.in", "r", stdin);
	freopen("green.out", "w", stdout);
	scanf("%d%d%lf", &n, &m, &r);
	r = r * 3.14159265358979324 / 180;
	for (int i = 0; i < n; i++) scanf("%lf", &h[i]);
	for (int i = 0; i < m; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		y[i] += x[i] * tan(r);
	}
	int t = 0;
	double y0 = y[0]; int i = 1;
	while (1) {
		while (i < m && y[i] < y0 + 1e-8) i++;
		if (i == m) break;
		double x0 = x[i] - (y[i] - y0) * ((x[i] - x[i-1]) / (y[i] - y[i-1]));
		a[t].xl = x0, a[t].xr = x[i], a[t].yl = y0, a[t].yr = y[i]; t++;
		y0 = y[i++];
	}
	if (t == 0) {
		ansh = 0;
		for (int i = 0; i < n; i++) {
			ans[i] = 0;
			if (h[i] > ansh) ansh = h[i];
		}
	} else {
		double max = 0;
		int maxi;
		for (int i = 0; i < n; i++)
			if (h[i] > max) max = h[i], maxi = i;
		ans[maxi] = a[t-1].xr;
		double y0 = a[0].yl, x0 = a[0].xl;
		int k = 0, i = 0;
		for (; i < n; i++)
			if (i != maxi) {
				ans[i] = x0, y0 += h[i];
				while (k < t && y0 > a[k].yr) k++;
				if (k == t) break;
				x0 = a[k].xr - (a[k].yr - y0) * ((a[k].xr - a[k].xl) / (a[k].yr - a[k].yl));
			}
		for (i++; i < n; i++)
			if (i != maxi) ans[i] = a[t-1].xr;
		if (k == t) ansh = a[t-1].yr - a[0].yl + max;
		else ansh = y0 - a[0].yl + max;
	}
	printf("%.10lf\n", ansh);
	for (int i = 0; i < n; i++) printf("%.10lf\n", ans[i]);
	return 0;
}
