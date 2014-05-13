#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <deque>
using namespace std;

const double eps = 1e-13;
const double pi = 3.14159265358979324;

struct point2
{
	double x, y;
	point2 (void) {}
	point2 (double _x, double _y) : x(_x), y(_y) {}
	point2& operator+= (point2 a)
	{
		x += a.x, y += a.y;
		return *this;
	}
	point2& operator-= (point2 a)
	{
		x -= a.x, y -= a.y;
		return *this;
	}
	point2& operator*= (double a)
	{
		x *= a, y *= a;
		return *this;
	}
	point2& operator /= (double a)
	{
		x /= a, y /= a;
		return *this;
	}
};
point2 operator+ (point2 a, point2 b)
{
	point2 c; c = a; c += b; return c;
}
point2 operator- (point2 a, point2 b)
{
	point2 c; c = a; c -= b; return c;
}
point2 operator* (point2 a, double b)
{
	point2 c; c = a; c *= b; return c;
}
point2 operator* (double a, point2 b)
{
	point2 c; c = b; c *= a; return c;
}
double operator* (point2 a, point2 b)
{
	return a.x * b.x + a.y * b.y;
}
point2 operator/ (point2 a, double b)
{
	point2 c; c = a; c /= b; return c;
}
double operator% (point2 a, point2 b)
{
	return a.x * b.y - a.y * b.x;
}
double sqdis (point2 a)
{
	return a.x * a.x + a.y * a.y;
}
double dis (point2 a)
{
	return sqrt(sqdis(a));
}
double arg (point2 a)
{
	return atan2(a.y, a.x);
}
double arg (point2 a, point2 b)
{
	return acos(a * b / dis(a) / dis(b));
}

struct line2
{
	point2 a, s;
	void generate_pp (point2 _a, point2 _b)
	{
		a = _a, s = _b - _a;
	}
};
struct circle2
{
	point2 a; double r;
};
double point_line_dis (point2 a, line2 b, point2 *res = NULL)
{
	point2 p;
	p = b.a + ((a - b.a) * b.s) / (b.s * b.s) * b.s;
	if (res != NULL) *res = p;
	return dis(a - p);
}
int line_circle_cross (line2 a, circle2 b, point2 *res1 = NULL, point2 *res2 = NULL)
{
	point2 p;
	double d = point_line_dis(b.a, a, &p);
	if (d / b.r > 1 + eps) return 0;
	else if (d / b.r > 1 - eps)
	{
		if (res1 != NULL) *res1 = p;
		return 1;
	}
	else
	{
		d = sqrt(b.r * b.r - d * d) / dis(a.s);
		if (res1 != NULL) *res1 = p + d * a.s;
		if (res2 != NULL) *res2 = p - d * a.s;
		return 2;
	}
}
bool point_on_segment (point2 p, line2 a)
{
	double t = (p - a.a) * a.s / (a.s * a.s);
	return t > eps && t < 1 - eps;
}	
double fan_area (point2 a, point2 b, double r)
{
	double ag = arg(a, b);
	return 0.5 * ag * r * r;
}
double cross_upon_circle (point2 a, point2 b, double r)
{
	circle2 c;
	c.a = point2(0, 0), c.r = r;

	double sign = 1; 
	if (fabs(a % b) < eps) return 0;
	if (a % b < -eps) sign = -1;

	line2 l;
	if (dis(a - c.a) < dis(b - c.a)) swap(a, b);
	l.generate_pp(a, b);

	if (sqdis(a) > r * r + eps && sqdis(b) > r * r + eps) // Case 1 2 3
	{
		point2 p;
		double d = point_line_dis(c.a, l, &p);
		if (d / c.r > 1 - eps || !point_on_segment(p, l)) // Case 1 3
		{
//			printf("Case 1 3\n");
			return sign * fan_area(a, b, r);
		}
		else // Case 2
		{
//			printf("Case 2\n");
			point2 r1, r2;
			line_circle_cross(l, c, &r1, &r2);
			if (dis(r1 - a) > dis(r2 - a)) swap(r1, r2);
			return sign * (fan_area(r1, a, r) + fan_area(r2, b, r) + fabs((r1 % r2) * 0.5));
		}
	}
	else if (sqdis(a) <= r * r + eps && sqdis(b) <= r * r + eps) // Case 4
	{
//		printf("Case 4\n");
		return sign * fabs((a % b) * 0.5);
	}
	else // Case 5
	{
//		printf("Case 5\n");
		point2 r1, r2;
		line_circle_cross(l, c, &r1, &r2);
		if (!point_on_segment(r1, l)) swap(r1, r2);
//		printf("r1 = %lf %lf\n", r1.x, r1.y);
		return sign * (fan_area(a, r1, r) + fabs((r1 % b) * 0.5));
	}
}

point2 polygon[110];

int main ()
{
	int n, r; while (scanf("%d %d", &n, &r) == 2)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
		}
		double res = 0;
		for (int i = 0; i < n; i++)
		{
			int j = i + 1;
			if (j == n) j = 0;
			double t = cross_upon_circle(polygon[i], polygon[j], r);
//			printf("T = %lf\n", t);
			res += t;
		}
		printf("%.9lf\n", fabs(res));
	}
	return 0;
}
