#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
struct point2 {
	int x, y;
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
point2 operator * (point2 a, int b) {
	point2 c; c = a; c *= b; return c;
}
point2 operator * (int a, point2 b) {
	point2 c; c = b; c *= a; return c;
}
point2 operator / (point2 a, int b) {
	point2 c; c = a; c /= b; return c;
}
long long operator * (point2 a, point2 b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
long long operator % (point2 a, point2 b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}
int parallel(point2 a, point2 b) {
	return a * a == 0 || b * b == 0 || a % b == 0;
}
typedef std::vector<point2> convex2;
int convex_gen(const convex2 &a, convex2 &b) {
	std::deque<point2> q;
	convex2 t(a);
	q.push_back(t[0]), q.push_back(t[1]);
	for (int i = 2; i < t.size(); i++) {
		while (q.size() > 1) {
			point2 p1 = t[i]-q[q.size()-1], p2 = q[q.size()-1]-q[q.size()-2];
			if (p1 % p2 > 0 || parallel(p1, p2)) q.pop_back();
			else break;
		}
		q.push_back(t[i]);
	}
	b.clear();
	for (int i = 0; i < q.size(); i++) b.push_back(q[i]);
}
std::pair<int, int> a[100000];
convex2 b;
int main() {
	freopen("caravan.in", "r", stdin);
	freopen("caravan.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);
	std::sort(a, a + n);
	int ansn = 10000000, ansd = 1;
	for (int i = 0, j = 0; i < n; i = j) {
		for (; j < n && (j == i || a[j].first <= a[j-1].second); j++);
		int tmpn, tmpd;
		if (j == i+1) {
			tmpn = a[i].second-a[i].first, tmpd = 1;
			if (1LL * tmpn * ansd < 1LL * ansn * tmpd) ansn = tmpn, ansd = tmpd;
		} else {
			b.clear();
			for (int k = i; k < j; k++) {
				point2 tmp; tmp.x = k+1, tmp.y = a[k].second;
				b.push_back(tmp);
			}
			convex_gen(b, b);
			for (int k = i; k < j; k++) {
				int l = 0, r = b.size();
				point2 tmp; tmp.x = k, tmp.y = a[k].first;
				while (l < r) {
					int mid = l+r>>1;
					if (b[mid].x <= k || mid+1 < b.size() && (b[mid]-tmp) % (b[mid+1]-b[mid]) < 0) l = mid+1;
					else r = mid;
				}
				tmpn = b[l].y - tmp.y, tmpd = b[l].x - tmp.x;
				if (1LL * tmpn * ansd < 1LL * ansn * tmpd) ansn = tmpn, ansd = tmpd;
			}
		}
	}
	int tmp = std::__gcd(ansn, ansd);
	ansn /= tmp, ansd /= tmp;
	printf("%d/%d\n", ansn, ansd);
	return 0;
}
