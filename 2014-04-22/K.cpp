#include <cstdio>
#include <cmath>
#include <cstdlib>
int x[100], y[100], n;
void solve() {
	for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
	double ans = 1e30;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++) {
			int flag = 0, flag2 = 1;
			int dis = 0;
			for (int k = 0; k < n; k++) {
				int cross = (x[k] - x[i]) * (y[j] - y[i]) - (y[k] - y[i]) * (x[j] - x[i]);
				if (cross != 0) {
					int sgn = (cross > 0 ? 1 : -1);
					if (flag != 0 && sgn != flag) {
						flag2 = 0; break;
					}
					flag = sgn;
				}
				if (abs(cross) > dis) dis = abs(cross);
			}
			if (!flag2) continue;
			double tmp = dis / sqrt((x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]));
			if (tmp < ans) ans = tmp;
		}
	printf("%.2lf\n", ans + 0.005 - 1e-12);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
