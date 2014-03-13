#include <cstdio>
#include <cmath>
#include <algorithm>
const double pi = 3.14159265358979324;
struct point2 {
	double x, y;
	point2 (void) {}
	point2 (double _x, double _y) : x(_x), y(_y) {}
	point2& operator += (point2 a) {
		x += a.x, y += a.y;
		return *this;
	}
	point2& operator -= (point2 a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point2& operator *= (double a) {
		x *= a, y *= a;
		return *this;
	}
	point2& operator /= (double a) {
		x /= a, y /= a;
		return *this;
	}
};
point2 operator + (point2 a, point2 b) {
	point2 c; c = a; c += b; return c;
}
point2 operator - (point2 a, point2 b) {
	point2 c; c = a; c -= b; return c;
}
point2 operator * (point2 a, double b) {
	point2 c; c = a; c *= b; return c;
}
point2 operator * (double a, point2 b) {
	point2 c; c = b; c *= a; return c;
}
point2 operator / (point2 a, double b) {
	point2 c; c = a; c /= b; return c;
}
double operator * (point2 a, point2 b) {
	return a.x * b.x + a.y * b.y;
}
double operator % (point2 a, point2 b) {
	return a.x * b.y - a.y * b.x;
}
double dis(point2 a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
double arg(point2 a) {
	return atan2(a.y, a.x);
}

point2 a[150000];
double b[150000], c[150000];
std::pair<double, int> d[150000];
int main() {
	freopen("minimum.in", "r", stdin);
	freopen("minimum.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
	int l = 2; c[0] = 0, c[1] = pi/2;
	for (int i = 0; i < n; i++) {
		b[i] = arg(a[(i+1)%n]-a[i]);
		if (b[i] < 0) b[i] += 2*pi;
		d[i] = std::make_pair(b[i], i);
		if (b[i] < 0) b[i] += 2 * pi;
		double t = b[i];
		for (int j = 0; j < 4; j++) {
			if (t >= 0 && t < pi/2) c[l++] = t;
			t += pi/2; if (t >= 2*pi) t -= 2*pi;
		}
	}
	std::sort(c, c+l);
	std::sort(d, d+n);
	int i1 = 0, i2 = std::lower_bound(d, d+n, std::make_pair(pi/2, 0))-d, i3 = std::lower_bound(d, d+n, std::make_pair(pi, 0))-d, i4 = std::lower_bound(d, d+n, std::make_pair(3*pi/2, 0))-d;
	double ans1 = 1e30, ans2 = 1e30;
	for (int i = 0; i+1 < l; i++)
		if (c[i+1] > c[i]+1e-10) {
			double mid = (c[i]+c[i+1])/2;
			while (i1 < n && d[i1].first < mid) i1++;
			while (i2 < n && d[i2].first < mid+pi/2) i2++;
			while (i3 < n && d[i3].first < mid+pi) i3++;
			while (i4 < n && d[i4].first < mid+pi*3/2) i4++;
			int j1 = d[i1%n].second, j2 = d[i2%n].second, j3 = d[i3%n].second, j4 = d[i4%n].second;
			double a1 = dis(a[j1%n]-a[j3%n]), a2 = dis(a[j2%n]-a[j4%n]), th1 = arg(a[j3%n]-a[j1%n]), th2 = arg(a[j4%n]-a[j2%n])-pi/2;
			double s = a1*a2*sin(th1-c[i])*sin(th2-c[i]);
			if (s < ans1) ans1 = s;
			double ll = c[i], rr = c[i+1];
			while (ll+1e-12 < rr) {
				double m1 = ll*(0.5+0.01)+rr*(0.5-0.01), m2 = ll*(0.5-0.01)+rr*(0.5+0.01);
				double s1 = a1*sin(th1-m1) + a2*sin(th2-m1), s2 = a1*sin(th1-m2) + a2*sin(th2-m2);
				if (s1 > s2) ll = m1;
				else rr = m2;
			}
			ll = (ll+rr)/2;
			s = a1*sin(th1-ll) + a2*sin(th2-ll);
			if (s < ans2) ans2 = s;
		}
	printf("%.12lf %.12lf\n", ans1, 2*ans2);
	return 0;
}
