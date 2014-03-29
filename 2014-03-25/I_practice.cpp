#include <cstdio>
#include <cmath>
double h[10], ph[10], p[10];
int n;
void solve() {
	for (int i = 0; i < n; i++) scanf("%lf", &h[i]);
	for (int i = 0; i < n-1; i++) scanf("%lf", &ph[i]), ph[i] -= 1e-8;
	ph[n-1] = h[n-1];
	long double v1 = 0; for (int i = 1; i < n; i++) v1 += h[i];
	p[0] = 1;
	for (int i = 1; i < n; i++) {
		long double l = ph[i-1], r = h[i-1];
		while (l+1e-15 < r) {
			long double mid = (l+r)/2;
			long double pp;
			if (i == 1) pp = 1;
			else pp = p[i-1] * (h[i-1] - ph[i-1]) / (h[i-1] - mid);
			pp += (mid - ph[i]) * 0.097;
			long double pp2 = p[i-1] * (v1 - ph[i-1]) / (v1 - ph[i]);
			if (pp < pp2) l = mid;
			else r = mid;
		}
		long double h0 = (l+r)/2;
		for (int j = i-1; j > 0; j--) {
			long double l = ph[j-1], r = h[j-1];
			while (l+1e-15 < r) {
				long double mid = (l+r)/2;
				long double pp;
				if (j == 1) pp = 1;
				else pp = p[j-1] * (h[j-1] - ph[j-1]) / (h[j-1] - mid);
				pp += (mid - h0) * 0.097;
				long double pp2 = p[j] * (h[j] - ph[j]) / (h[j] - h0);
				if (pp < pp2) l = mid;
				else r = mid;
			}
			h0 = (l+r)/2;
		}
		if (fabs(h0 - h[0]) < 1e-14) {
			double ans = h[0];
			long double pp;
			for (int j = 1; j < i; j++) {
				long double l = ph[j], r = h[j];
				while (l+1e-15 < r) {
					long double mid = (l+r)/2;
					if (j == 1) pp = 1;
					else pp = p[j-1] * (h[j-1] - ph[j-1]) / (h[j-1] - h0);
					pp += (h0 - mid) * 0.097;
					long double pp2 = p[j] * (h[j] - ph[j]) / (h[j] - mid);
					if (pp < pp2) r = mid;
					else l = mid;
				}
				h0 = (l+r)/2;
				ans += h0;
			}
			if (fabs(h0 - ph[i-1]) < 1e-14) {
				long double hh;
				if (i == 1) hh = ph[i-1];
				else hh = v1 + h[i-1] - ph[i-1] - p[i-2] * (v1 + h[i-1] - ph[i-2]) / pp;
				ans += hh;
			} else {
				long double l = ph[i-1], r = ph[i];
				while (l+1e-15 < r) {
					long double mid = (l+r)/2;
					long double pp;
					if (i == 1) pp = 1;
					else pp = p[i-1] * (h[i-1] - ph[i-1]) / (h[i-1] - h0);
					pp += (h0 - mid) * 0.097;
					long double pp2 = p[i-1] * (v1 - ph[i-1]) / (v1 - mid);
					if (pp < pp2) r = mid;
					else l = mid;
				}
				ans += (l+r)/2;
			}
			printf("%.3lf\n", ans);
			break;
		} else {
			p[i] = p[i-1] * (v1 - ph[i-1]) / (v1 - 2*ph[i]);
			v1 -= h[i];
		}
	}
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve(), puts("");
	return 0;
}
