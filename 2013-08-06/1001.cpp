#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double eps = 1e-6, inf = 1000000000;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

template<class T> inline int sign(T x) { if (x < -eps) return -1; else if (x > eps) return 1; else return 0;}
struct Point {
    double x, y;
    Point():x(0),y(0){}
    Point(double x, double y):x(x), y(y){}
    inline Point operator +(const Point& oth) const {
        return Point(x + oth.x, y + oth.y);
    }
    inline Point operator -(const Point& oth) const {
        return Point(x - oth.x, y - oth.y);
    }
	inline Point operator *(const double k) const {
		return Point(x * k, y * k);
	}
	inline Point operator /(const double k) const {
		return Point(x / k, y / k);
	}
	inline double len(void) const {
		return sqrt(x*x + y*y);
	}
	inline Point Resize(void) const {
		Point ret = *this;
		return ret / ret.len();
	}
    inline double operator ^(const Point& oth) const {
        return (double) x * oth.y - (double) oth.x * y;
    }
	inline double rotate(const Point& a, const Point& b) const {
		return sign((a - *this) ^ (b - *this));
	}
};

struct Line {
	double A, B, C;
	Line():A(0), B(0), C(0){}
	Line(double A, double B, double C):A(A), B(B), C(C){}
};

inline Point Intersect(const Line& x, const Line& y) {
	double Y = ((x.A * y.C) - (y.A * x.C)) / ((y.A * x.B) - (x.A * y.B));
	double X = - (x.B * Y + x.C) / x.A;
	return Point(X, Y);
}

inline Line getMid(Point a, Point b) {
	double A = b.x - a.x, B = b.y - a.y, C = - ((a.x + b.x) * (b.x - a.x) - (a.y + b.y) * (a.y - b.y)) / 2.0;
	return Line(A, B, C);
}

const int MAXN = 55;

Point station[MAXN], city[MAXN];

int n, m;

inline int get(const Point& now) {
	double best = inf, tmp; int ret = 0;
	for (int i = 1; i <= m; i++) if ((tmp = (now - station[i]).len()) < best) {
		ret = i;
		best = tmp;
	}
	return ret;
}

inline int Cal(const Point& x, const Point& y) {
	if (get(x) == get(y)) return 0;
	if ((x - y).len() < 1e-6) return 1;
	Point mid = (x + y) / 2;
	return Cal(x, mid) + Cal(mid, y);
}

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++) scanf("%lf%lf", &city[i].x, &city[i].y);
		for (int i = 1; i <= m; i++) scanf("%lf%lf", &station[i].x, &station[i].y);
		int q; scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			int l1 = ScanInt(), l2 = ScanInt();
			Point x = city[l1], y = city[l2];
			printf("%d\n", Cal(x, y));
		}
	}
	return 0;
}

