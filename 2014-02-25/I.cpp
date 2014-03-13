#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
const double eps = 1e-10;

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
bool parallel(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
bool perpend(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}
double dis(point2 a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
point2 rotate(point2 a, double th) {
	point2 b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}

struct circle2 {
	point2 a;
	double r;
};
int circle_circle_cross(circle2 a, circle2 b, point2 *res1 = NULL, point2 *res2 = NULL) {
	double d = dis(a.a - b.a);
	point2 u = (b.a - a.a) / d;
	if (d / (a.r + b.r) > 1 + eps)
		return 0;
	else if (d / (a.r + b.r) > 1 - eps) {
		if (res1 != NULL) *res1 = a.a + u * a.r;
		return 1;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > eps) {
		double th = acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
		if (res1 != NULL) *res1 = a.a + rotate(u * a.r, th);
		if (res2 != NULL) *res2 = a.a + rotate(u * a.r, -th);
		return 2;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > -eps) {
		if (a.r / b.r < 1 - eps) {
			if (res1 != NULL) *res1 = b.a - u * b.r;
			return 1;
		} else if (a.r / b.r > 1 + eps) {
			if (res1 != NULL) *res1 = a.a + u * a.r;
			return 1;
		} else return -1;
	} else return 0;
}

circle2 a, b;
point2 c, d;
int main() {
	freopen("circles.in", "r", stdin);
	freopen("circles.out", "w", stdout);
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%lf%lf%lf%lf%lf%lf", &a.a.x, &a.a.y, &a.r, &b.a.x, &b.a.y, &b.r);
		int t = circle_circle_cross(a, b, &c, &d);
		printf("%d\n", t);
		if (t > 0) printf("%.12lf %.12lf\n", c.x, c.y);
		if (t > 1) printf("%.12lf %.12lf\n", d.x, d.y);
		puts("");
	}
	return 0;
}
