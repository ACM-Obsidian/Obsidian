#include <cstdio>
#include <cmath>
int n, b, p[10], d;
double h[10];
int main() {
	scanf("%d%d%d", &d, &n, &b), b++;
	for (int i = 0; i < n; i++)
		scanf("%d%lf", &p[i], &h[i]);
	double min = 1e10;
	for (int i = 1; i <= b; i++) {
		double mina = 0, c = 1.0 * d / i;
		bool flag = true;
		for (int j = 0; j < n; j++) {
			if (p[j] * i % d == 0) {
				flag = false;
				break;
			}
			double x = p[j] - p[j] * i / d * c;
			double t = h[j] / (x * (c - x));
			if (t > mina) mina = t;
		}
		if (!flag) continue;
		double ans;
		if (mina < 1.0 / c) ans = sqrt(c);
		else ans = sqrt(0.5 / mina + c * c * mina * 0.5);
		if (ans < min) min = ans;
	}
	printf("%lf\n", min);
	return 0;
}
