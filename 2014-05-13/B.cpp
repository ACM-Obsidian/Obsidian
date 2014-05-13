#include <cstdio>
#include <cmath>
double eval(int l, double rat, double alp) {
	double pwrl = pow(rat, l), max = 0, pwrr = 1;
	for (int r = 0; r <= 100000; r++) {
		double tmp = (l*alp*(pwrr-1)+r*(1-pwrl))/(pwrr-pwrl);
		if (tmp > max) max = tmp;
		pwrr *= rat;
	}
	return max;
}
int main() {
	double x, p;
	while (scanf("%lf%lf", &x, &p) == 2) {
		if (p == 0) {
			puts("0.0");
			continue;
		}
		double rat = (100-p)/p, alp = 1-x/100, max = 0;
		int l1 = -1000000, r1 = 0;
		while (l1 < r1-2) {
			int mid1 = l1+r1>>1, mid2 = mid1+1;
			if (eval(mid1, rat, alp) <= eval(mid2, rat, alp)) l1 = mid1;
			else r1 = mid2;
		}
		for (int l = l1; l <= r1; l++) {
			double tmp = eval(l, rat, alp);
			if (tmp > max) max = tmp;
		}
		printf("%.10lf\n", max);
	}
	return 0;
}
