#include <cstdio>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>

struct point2 {
	long long x, y;
	point2& operator += (point2 a) {
		x += a.x, y += a.y;
		return *this;
	}
	point2& operator -= (point2 a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point2& operator *= (long long a) {
		x *= a, y *= a;
		return *this;
	}
};
point2 operator + (point2 a, point2 b) {
	point2 c; c = a; c += b; return c;
}
point2 operator - (point2 a, point2 b) {
	point2 c; c = a; c -= b; return c;
}
point2 operator * (point2 a, long long b) {
	point2 c; c = a; c *= b; return c;
}
point2 operator * (long long a, point2 b) {
	point2 c; c = b; c *= a; return c;
}
long long operator * (point2 a, point2 b) {
	return a.x * b.x + a.y * b.y;
}
long long operator % (point2 a, point2 b) {
	return a.x * b.y - a.y * b.x;
}
bool parallel(point2 a, point2 b) {
	return a * a == 0 || b * b == 0 || a % b == 0;
}
bool perpend(point2 a, point2 b) {
	return a * a == 0 || b * b == 0 || a * b == 0;
}
typedef std::vector<point2> convex2;
bool convex_gen_cmp(point2 a, point2 b) {
	return a.y < b.y || a.y == b.y && a.x < b.x;
}
void convex_gen(const convex2 &a, convex2 &b) {
	std::deque<point2> q;
	convex2 t(a);
	std::sort(t.begin(), t.end(), convex_gen_cmp);
	q.push_back(t[0]), q.push_back(t[1]);
	for (int i = 2; i < t.size(); i++) {
		while (q.size() > 1) {
			point2 p1 = t[i]-q[q.size()-1], p2 = q[q.size()-1]-q[q.size()-2];
			if (p1 % p2 > 0 || parallel(p1, p2)) q.pop_back();
			else break;
		}
		q.push_back(t[i]);
	}
	int pretop = q.size();
	for (int i = t.size()-1; i >= 0; i--) {
		while (q.size() > pretop) {
			point2 p1 = t[i]-q[q.size()-1], p2 = q[q.size()-1]-q[q.size()-2];
			if (p1 % p2 > 0 || parallel(p1, p2)) q.pop_back();
			else break;
		}
		q.push_back(t[i]);
	}
	q.pop_back();
	if (q.size() < 3) {
		b.clear();
		return;
	}
	b.clear();
	for (int i = 0; i < q.size(); i++) b.push_back(q[i]);
}

int n;
convex2 a, b;
int main() {
	freopen("convex.in", "r", stdin);
	freopen("convex.out", "w", stdout);
	scanf("%d", &n);
	point2 tmp;
	for (int i = 0; i < n; i++) {
		scanf("%I64d%I64d", &tmp.x, &tmp.y);
		a.push_back(tmp);
	}
	convex_gen(a, b);
	if (b.size() == 0) {
		point2 min = a[0], max = a[0];
		for (int i = 1; i < n; i++) {
			if (convex_gen_cmp(a[i], min)) min = a[i];
			if (convex_gen_cmp(max, a[i])) max = a[i];
		}
		if (min.x == max.x && min.y == max.y) printf("1\n%I64d %I64d\n", min.x, min.y);
		else printf("2\n%I64d %I64d\n%I64d %I64d\n", min.x, min.y, max.x, max.y);
	} else {
		printf("%d\n", b.size());
		for (int i = 0; i < b.size(); i++) printf("%I64d %I64d\n", b[i].x, b[i].y);
	}
	return 0;
}
