#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
const double pi = 3.14159265358979324;
double x[50000], y[50000], r[50000], th[50000];
std::vector<std::pair<double, double> > a, b;
int main() {
	freopen("tower.in", "r", stdin);
	freopen("tower.out", "w", stdout);
	int n, m; scanf("%d%d", &n, &m);
	double ll = 0, rr = 0, k = 2 * pi / m;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		r[i] = hypot(x[i], y[i]);
		th[i] = atan2(y[i], x[i]);
		if (th[i] < 0) th[i] += 2 * pi;
		if (r[i] > rr) rr = r[i];
	}
	ll = rr * cos(pi / m);
	while (rr > ll * (1+1e-10)) {
		double mid = (ll + rr) / 2;
		a.clear(), b.clear();
		for (int i = 0; i < n; i++) {
			if (r[i] <= mid+1e-10) continue;
			double th0 = th[i], dth = acos(mid / r[i]);
			double th1 = th0 + dth, th2 = th0 + k - dth;
			th1 -= int(th1 / k) * k, th2 -= int(th2 / k) * k;
			if (th1 < th2) a.push_back(std::make_pair(th1, th2));
			else b.push_back(std::make_pair(th2, th1));
		}
		double tl = 0, tr = k;
		for (int i = 0; i < a.size(); i++) {
			if (a[i].first > tl) tl = a[i].first;
			if (a[i].second < tr) tr = a[i].second;
		}
		if (tl > tr) {
			ll = mid;
			continue;
		}
		int flag = 1;
		if (b.size()) {
			std::sort(b.begin(), b.end());
			flag = 0;
			if (!(tr <= 0 || tl >= b[0].first))
				flag = 1;
			double ur = b[0].second;
			for (int i = 1; !flag && i < b.size(); i++)
				if (b[i].first > ur) {
					if (!(tr <= ur || tl >= b[i].first))
						flag = 1;
					ur = b[i].second;
				} else if (b[i].second > ur) ur = b[i].second;
			if (!flag && !(tr <= ur || tl >= k))
				flag = 1;
		}
		if (flag) rr = mid;
		else ll = mid;
	}
	printf("%.12lf\n", (ll + rr) / 2 / cos(pi / m));
	return 0;
}
