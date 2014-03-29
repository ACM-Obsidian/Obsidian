#include <cstdio>
#include <cmath>
#include <vector>
const double pi = 3.14159265358979324;
double x[10001], y[10001];
int n, th;
std::vector<std::pair<double, double> > a, b;
void solve() {
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &x[i], &y[i]);
	if (th == 0) {
		puts("Acceptable as proposed");
		return;
	}
	a.clear(), b.clear();
	for (int i = 0; i < n; i++) {
		double th = atan2(y[i+1]-y[i], x[i+1]-x[i]), thl = -pi/2-th, thr = pi/2-th;
		thl -= floor(thl / (2*pi)) * (2*pi);
		thr -= floor(thr / (2*pi)) * (2*pi);
		if (thl < thr) a.push_back(std::make_pair(thl, thr));
		else b.push_back(std::make_pair(thr, thl));
	}
	double l = 0, r = 2*pi;
	for (int i = 0; i < a.size(); i++) {
		if (a[i].first > l) l = a[i].first;
		if (a[i].second < r) r = a[i].second;
	}
	double ll = 2*pi, rr = 0;
	for (int i = 0; i < b.size(); i++) {
		if (b[i].first < ll) ll = b[i].first;
		if (b[i].second > rr) rr = b[i].second;
	}
	if (l > r+1e-12 || l > ll+1e-12 && r < rr-1e-12)
		puts("Unacceptable");
	else {
		double min, max;
		if (l > ll+1e-12 && l < rr-1e-12) min = rr;
		else min = l;
		if (r > ll+1e-12 && r < rr-1e-12) max = ll;
		else max = r;
		max = 2*pi-max;
		if (min < 1e-12) puts("Acceptable as proposed");
		else if (min < max) printf("Acceptable after counterclockwise rotation of %.2lf degrees\n", min/pi*180);
		else printf("Acceptable after clockwise rotation of %.2lf degrees\n", max/pi*180);
	}
}
int main() {
	int _ = 0;
	while (scanf("%d%d", &n, &th), n)
		printf("Case %d: ", ++_), solve(), puts("");
	return 0;
}
