#include <cstdio>
#include <cmath>
#include <algorithm>
const double eps = 1e-10;
struct point {
	double x, y;
	point& operator += (point a) {
		x += a.x, y += a.y;
		return *this;
	}
	point& operator -= (point a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point& operator *= (double a) {
		x *= a, y *= a;
		return *this;
	}
	point& operator /= (double a) {
		x /= a, y /= a;
		return *this;
	}
};
point operator + (point a, point b) {
	point c; c = a, c += b; return c;
}
point operator - (point a, point b) {
	point c; c = a, c -= b; return c;
}
point operator * (point a, double b) {
	point c; c = a, c *= b; return c;
}
double operator * (point a, point b) {
	return a.x * b.x + a.y * b.y;
}
double operator % (point a, point b) {
	return a.x * b.y - a.y * b.x;
}
int parallel(point a, point b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
struct line {
	point a, s;
};
int line_line_cross(line a, line b, point *res = NULL) {
	if (parallel(a.s, b.s))
		if (parallel(b.a - a.a, a.s))
			return -1;
		else
			return 0;
	double k1 = (b.a - a.a) % b.s / (a.s % b.s);
	if (res != NULL) *res = a.a + a.s * k1;
	return 1;
}
int n;
line a[200];
double t[21000];
void solve() {
	int m = 3 * n;
	for (int i = 0; i < n; i++) {
		double x, h, b; scanf("%lf%lf%lf", &x, &h, &b);
		a[2*i].a.x = x-b/2, a[2*i].a.y = 0, a[2*i].s.x = b/2, a[2*i].s.y = h;
		a[2*i+1].a.x = x, a[2*i+1].a.y = h, a[2*i+1].s.x = b/2, a[2*i+1].s.y = -h;
		t[3*i] = x-b/2, t[3*i+1] = x, t[3*i+2] = x+b/2;
	}
	n *= 2;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++) {
			point p;
			int ret = line_line_cross(a[i], a[j], &p);
			if (ret == 1) {
				double k1 = (p - a[i].a) * a[i].s / (a[i].s * a[i].s);
				double k2 = (p - a[j].a) * a[j].s / (a[j].s * a[j].s);
				if (k1 > 1e-8 && k1 < 1-1e-8 && k2 > 1e-8 && k2 < 1-1e-8)
					t[m++] = p.x;
			}
		}
	std::sort(t, t + m);
	double ans = 0;
	for (int i = 0; i+1 < m; i++)
		if (t[i+1] - t[i] > 1e-8) {
			double x0 = (t[i] + t[i+1]) / 2, max = -1e30;
			int maxi = -1;
			for (int j = 0; j < n; j++)
				if (x0 >= a[j].a.x && x0 <= a[j].a.x + a[j].s.x) {
					double y0 = (x0 - a[j].a.x) * a[j].s.y / a[j].s.x + a[j].a.y;
					if (y0 > max) max = y0, maxi = j;
				}
			if (maxi != -1)
				ans += hypot(a[maxi].s.x, a[maxi].s.y) / a[maxi].s.x * (t[i+1] - t[i]);
		}
	printf("%.0lf\n", ans + 1e-8);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve(), puts("");
	return 0;
}
