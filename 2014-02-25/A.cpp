#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
const long double eps = 1e-12;

struct point2 {
	long double x, y;
	point2 (void) {}
	point2 (long double _x, long double _y) : x(_x), y(_y) {}
	point2& operator += (point2 a) {
		x += a.x, y += a.y;
		return *this;
	}
	point2& operator -= (point2 a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point2& operator *= (long double a) {
		x *= a, y *= a;
		return *this;
	}
	point2& operator /= (long double a) {
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
point2 operator * (point2 a, long double b) {
	point2 c; c = a; c *= b; return c;
}
point2 operator * (long double a, point2 b) {
	point2 c; c = b; c *= a; return c;
}
point2 operator / (point2 a, long double b) {
	point2 c; c = a; c /= b; return c;
}
long double operator * (point2 a, point2 b) {
	return a.x * b.x + a.y * b.y;
}
long double operator % (point2 a, point2 b) {
	return a.x * b.y - a.y * b.x;
}
bool parallel(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
bool perpend(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}
long double dis(point2 a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
point2 rotate(point2 a, long double th) {
	point2 b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}

struct line2 {
	point2 a, s;
	line2 (void) {}
	line2 (point2 _a, point2 _b) : a(_a), s(_b - _a) {}
};
int line_line_cross (line2 a, line2 b, point2 *res = NULL)
{
	if (parallel(a.s, b.s))
		if (parallel(b.a - a.a, a.s))
			return -1;
		else
			return 0;
	long double k1 = (b.a - a.a) % b.s / (a.s % b.s);
	if (res != NULL) *res = a.a + k1 * a.s;
	return 1;
}

bool point_on_segment (point2 a, point2 s1, point2 s2)
{
	return (s1 - a) * (s2 - a) / ((s2 - s1) * (s2 - s1)) <= eps;
}
long double len (line2 l)
{
	return dis(l.s);
}

int main ()
{
	freopen("segments.in", "r", stdin);
	freopen("segments.out", "w", stdout);
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		int x1, y1, x2, y2, x3, y3, x4, y4;
		scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		point2 s1(x1, y1), s2(x2, y2), s3(x3, y3), s4(x4, y4);
		line2 l1(s1, s2), l2(s3, s4);
		if (len(l1) < eps || len(l2) < eps)
		{
			if (len(l1) >= eps) std::swap(l1, l2);
			if (len(l2) < eps)
			{
				if (dis(l2.a - l1.a) < eps) puts("1");
				else puts("0");
			}
			else
			{
				if (parallel(l1.a - l2.a, l2.s) && point_on_segment(l1.a, l2.a, l2.a + l2.s)) puts("1");
				else puts("0");
			}
		}
		else
		{
			point2 tt;
			int res = line_line_cross(l1, l2, &tt);
			if (res == 0) puts("0");
			else if (res == -1)
			{
				long double t1, t2;
				t1 = (l2.a - l1.a) * l1.s / (l1.s * l1.s);
				t2 = (l2.a + l2.s - l1.a) * l1.s / (l1.s * l1.s);
				if (t1 > t2) std::swap(t1, t2);
				if (fabs(t1 - 1) < eps) puts("1");
				else if (fabs(t2) < eps) puts("1");
				else if (t1 > 1 + eps) puts("0");
				else if (t2 < -eps) puts("0");
				else puts("2");
			}
			else
			{
				if (point_on_segment(tt, l1.a, l1.a + l1.s) && point_on_segment(tt, l2.a, l2.a + l2.s)) puts("1");
				else puts("0");
			}
		}
	}
}
