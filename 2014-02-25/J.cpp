#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
const double eps = 1e-10;
const double pi = 3.14159265358979324;

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

struct line2 {
	point2 a, s;
};
struct circle2 {
	point2 a;
	double r;
};
int circle_circle_tangent(circle2 a, circle2 b, line2 *reso1 = NULL, line2 *reso2 = NULL, line2 *resi1 = NULL, line2 *resi2 = NULL) {
	double d = dis(a.a - b.a);
	point2 u = (b.a - a.a) / d;
	int cnt = 0;
	if ((d - fabs(a.r - b.r)) / (a.r + b.r) > eps) {
		double th = acos((a.r - b.r) / d);
		if (reso1 != NULL) {
			reso1->a = a.a + rotate(u * a.r, th);
			reso1->s = b.a + rotate(u * b.r, th) - reso1->a;
		}
		if (reso2 != NULL) {
			reso2->a = a.a + rotate(u * a.r, -th);
			reso2->s = b.a + rotate(u * b.r, -th) - reso2->a;
		}
		cnt += 2;
	} else if ((d - fabs(a.r - b.r)) / (a.r + b.r) > -eps) {
		if (a.r / b.r < 1 - eps) {
			if (reso1 != NULL) {
				reso1->a = b.a - u * b.r;
				reso1->s = rotate(u, pi / 2);
			}
			cnt++;
		} else if (a.r / b.r > 1 + eps) {
			if (reso1 != NULL) {
				reso1->a = a.a + u * a.r;
				reso1->s = rotate(u, pi / 2);
			}
			cnt++;
		} else return -1;
	}
	if (d / (a.r + b.r) > 1 + eps) {
		double th = acos((a.r + b.r) / d);
		if (resi1 != NULL) {
			resi1->a = a.a + rotate(u * a.r, th);
			resi1->s = b.a - rotate(u * b.r, th) - resi1->a;
		}
		if (resi2 != NULL) {
			resi2->a = a.a + rotate(u * a.r, -th);
			resi2->s = b.a - rotate(u * b.r, -th) - resi2->a;
		}
		cnt += 2;
	} else if (d / (a.r + b.r) > 1 - eps) {
		if (resi1 != NULL) {
			resi1->a = a.a + u * a.r;
			resi1->s = rotate(u, pi / 2);
		}
		cnt++;
	}
	return cnt;
}

circle2 a, b;
line2 res[4];
struct rec {
	double a, b, c;
} res2[4];
bool cmp(rec a, rec b) {
	return a.a < b.a-eps || fabs(a.a-b.a) < eps && (a.b < b.b-eps || fabs(a.b-b.b) < eps && a.c < b.c-eps);
}
int main() {
	freopen("circles2.in", "r", stdin);
	freopen("circles2.out", "w", stdout);
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%lf%lf%lf%lf%lf%lf", &a.a.x, &a.a.y, &a.r, &b.a.x, &b.a.y, &b.r);
		int t = circle_circle_tangent(a, b, &res[0], &res[1], &res[2], &res[3]);
		if (t == -1) {
			puts("-1\n");
			continue;
		}
		for (int i = 0; i < t; i++) {
			point2 c = res[i].a, d = res[i].a + res[i].s;
			res2[i].a = d.y - c.y, res2[i].b = c.x - d.x, res2[i].c = d % c;
			double r = hypot(res2[i].a, res2[i].b);
			res2[i].a /= r, res2[i].b /= r, res2[i].c /= r;
			if (res2[i].a < -eps || fabs(res2[i].a) < eps && res2[i].b < 0)
				res2[i].a = -res2[i].a, res2[i].b = -res2[i].b, res2[i].c = -res2[i].c;
		}
		std::sort(res2, res2+t, cmp);
		printf("%d\n", t);
		for (int i = 0; i < t; i++) printf("%.12lf %.12lf %.12lf\n", res2[i].a, res2[i].b, res2[i].c);
		puts("");
	}
	return 0;
}
