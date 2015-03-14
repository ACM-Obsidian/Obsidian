#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef double dbl;

const dbl eps = 1e-10;
inline int fi (dbl x) {
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}
struct pt {
	dbl x, y;
	pt (void) {}
	pt (dbl _x, dbl _y) : x(_x), y(_y) {}
	dbl cross (const pt& p) {
		return x * p.y - y * p.x;
	}
	bool operator< (const pt& p) const {
		if (fi(x - p.x)) return fi(x - p.x) < 0;
		else return fi(y - p.y) < 0;
	}
	dbl sq (void) {
		return x * x + y * y;
	}
};
pt operator- (const pt& a, const pt& b) {
	return pt(a.x - b.x, a.y - b.y);
}
struct seg { // [a, b)
	pt a, b;
	seg (void) {}
	seg (pt _a, pt _b) : a(_a), b(_b) {}
	bool _on (const pt& p) {
		dbl xl = min(a.x, b.x), xr = max(a.x, b.x);
		dbl yl = min(a.y, b.y), yr = max(a.y, b.y);
		if (fi(p.x - b.x) == 0 && fi(p.y - b.y) == 0) return false;
		else return fi(p.x - xl) >= 0 && fi(p.x - xr) <= 0 && fi(p.y - yl) >= 0 && fi(p.y - yr) <= 0;
	}
	bool on (const pt& p) {
		return fi((b - a).cross(p - a)) == 0 && _on(p);
	}
	pt v (void) {
		return b - a;
	}
};
bool segment_cross (seg s1, seg s2) {
	if (fi(s1.v().cross(s2.v())) == 0) {
		if (s1.on(s2.a) || s1.on(s2.b)) return -1;
		else return 0;
	} else {
		dbl u1 = (s1.a - s2.a).cross(s1.b - s2.a);
		dbl u2 = (s1.b - s2.b).cross(s1.a - s2.b);
		dbl v1 = (s2.a - s1.a).cross(s2.b - s1.a);
		dbl v2 = (s2.b - s1.b).cross(s2.a - s1.b);
		if (fi(u2) == 0 || fi(v2) == 0) return 0;
		else if (fi(u1) * fi(u2) >= 0 && fi(v1) * fi(v2) >= 0) return 1;
		else return 0;
	}
}

const int N = 100010;
pt arr[N]; seg cov[N];
pt arr2[N];

pt st[N];

int convex_hull (pt a[], int n) {
	sort(a, a + n);
	int covtop = 0;
	int top;
	top = 0;
	for (int i = 0; i < n; i++) {
		// printf("CVH: %lf %lf\n", a[i].x, a[i].y);
		while (top >= 2 && fi((st[top - 1] - st[top - 2]).cross(a[i] - st[top - 1])) <= 0) --top;
		st[top++] = a[i];
	}
	for (int i = 1; i < top; i++) {
		cov[covtop++] = seg(st[i], st[i - 1]);
	}
	top = 0;
	for (int i = n - 1; i >= 0; i--) {
		while (top >= 2 && fi((st[top - 1] - st[top - 2]).cross(a[i] - st[top - 1])) <= 0) --top;
		st[top++] = a[i];
	}
	for (int i = 1; i < top; i++) {
		cov[covtop++] = seg(st[i], st[i - 1]);
	}
	return covtop;
}

int main () {
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	int kase; for (scanf("%d", &kase); kase; --kase) {
		int n; scanf("%d", &n);
		pt s1, t1, s2, t2;
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &s1.x, &s1.y, &t1.x, &t1.y, &s2.x, &s2.y, &t2.x, &t2.y);
		n -= 4;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &arr[i].x, &arr[i].y);
		}
		seg u1(s1, t1), u2(s2, t2);
		if (segment_cross(u1, u2) || u1.on(t2) || u2.on(t1)) {
			if (n == 0) printf("IMPOSSIBLE\n");
			else {
				int ct, cnt;
				memcpy(arr2, arr, sizeof arr);
				arr2[n] = s1, arr2[n + 1] = t1; 
				ct = convex_hull(arr2, n + 2);
				cnt = 0;
				for (int i = 0; i < ct; i++) {
					int x = segment_cross(cov[i], u2);
					// printf("%lf %lf %lf %lf, %d\n", cov[i].a.x, cov[i].a.y, cov[i].b.x, cov[i].b.y, x);
					if (x == -1) {
						cnt = 1;
						break;
					} else {
						cnt += x;
					}
				}
				if (cnt <= 1) printf("POSSIBLE\n");
				else {
					memcpy(arr2, arr, sizeof arr);
					arr2[n] = s2, arr2[n + 1] = t2; 
					ct = convex_hull(arr2, n + 2);
					cnt = 0;
					for (int i = 0; i < ct; i++) {
						int x = segment_cross(cov[i], u1);
						if (x == -1) {
							cnt = 1;
							break;
						} else {
							cnt += x;
						}
					}
					if (cnt <= 1) printf("POSSIBLE\n");
					else printf("IMPOSSIBLE\n");
				}
			}
		} else {
			printf("POSSIBLE\n");
		}
	}
	return 0;
}
