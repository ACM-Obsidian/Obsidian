#include <cstdio>
#include <algorithm>

struct point {
	long long x, y;
	point& operator += (point a) {
		x += a.x, y += a.y;
		return *this;
	}
	point& operator -= (point a) {
		x -= a.x, y -= a.y;
		return *this;
	}
	point& operator *= (long long a) {
		x *= a, y *= a;
		return *this;
	}
};
point operator + (point a, point b) {
	point c; c = a, c += b; return c;
}
point operator - (point a, point b) {
	point c; c = a, c -= b; return c;
}
point operator * (point a, long long b) {
	point c; c = a, c *= b; return c;
}
point operator * (long long a, point b) {
	point c; c = b, c *= a; return c;
}
long long operator * (point a, point b) {
	return a.x * b.x + a.y * b.y;
}
long long operator % (point a, point b) {
	return a.x * b.y - a.y * b.x;
}

long long floor(long long a, long long b) {
	if (b > 0) return a / b;
	else return a / b - (a % b ? 1 : 0);
}
long long ceil(long long a, long long b) {
	if (b > 0) return a / b + (a % b ? 1 : 0);
	else return a / b;
}
void ext_gcd(long long a, long long b, long long &x, long long &y) {
	if (!b) x = 1, y = 0;
	else if (!a) x = 0, y = 1;
	else if (a > b) ext_gcd(a % b, b, x, y), y += a / b * x;
	else ext_gcd(a, b % a, x, y), x += b / a * y;
}

int n;
point a[100000], ans;
long long s;

int main() {
	int x;
	scanf("%d%lld.%d", &n, &s, &x); n--;
	s *= 2;
	if (x) s++;
	for (int i = 0; i < n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
	for (int i = 0; i < n; i++) s -= a[i] % a[(i+1)%n];
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n, k = (i+n-1)%n, l = (i+2)%n;
		long long dx = a[j].x - a[i].x, dy = a[j].y - a[i].y;
		long long d = std::__gcd(std::abs(dx), std::abs(dy));
		if (s % d) continue;
		point v; v.x = dx / d, v.y = dy / d;
		long long s_ = s / d;
		point p;
		ext_gcd(std::abs(v.y), std::abs(v.x), p.x, p.y);
		if (v.y < 0) p.x = -p.x;
		if (v.x > 0) p.y = -p.y;
		if (v.y) {
			p *= s_ % v.y;
			p.x += s_ / v.y;
		} else {
			p *= s_ % v.x;
			p.y -= s_ / v.x;
		}
		p += a[i];
		long long R = ~0ULL>>2, L = -R, t;
		t = floor((a[i] - a[k]) % (a[i] - p), (a[i] - a[k]) % v) + 1;
		if (t > L) L = t;
		t = floor((a[j] - p) % (a[l] - a[j]) - 1, v % (a[l] - a[j]));
		if (t < R) R = t;
		if (v.x > 0) {
			t = ceil(-1000000 - p.x, v.x);
			if (t > L) L = t;
			t = floor(1000000 - p.x, v.x);
			if (t < R) R = t;
		} else if (v.x < 0) {
			t = floor(1000000 + p.x, -v.x);
			if (t < R) R = t;
			t = ceil(-1000000 + p.x, -v.x);
			if (t > L) L = t;
		} else {
			if (std::abs(p.x) > 1000000) continue;
		}
		if (v.y > 0) {
			t = ceil(-1000000 - p.y, v.y);
			if (t > L) L = t;
			t = floor(1000000 - p.y, v.y);
			if (t < R) R = t;
		} else if (v.y < 0) {
			t = floor(1000000 + p.y, -v.y);
			if (t < R) R = t;
			t = ceil(-1000000 + p.y, -v.y);
			if (t > L) L = t;
		} else {
			if (std::abs(p.y) > 1000000) continue;
		}
		if (L > R) continue;
		ans = p + L * v;
		break;
	}
	printf("%lld %lld\n", ans.x, ans.y);
	return 0;
}
