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
	point2 c; c = a, c += b; return c;
}
point2 operator - (point2 a, point2 b) {
	point2 c; c = a, c -= b; return c;
}
point2 operator * (point2 a, double b) {
	point2 c; c = a, c *= b; return c;
}
point2 operator * (double a, point2 b) {
	point2 c; c = b, c *= a; return c;
}
point2 operator / (point2 a, double b) {
	point2 c; c = a, c /= b; return c;
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
int parallel(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a % b) * (a % b) / ((a * a) * (b * b)) < eps * eps;
}
int perpend(point2 a, point2 b) {
	return a * a < eps * eps || b * b < eps * eps || (a * b) * (a * b) / ((a * a) * (b * b)) < eps * eps;
}

struct line2 {
	point2 a, s;
};
typedef std::vector<point2> convex2;
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
int halfplane_cross_cmp(line2 a, line2 b) {
	double c1 = arg(a.s), c2 = arg(b.s);
	return c1 < c2-eps || fabs(c1-c2) < eps && b.s % (a.a-b.a) / dis(b.s) > eps;
}
int halfplane_cross(const std::vector<line2> &a, convex2 &b) {
	std::vector<line2> t(a);
	std::sort(t.begin(), t.end(), halfplane_cross_cmp);
	int j = 0;
	for (int i = 0; i < t.size(); i++)
		if (!i || arg(t[i].s) > arg(t[i-1].s)+eps) t[j++] = t[i];
	if (j > 0 && arg(t[j].s) > arg(t[0].s) + 2*pi - eps) j--;
	t.resize(j);
	std::deque<line2> q;
	q.push_back(t[0]), q.push_back(t[1]);
	point2 p;
	for (int i = 2, k = 0; i < t.size(); i++) {
		for (; k < q.size() && t[i].s % q[k].s > 0; k++);
		point2 s1 = q[q.size()-1].s, s2 = q[0].s;
		if (k > 0 && k < q.size()) {
			line_line_cross(q[k], q[k-1], &p);
			double r1 = t[i].s % (p - t[i].a) / dis(t[i].s);
			if (r1 < eps) {
				b.clear();
				return 0;
			}
		}
		if (s1 % s2 > 0 && !parallel(s1, s2)) {
			line_line_cross(q[0], q[q.size()-1], &p);
			double r2 = t[i].s % (p - t[i].a) / dis(t[i].s);
			if (r2 > -eps)
				continue;
		}
		while (q.size() > 1) {
			line_line_cross(q[q.size()-1], q[q.size()-2], &p);
			if (t[i].s % (p - t[i].a) / dis(t[i].s) < eps) {
				q.pop_back();
				if (k == q.size()) k--;
			} else break;
		}
		while (q.size() > 1) {
			line_line_cross(q[0], q[1], &p);
			if (t[i].s % (p - t[i].a) / dis(t[i].s) < eps) {
				q.pop_front();
				k--; if (k < 0) k = 0;
			} else break;
		}
		q.push_back(t[i]);
	}
	b.clear();
	for (int i = 0; i < q.size(); i++) {
		line_line_cross(q[i], q[(i+1)%q.size()], &p);
		b.push_back(p);
	}
	return 1;
}

int n;
convex2 a;
std::vector<line2> b;
void solve() {
	point2 tmp;
	a.clear();
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &tmp.x, &tmp.y);
		a.push_back(tmp);
	}
	b.resize(n);
	for (int i = 0; i < n; i++)
		b[i].a = a[i], b[i].s = a[(i+1)%n] - a[i];
	printf("%d\n", halfplane_cross(b, a));
}

int main() {
	freopen("B.txt", "r", stdin);
	while (scanf("%d", &n), n) solve();
	return 0;
}
