#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
const double pi = 3.14159265358979324;
double th1[2000], th2[2000], b[2000], x[2000], y[2000];
std::pair<std::pair<double, double>, int> a[2000];
int t[2001], t2[2001], f[2001], n;
std::vector<int> ansv;
double r;
int main() {
	scanf("%d%lf", &n, &r);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		double th = atan2(y[i], x[i]);
		double dth = acos(r / sqrt(x[i] * x[i] + y[i] * y[i]));
		th1[i] = th + dth; if (th1[i] > pi) th1[i] -= 2*pi;
		th2[i] = th - dth; if (th2[i] <= -pi) th2[i] += 2*pi;
		if (th1[i] > th2[i]) std::swap(th1[i], th2[i]);
	}
	int ans = 1;
	ansv.push_back(0);
	for (int i = 0; i < n; i++) {
		int l = 0, ans2 = -1;
		for (int j = 0; j < n; j++)
			if (i != j && (th1[j] < th1[i] || th1[j] > th2[i] || th2[j] < th1[i] || th2[j] > th2[i])
					&& (th1[j] > th1[i] && th1[j] < th2[i] || th2[j] > th1[i] && th2[j] < th2[i])) {
				if (th1[j] > th1[i] && th1[j] < th2[i]) {
					a[l].first.first = th1[j] - th1[i];
					a[l].first.second = th2[j] - th2[i];
				} else {
					a[l].first.first = th2[j] - th1[i];
					a[l].first.second = th1[j] - th2[i];
				}
				if (a[l].first.second < 0) a[l].first.second += 2*pi;
				a[l].second = j;
				l++;
			}
		std::sort(a, a + l);
		for (int j = 0; j < l; j++) b[j] = a[j].first.second;
		std::sort(b, b + l);
		for (int j = 1; j <= l; j++) t[j] = 0;
		for (int j = 0; j < l; j++) {
			int p = std::lower_bound(b, b + l, a[j].first.second) - b + 1;
			int v = 0, v2 = -1;
			for (int k = p; k; k -= k&-k)
				if (t[k] > v) v = t[k], v2 = t2[k];
			v++;
			f[a[j].second] = v2;
			if (v+1 > ans) ans = v+1, ans2 = a[j].second;
			for (int k = p; k <= l; k += k&-k)
				if (t[k] < v) t[k] = v, t2[k] = a[j].second;
		}
		if (ans2 != -1) {
			ansv.clear();
			while (ans2 != -1)
				ansv.push_back(ans2), ans2 = f[ans2];
			ansv.push_back(i);
		}
	}
	printf("%d\n", ans);
	for (int i = ansv.size()-1; i >= 0; i--)
		printf("%d%c", ansv[i]+1, " \n"[i == 0]);
	return 0;
}
