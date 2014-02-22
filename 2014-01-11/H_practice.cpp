//I suspect that the judger in Codeforces is problematic. This program can pass local test.
#include <cstdio>
#include <cmath>
const double eps = 1e-8;
struct point2 {
	double x, y;
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
point2 rotate(point2 a, double th) {
	point2 b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}
int parallel(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps
		|| (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
int perpend(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps
		|| (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}
struct line2 {
	point2 a, s;
};
double point_line_dis(point2 a, line2 b, point2 *res = NULL) {
	point2 p;
	p = b.a + ((a - b.a) * b.s) / (b.s * b.s) * b.s;
	if (res != NULL) *res = p;
	return dis(a - p);
}
line2 l1, l2;
point2 p1, p2;
double f(double x) {
	point2 q;
	line2 tmp;
	tmp.a = (p1 + l1.a + x * l1.s) / 2;
	tmp.s = l1.a + x * l1.s - p1;
	double t = tmp.s.y; tmp.s.y = tmp.s.x, tmp.s.x = -t;
	point_line_dis(p2, tmp, &q);
	q = 2 * q - p2;
	return l2.s % (q - l2.a);
}
int line_line_cross(line2 a, line2 b, point2 *res = NULL) {
	if (parallel(a.s, b.s))
		if (parallel(b.a - a.a, a.s))
			return -1;
		else
			return 0;
	double k1 = (b.a - a.a) % b.s / (a.s % b.s);
	if (res != NULL) *res = a.a + k1 * a.s;
	return 1;
}
void solve() {
	point2 a, b;
	scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
	l1.a = a, l1.s = b - a;
	scanf("%lf%lf", &p1.x, &p1.y);
	scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
	l2.a = a, l2.s = b - a;
	scanf("%lf%lf", &p2.x, &p2.y);
	double l = -100000, r = 100000;
	if (parallel(l1.s, l2.s)) {
		point2 q;
		if (dis(p1 - p2) < point_line_dis(l1.a, l2) - eps || fabs(dis(p1 - p2) - point_line_dis(l1.a, l2, &q)) < eps && parallel(p2 - p1, q - l1.a) && (p2 - p1) * (q - l1.a) > 0) {
			puts("0 0 0 0");
			return;
		}
		if (perpend(p2 - p1, l1.s)) {
			point_line_dis(p1, l1, &q);
			l = (q - l1.a) * l1.s / (l1.s * l1.s);
			r = 100000;
		} else {
			double d = point_line_dis(p1, l1, &q);
			q = (q - p1) / d * dis(p2 - p1) + p1;
			q = (q + p2) / 2;
			line2 l3; l3.a = p1, l3.s = q - p1;
			point2 q1, q2;
			line_line_cross(l3, l1, &q1);
			double t = l3.s.x; l3.s.x = l3.s.y, l3.s.y = -t;
			line_line_cross(l3, l1, &q2);
			l = (q1 - l1.a) * l1.s / (l1.s * l1.s);
			r = (q2 - l1.a) * l1.s / (l1.s * l1.s);
			if (l > r) t = l, l = r, r = t;
		}
	}
	double fl = f(l), fr = f(r);
	if (fabs(fl) < eps) ;
	else if (fabs(fr) < eps) l = r;
	else {
		if (fl * fr > 0) {
			puts("0 0 0 0");
			return;
		}
		while (fabs(r-l) >= 1e-12) {
			double mid = (l+r)/2, fmid = f(mid);
			if (fmid * fl > 0) l = mid, fl = fmid;
			else r = mid, fr = fmid;
		}
	}
	line2 ans;
	ans.a = (p1 + l1.a + l * l1.s) / 2;
	ans.s = l1.a + l * l1.s - p1;
	double t = ans.s.y; ans.s.y = ans.s.x, ans.s.x = -t;
	a = ans.a, b = ans.s + ans.a;
	printf("%lf %lf %lf %lf\n", a.x, a.y, b.x, b.y);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
