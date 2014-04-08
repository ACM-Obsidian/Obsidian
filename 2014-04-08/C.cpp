#include <cstdio>
#include <cmath>
const double pi = 3.14159265358979324;
struct point2 {
	double x, y;
};
point2 rotate(point2 a, double th) {
	point2 b;
	b.x = a.x * cos(th) - a.y * sin(th);
	b.y = a.x * sin(th) + a.y * cos(th);
	return b;
}
double dis(point2 a, point2 b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
struct point3 {
	double x, y, z;
	point3& operator += (point3 a) {
		x += a.x, y += a.y, z += a.z;
		return *this;
	}
	point3& operator -= (point3 a) {
		x -= a.x, y -= a.y, z -= a.z;
		return *this;
	}
	point3& operator *= (double a) {
		x *= a, y *= a, z *= a;
		return *this;
	}
	point3& operator /= (double a) {
		x /= a, y /= a, z /= a;
		return *this;
	}
};
point3 operator + (point3 a, point3 b) {
	point3 c; c = a, c += b; return c;
}
point3 operator - (point3 a, point3 b) {
	point3 c; c = a, c -= b; return c;
}
point3 operator * (point3 a, double b) {
	point3 c; c = a, c *= b; return c;
}
point3 operator / (point3 a, double b) {
	point3 c; c = a, c /= b; return c;
}
double operator * (point3 a, point3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
point3 operator % (point3 a, point3 b) {
	point3 c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}
double dis(point3 a) {
	return sqrt(a * a);
}
point2 pos(double th, double phi) {
	double r = 1.0 / (cos(phi)*cos(th)+cos(phi)*sin(th)+sin(phi));
	point3 tmp; tmp.x = r*cos(phi)*cos(th), tmp.y = r*cos(phi)*sin(th), tmp.z = r*sin(phi);
	tmp.x--;
	point3 tmp2; tmp2.x = -1, tmp2.y = 1, tmp2.z = 0;
	point2 res;
	res.y = dis(tmp % tmp2) / sqrt(2);
	res.x = sqrt(tmp * tmp - res.y * res.y);
	return res;
}
point2 pos2(double th, double phi) {
	while (th >= 90) th -= 90;
	point2 res = pos(th / 180 * pi, fabs(phi) / 180 * pi);
	if (phi < 0) res.x = sqrt(2) - res.x;
	return res;
}
double ans, th1, phi1, th2, phi2;
void solve1(double th1, double phi1, double th2, double phi2) {
	while (th1 >= 90) th1 -= 90, th2 -= 90;
	if (th2 < 0) th2 += 360;
	if (phi1 < 0) phi1 = -phi1, phi2 = -phi2;
	point2 p1 = pos2(th1, phi1), p2 = pos2(th2, phi2), tmp;
	if (phi2 >= 0 && th2 < 90) {
		double d = dis(p1, p2);
		if (d < ans) ans = d;
	} else if (phi2 >= 0 && th2 < 180) {
		tmp = rotate(p2, pi / 3);
		tmp.x += sqrt(2);
		double d = dis(p1, tmp);
		if (d < ans) ans = d;
	} else if (phi2 >= 0 && th2 < 270) {
		tmp = rotate(p2, pi / 3 * 2);
		tmp.x += sqrt(2)*1.5, tmp.y += sqrt(6)/2;
		double d = dis(p1, tmp);
		if (d < ans) ans = d;
	} else if (phi2 < 0 && th2 < 90) {
		tmp = rotate(p2, pi);
		tmp.x += sqrt(2);
		double d = dis(p1, tmp);
		if (d < ans) ans = d;
	} else if (phi2 < 0 && th2 < 180) {
		tmp = rotate(p2, -pi / 3 * 2);
		tmp.x += sqrt(2)*1.5, tmp.y += sqrt(6)/2;
		double d = dis(p1, tmp);
		if (d < ans) ans = d;
		tmp = rotate(p2, pi / 3 * 2);
		tmp.x += sqrt(2)*1.5, tmp.y -= sqrt(6)/2;
		d = dis(p1, tmp);
		if (d < ans) ans = d;
	} else if (phi2 < 0 && th2 < 270) {
		tmp = rotate(p2, -pi / 3);
		tmp.x += sqrt(2), tmp.y += sqrt(6);
		double d = dis(p1, tmp);
		if (d < ans) ans = d;
		tmp = rotate(p2, pi);
		tmp.x += sqrt(2)*2.5, tmp.y += sqrt(6)/2;
		d = dis(p1, tmp);
		if (d < ans) ans = d;
		tmp = rotate(p2, pi / 3);
		tmp.x += sqrt(2), tmp.y -= sqrt(6);
		d = dis(p1, tmp);
		if (d < ans) ans = d;
	}
}
void solve() {
	ans = 1e30;
	phi1 = 90 - phi1, phi2 = 90 - phi2;
	solve1(th1, phi1, th2, phi2);
	th1 = -th1; if (th1 < 0) th1 += 360;
	th2 = -th2; if (th2 < 0) th2 += 360;
	solve1(th1, phi1, th2, phi2);
	printf("%.3lf\n", 5*sqrt(2)*ans);
}
int main() {
	int _ = 0;
	while (scanf("%lf%lf%lf%lf", &th1, &phi1, &th2, &phi2), th1 != -1)
		printf("Case %d: ", ++_), solve();
	return 0;
}
