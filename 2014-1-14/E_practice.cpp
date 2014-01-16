#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
struct point {
	double x, y;
} a[100000];
bool operator < (point x, point y) {
	return x.x < y.x;
}
std::vector<point> upper, lower;
double xmin, xmax;
void getlu(double x, double &l, double &u) {
	point tmp; tmp.x = x, tmp.y = 0;
	int k = std::lower_bound(upper.begin(), upper.end(), tmp) - upper.begin();
	if (k == 0) u = upper[k].y;
	else u = upper[k].y - (upper[k].y - upper[k-1].y) / (upper[k].x - upper[k-1].x) * (upper[k].x - x);
	k = std::lower_bound(lower.begin(), lower.end(), tmp) - lower.begin();
	if (k == 0) l = lower[k].y;
	else l = lower[k].y - (lower[k].y - lower[k-1].y) / (lower[k].x - lower[k-1].x) * (lower[k].x - x);
}
double f(double x, double *w, double *l, double *u) {
	double xl, xu;
	getlu(x, xl, xu);
	double wl = x, wr = xmax, wll = xl, wlu = xu, wrl, wru;
	getlu(wr, wrl, wru);
	while (wr - wl > 1e-8 && (wr - wl) / (fabs(wl) + fabs(wr)) > 1e-8) {
		double ml = (11*wl+9*wr)/20, mr = (11*wr+9*wl)/20, mll, mlu, mrl, mru;
		getlu(ml, mll, mlu);
		getlu(mr, mrl, mru);
		double al = (ml-x) * ((mlu < xu ? mlu : xu) - (mll > xl ? mll : xl));
		double ar = (mr-x) * ((mru < xu ? mru : xu) - (mrl > xl ? mrl : xl));
		if (al < ar) wl = ml, wll = mll, wlu = mlu;
		else wr = mr, wrl = mrl, wru = mru;
	}
	if (w != NULL) *w = wl-x;
	if (l != NULL) *l = (wll > xl ? wll : xl);
	if (u != NULL) *u = (wlu < xu ? wlu : xu);
	return (wl-x) * ((wlu < xu ? wlu : xu) - (wll > xl ? wll : xl));
}
int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
	int n; scanf("%d", &n);
	xmin = 1e30, xmax = -1e30;
	int j;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &a[i].x, &a[i].y);
		if (a[i].x < xmin) xmin = a[i].x, j = i;
		if (a[i].x > xmax) xmax = a[i].x;
	}
	for (; a[j].x == xmin; j = (j+1)%n); j = (j+n-1)%n;
	for (; ; j = (j+1)%n) {
		upper.push_back(a[j]);
		if (a[j].x == xmax) break;
	}
	for (; a[j].x == xmax; j = (j+1)%n); j = (j+n-1)%n;
	for (; ; j = (j+1)%n) {
		lower.push_back(a[j]);
		if (a[j].x == xmin) break;
	}
	std::reverse(lower.begin(), lower.end());
	double xl = xmin, xr = xmax;
	while (xr - xl > 1e-8 && (xr - xl) / (fabs(xl) + fabs(xr)) > 1e-8) {
		double ml = (11*xl+9*xr)/20, mr = (11*xr+9*xl)/20;
		if (f(ml, NULL, NULL, NULL) < f(mr, NULL, NULL, NULL)) xl = ml;
		else xr = mr;
	}
	double ansxl = xl, ansxr, ansyl, ansyr;
	f(ansxl, &ansxr, &ansyl, &ansyr); ansxr += ansxl;
	printf("%lf %lf %lf %lf\n", ansxl, ansyl, ansxr, ansyr);
	return 0;
}
