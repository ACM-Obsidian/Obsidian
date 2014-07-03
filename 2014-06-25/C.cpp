#include <cstdio>
#include <cstdlib>
#include <cmath>
struct point {
	int x, y;
} a[100];
point operator - (point a, point b) {
	point c; c.x = a.x - b.x, c.y = a.y - b.y; return c;
}
int operator % (point a, point b) {
	return a.x * b.y - a.y * b.x;
}
int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	int minx = ~0U>>1, maxx = 0;
	long long s = 0, x = 0, y = 0;
	for (int i = 0; i < n; i++)
		if (a[i].y == 0) {
			if (a[i].x < minx) minx = a[i].x;
			if (a[i].x > maxx) maxx = a[i].x;
		}
	for (int i = 0; i < n; i++) {
		int j = (i+1)%n;
		int gx = a[i].x + a[j].x, gy = a[i].y + a[j].y;
		int ts = a[i] % a[j];
		s += ts, x += 1LL * gx * ts, y += 1LL * gy * ts;
	}
	double xx = x / (3.0*s), yy = y / (3.0*s), ss = fabs((double)s)/2;
	double l = 0, r = 1e30;
	if (a[0].x == minx && xx < minx) puts("unstable");
	else if (a[0].x == maxx && xx > maxx) puts("unstable");
	else {
		double t = (xx - minx) / (minx - a[0].x) * ss;
		if (a[0].x < minx && t < r) r = t;
		else if (a[0].x > minx && t > l) l = t;
		t = (xx - maxx) / (maxx - a[0].x) * ss;
		if (a[0].x < maxx && t > l) l = t;
		else if (a[0].x > maxx && t < r) r = t;
		if (r <= l) puts("unstable");
		else {
			printf("%.0lf .. ", floor(l));
			if (r > 1e20) puts("inf");
			else printf("%.0lf\n", ceil(r));
		}
	}
	return 0;
}
