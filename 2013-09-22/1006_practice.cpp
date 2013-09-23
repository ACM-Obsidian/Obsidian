#include <cstdio>
#include <cmath>
struct point {
	double x, y;
} a[100];
point operator + (point a, point b) {
	point c;
	c.x = a.x+b.x, c.y = a.y+b.y;
	return c;
}
point operator - (point a, point b) {
	point c;
	c.x = a.x-b.x, c.y = a.y-b.y;
	return c;
}
double operator * (point a, point b) {
	return a.x*b.x + a.y*b.y;
}
point operator * (point a, double b) {
	point c;
	c.x = a.x*b, c.y = a.y*b;
	return c;
}
double dis(point a) {
	return sqrt(a*a);
}
double d, k, R, r;
int n;
double f(double x) {
	double rho = d/cos(k*x)+R-r;
	double drho = d*k*sin(k*x)/(cos(k*x)*cos(k*x));
	return sqrt(rho*rho+drho*drho);
}
double area(double (*f) (double), double l, double r) {
	double mid = (l+r)/2;
	return (f(l) + 4*f(mid) + f(r)) * (r-l) / 6;
}
double simpson(double (*f) (double), double l, double r) {
	double mid = (l+r)/2;
	double a = area(f, l, r), al = area(f, l, mid), ar = area(f, mid, r);
	if (fabs(al+ar-a) < 1e-8) return al+ar;
	else return simpson(f, l, mid) + simpson(f, mid, r);
}
int main() {
	for (; scanf("%lf%lf%d", &R, &r, &n) != EOF; ) {
		for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
		k = R/r;
		double ans = 0;
		for (int i = 0; i < n; i++) {
			int j = (i+1)%n;
			point x = a[j]-a[i];
			double d1 = a[i]*x/dis(x);
			d = sqrt(a[i]*a[i]-d1*d1);
			double d2 = a[j]*x/dis(x);
			d1 = atan(d1/d), d2 = atan(d2/d);
			ans += simpson(f, d1/k, d2/k);
		}
		printf("%.3lf\n", ans);
	}
	return 0;
}
