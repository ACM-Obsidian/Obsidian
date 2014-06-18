#include <cstdio>
#include <cmath>
int u[10], n;
double xs, ys, vm, x[10], y[10], vx[10], vy[10], ans;
void dfs(int dep, double t, double xs, double ys) {
	if (t > ans) return;
	if (dep == n) {
		if (t < ans) ans = t;
	} else
		for (int i = 0; i < n; i++)
			if (!u[i]) {
				u[i] = 1;
				double x1 = x[i]+vx[i]*t-xs, y1 = y[i]+vy[i]*t-ys;
				double dt = ((vx[i]*x1+vy[i]*y1)+sqrt((x1*x1+y1*y1)*vm*vm-(vx[i]*y1-vy[i]*x1)*(vx[i]*y1-vy[i]*x1)))/(vm*vm-vx[i]*vx[i]-vy[i]*vy[i]);
				dfs(dep+1, t+dt, x[i]+vx[i]*(t+dt), y[i]+vy[i]*(t+dt));
				u[i] = 0;
			}
}
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%lf%lf%lf%d", &xs, &ys, &vm, &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf%lf%lf", &x[i], &y[i], &vx[i], &vy[i]);
		ans = 1e30;
		dfs(0, 0, xs, ys);
		printf("%.13lf\n", ans);
	}
	return 0;
}
