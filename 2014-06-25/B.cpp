#include <cstdio>
#include <deque>
#include <algorithm>
#define X first
#define Y second
long double f[251][10001];
std::deque<std::pair<long double, long double> > q[10000];
int n1, n2, a1[250], b1[250], w1[250], a2[250], b2[250];
char s[2];
long double cross(std::pair<long double, long double> a, std::pair<long double, long double> b, std::pair<long double, long double> c) {
	long double x1 = b.X-a.X, y1 = b.Y-a.Y, x2 = c.X-a.X, y2 = c.Y-a.Y;
	return x1*y2-x2*y1;
}
int main() {
	int d, w; scanf("%d%d", &d, &w);
	for (int i = 0; i < d; i++) {
		scanf("%s", s);
		int t, dt;
		if (s[0] == 'D') {
			scanf("%d%d%d", &w1[n1], &t, &dt);
			a1[n1] = dt, b1[n1] = dt + 2*t, n1++;
		} else {
			scanf("%d%d", &t, &dt);
			a2[n2] = dt, b2[n2] = 2*t, n2++;
		}
	}
	for (int j = 1; j <= w; j++) f[0][j] = -1e30;
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < w1[i]; j++) q[j].clear();
		for (int j = 0; j <= w; j++) {
			int k = j/w1[i], id = j%w1[i];
			while (q[id].size() > 1 && q[id][0].Y+k*q[id][0].X < q[id][1].Y+k*q[id][1].X) q[id].pop_front();
			f[i+1][j] = f[i][j];
			if (q[id].size() > 0) f[i+1][j] = std::max(f[i+1][j], q[id][0].Y+k*q[id][0].X-1.0*a1[i]*k*k+1.0*b1[i]*k);
			auto tmp = std::make_pair(2.0*a1[i]*k, -1.0*a1[i]*k*k-1.0*b1[i]*k+f[i][j]);
			if (a1[i] != 0) {
				while (q[id].size() > 1 && cross(q[id][q[id].size()-2], q[id][q[id].size()-1], tmp) > 0) q[id].pop_back();
				q[id].push_back(tmp);
			} else if (q[id].size() == 0 || tmp.Y > q[id][q[id].size()-1].Y) q[id].push_back(tmp);
		}
	}
	long double ans = -1e30;
	for (int j = 0; j <= w; j++) {
		if (f[n1][j] < -1e20) continue;
		if (j < w && n2 == 0) continue;
		long double l = -1e12, r = 1e12;
		while (r-l > 1e-12 && (l > 0 && l*(1+1e-12) < r || l < 0 && r*(1+1e-12) > l || l == 0)) {
			long double mid = (l+r)/2, sum = 0;
			for (int i = 0; i < n2; i++)
				if (a2[i] == 0 && b2[i] > mid) sum += 1e10;
				else if (a2[i] != 0 && b2[i] > mid) sum += (b2[i] - mid) / (2*a2[i]);
			if (sum < w-j) r = mid;
			else l = mid;
		}
		long double tmp = f[n1][j], s = 0;
		for (int i = 0; i < n2; i++)
			if (b2[i] > l && a2[i] != 0) {
				long double t = (b2[i] - l) / (2*a2[i]);
				tmp += -a2[i]*t*t+b2[i]*t;
				s += t;
			}
		int maxb = 0;
		for (int i = 0; i < n2; i++)
			if (a2[i] == 0 && b2[i] > l && b2[i] > maxb) maxb = b2[i];
		tmp += maxb*(w-j-s);
		if (tmp > ans) ans = tmp;
	}
	if (ans < -1e20) puts("impossible");
	else printf("%.10lf\n", (double)ans/2);
	return 0;
}
