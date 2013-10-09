#include <cstdio>
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		double x, y, p, q;
		scanf("%lf%lf%lf%lf", &x, &y, &p, &q);
		double a = p*q*(x+y)+(1-q)*x;
		double b = p*(1-q)*(x+y)+q*y;
		if (a > b) printf("tiger %.4lf\n", a);
		else printf("wolf %.4lf\n", b);
	}
	return 0;
}