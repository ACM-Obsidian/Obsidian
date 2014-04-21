#include <cstdio>
#include <cstring>
double a[2][2], b[2][2], c[2][2], tmp1[2][2], tmp2[2][2];
void mul(double (*a)[2], double (*b)[2], double (*c)[2]) {
	c[0][0] = a[0][0]*b[0][0]+a[0][1]*b[1][0];
	c[0][1] = a[0][0]*b[0][1]+a[0][1]*b[1][1];
	c[1][0] = a[1][0]*b[0][0]+a[1][1]*b[1][0];
	c[1][1] = a[1][0]*b[0][1]+a[1][1]*b[1][1];
}
void pow(double (*a)[2], int n, double (*b)[2]) {
	memcpy(tmp1, a, 4*sizeof(double));
	b[0][0] = b[1][1] = 1, b[0][1] = b[1][0] = 0;
	while (n) {
		if (n & 1) {
			mul(b, tmp1, tmp2);
			memcpy(b, tmp2, 4*sizeof(double));
		}
		mul(tmp1, tmp1, tmp2);
		memcpy(tmp1, tmp2, 4*sizeof(double));
		n >>= 1;
	}
}
int t[100000], n;
char s[100000];
double p[100000];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %c %lf", &t[i], &s[i], &p[i]);
	double ans = 0, pl = 1, pr = 0;
	for (int i = 0; i < n; i++) {
		a[0][0] = a[1][1] = 1 - p[i], a[0][1] = a[1][0] = p[i];
		pow(a, t[i], b);
		double ql = b[0][0], qr = b[1][0];
		if (s[i] == 'R') { double tmp = ql; ql = qr; qr = tmp; }
		ans += pl * ql + pr * qr;
		pl = qr, pr = ql;
	}
	printf("%.10lf\n", ans);
	return 0;
}
