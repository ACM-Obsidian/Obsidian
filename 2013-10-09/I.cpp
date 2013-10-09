#include <cstdio>
#include <cmath>
#include <algorithm>
const double pi = 3.14159265358979324;
struct interval {
	double l, r;
} a[1000], b[1000];
double x[1001], y[1001], v[1001];
int n, f[1000];
int cmp(interval a, interval b) {
	return a.l < b.l || a.l == b.l && a.r < b.r;
}
int cmp2(interval a, interval b) {
	double len1 = a.r-a.l, len2 = b.r-b.l;
	if (len1 < 0) len1 += 2*pi;
	if (len2 < 0) len2 += 2*pi;
	return len1 < len2;
}
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%d", &n);
		for (int i = 0; i <= n; i++)
			scanf("%lf%lf%lf", &v[i], &x[i], &y[i]);
		int flag = 0;
		for (int i = 1; i <= n; i++)
			if (v[i] > v[0] || fabs(x[i]-x[0]) < 1e-8 && fabs(y[i]-y[0]) < 1e-8) {
				flag = 1;
				break;
			}
		if (flag) {
			puts("1");
			continue;
		}
		int m = 0;
		for (int i = 1; i <= n; i++) {
			if (v[i] == 0) continue;
			double arg = atan2(y[i]-y[0], x[i]-x[0]);
			double theta = asin(v[i]/v[0]);
			a[m].l = arg - theta, a[m].r = arg + theta;
			if (a[m].l <= -pi) a[m].l += 2*pi;
			if (a[m].r > pi) a[m].r -= 2*pi;
			f[m++] = 0;
		}
		n = m;
		std::sort(a, a+n, cmp2);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				if (a[i].l < a[i].r && a[j].l > a[i].l+1e-8 && a[j].l < a[i].r-1e-8 && a[j].r > a[i].l+1e-8 && a[j].r < a[i].r-1e-8)
					f[j] = 1;
				else if (a[i].l > a[i].r && (a[j].l > a[i].l+1e-8 || a[j].l < a[i].r-1e-8) && (a[j].r > a[i].l+1e-8 || a[j].r < a[i].r-1e-8))
					f[j] = 1;
				else if ((fabs(a[i].l-a[j].l) < 1e-8 || fabs(fabs(a[i].l-a[j].l)-2*pi) < 1e-8) && (fabs(a[i].r-a[j].r) < 1e-8 || fabs(fabs(a[i].r-a[j].r)-2*pi) < 1e-8))
					f[j] = 1;
		int l = 0;
		for (int i = 0; i < n; i++)
			if (!f[i]) a[l++] = a[i];
		n = l;
		int ans = ~0U>>1;
		std::sort(a, a+n, cmp);
		for (int i = 0; i < n; i++) {
			m = 0;
			for (int j = i+1; ; j++) {
				if (j == n) j = 0;
				if (j == i) break;
				b[m] = a[j];
				if (a[i].l < a[i].r && a[j].l > a[i].l+1e-8 && a[j].l < a[i].r-1e-8 || a[i].l > a[i].r && (a[j].l > a[i].l+1e-8 || a[j].l < a[i].r-1e-8))
					b[m].l = a[i].r;
				else if (a[i].l < a[i].r && a[j].r > a[i].l+1e-8 && a[j].r < a[i].r-1e-8 || a[i].l > a[i].r && (a[j].r > a[i].l+1e-8 || a[j].r < a[i].r-1e-8))
					b[m].r = a[i].l;
				b[m].l -= a[i].r, b[m].r -= a[i].r;
				if (b[m].l < 0) b[m].l += 2*pi;
				if (b[m].r < 0) b[m].r += 2*pi;
				m++;
			}
			double len = a[i].l - a[i].r;
			if (len < 0) len += 2*pi;
			int sum = 0;
			double l = 0;
			for (int j = 0, k = 0; j < m; j = k) {
				for (; k < m && b[k].l <= l+1e-8; k++);
				if (j == k) {
					sum = ans-1;
					break;
				}
				l = b[k-1].r;
				sum++;
				if (l >= len-1e-8) break;
			}
			if (l < len-1e-8) continue;
			if (sum+1 < ans) ans = sum+1;
		}
		if (ans > ~0U>>2) puts("0");
		else printf("%d\n", ans);
	}
	return 0;
}