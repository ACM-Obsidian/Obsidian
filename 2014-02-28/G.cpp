#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>
const double eps = 1e-10;
const double pi = 3.14159265358979324;
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
point operator / (point a, double b) {
	point c; c = a, c /= b; return c;
}
double operator * (point a, point b) {
	return a.x * b.x + a.y * b.y;
}
double operator % (point a, point b) {
	return a.x * b.y - a.y * b.x;
}
double dis(point a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
double arg(point a) {
	return atan2(a.y, a.x);
}
point rotate(point a, double th) {
	point b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}
int parallel(point a, point b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
int perpend(point a, point b) {
	return a * a < eps * eps || b * b < eps * eps || (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}

struct circle {
	point a;
	double r;
};
int circle_circle_cross(circle a, circle b, point *res1, point *res2) {
	double d = dis(a.a-b.a);
	point u = (b.a-a.a)/d;
	if (d > a.r+b.r+0.1)
		return 0;
	else if (d > a.r+b.r-0.1) {
		*res1 = a.a+u*a.r;
		return 1;
	} else if (d-fabs(a.r-b.r) > 0.1) {
		double th = acos((a.r*a.r+d*d-b.r*b.r)/(2*a.r*d));
		*res1 = a.a+rotate(u*a.r, th);
		*res2 = a.a+rotate(u*a.r, -th);
		return 2;
	} else if (d-fabs(a.r-b.r) > -0.1) {
		if (a.r < b.r-0.1) {
			*res1 = b.a-u*b.r;
			return 1;
		} else if (a.r > b.r+0.1) {
			*res1 = a.a+u*a.r;
			return 1;
		} else return -1;
	} else return 0;
}

int n, f[2]; double t;
point des, x[2];
circle a[10];
void out(point a) {
	if (dis(a-des) < 0.1) puts("Arrived");
	else {
		double th = arg(des-a);
		th = pi/2-th;
		if (th < -eps) th += 2*pi;
		th = th/pi*180;
		int d = int(round(th));
		if (d == 360) d = 0;
		//if (d == 1) puts("1 degree");
		/*else*/ printf("%d degrees\n", d);
	}
}
void solve() {
	for (int i = 0; i < n; i++) {
		double d, t2;
		scanf("%lf%lf%lf%lf", &a[i].a.x, &a[i].a.y, &d, &t2);
		d = pi/2-d/180*pi;
		point tmp; tmp.x = cos(d), tmp.y = sin(d);
		a[i].a += tmp*100*t2;
		a[i].r = (t-t2)*350;
	}
	int flag = -1, ret;
	for (int i = 1; i < n; i++)
		if ((ret = circle_circle_cross(a[0], a[i], &x[0], &x[1])) != -1) {
			flag = i;
			break;
		}
	if (flag == -1) {
		if (fabs(a[0].r) < 0.1) out(a[0].a);
		else puts("Inconclusive");
		return;
	}
	for (int i = 0; i < n; i++)
		if (fabs(a[i].r) < 0.1) {
			x[0] = a[i].a, ret = 1;
			break;
		}
	for (int i = 0; i < ret; i++) f[i] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < ret; j++)
			if (fabs(dis(x[j]-a[i].a)-a[i].r) > 0.1) f[j] = 0;
	int i = 0;
	for (int j = 0; j < ret; j++)
		if (f[j]) x[i++] = x[j];
	if (i == 2 && dis(x[0]-x[1]) < 0.1) i = 1;
	if (i == 0) puts("Inconsistent");
	else if (i == 2) puts("Inconclusive");
	else out(x[0]);
}
int main() {
	freopen("navigation.in", "r", stdin);
	int _ = 0;
	while (scanf("%d%lf%lf%lf", &n, &t, &des.x, &des.y), n)
		printf("Trial %d: ", ++_), solve();
	return 0;
}
