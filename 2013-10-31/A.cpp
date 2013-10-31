#include <cstdio>
#include <cmath>
#include <algorithm>
const long double pi = 3.14159265358979324;
long double arg[200], x[200], y[200], p[200], ans, ansarg;
int n;
int cmpeq(long double a, long double b) {
	return fabs(a-b) < 1e-12;
}
void solve() {
	for (int i = 0; i < n; i++) {
		double tx, ty; scanf("%lf%lf", &tx, &ty);
		x[i] = tx, y[i] = ty;
	}
	if (n == 1) {
		printf("%.12lf\n%.12lf\n%.12lf %.12lf\n\n", 0.0, 0.0, (double)x[0], (double)y[0]);
		return;
	}
	for (int i = 0; i < n-1; i++) {
		arg[i] = atan2(y[i+1]-y[i], x[i+1]-x[i]);
		if (arg[i] < -1e-12) arg[i] += 2*pi;
		if (arg[i] < 1e-12) p[i] = arg[i];
		else p[i] = 2*pi-arg[i];
	}
	n--;
	std::sort(p, p+n);
	int l = std::unique(p, p+n, cmpeq)-p;
	p[l] = p[0]+2*pi;
	ans = 1e30;
	for (int i = 0; i < l; i++) {
		long double sum = 0;
		for (int j = 0; j < n; j++) sum += arg[j]+p[i];
		while (sum > 2*pi-1e-12) sum -= 2*pi;
		if (sum + (p[i+1]-p[i])*n > 2*pi-1e-12) {
			ans = 0, ansarg = p[i] + (2*pi-sum) / n;
			if (ansarg > 2*pi-1e-12) ansarg -= 2*pi;
			break;
		} else if (sum < ans)
			ans = sum, ansarg = p[i];
	}
	printf("%.12lf\n%.12lf\n", (double)ans, (double)ansarg);
	for (int i = 0; i <= n; i++) printf("%.12lf %.12lf\n", (double)(x[i]*cos(ansarg)-y[i]*sin(ansarg)), (double)(x[i]*sin(ansarg)+y[i]*cos(ansarg)));
	puts("");
}
int main() {
	freopen("angle.in","r",stdin);
	freopen("angle.out","w",stdout);
	for (; scanf("%d", &n), n; solve());
	return 0;
}
