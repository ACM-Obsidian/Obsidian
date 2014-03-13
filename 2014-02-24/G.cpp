#include <cstdio>
#include <cmath>
long double a[5][5], b[5][5];
int c[13][13];
int main() {
	c[0][0] = 1;
	for (int i = 1; i <= 12; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 0; j < i; j++)
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	}
	double p;
	while (scanf("%lf", &p), p >= 0) {
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				a[i][j] = 0;
		a[0][0] = a[4][4] = 1; a[0][1] = a[1][2] = a[2][3] = 1-p; a[2][1] = a[3][2] = a[4][3] = p;
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 5; j++)
				for (int k = 0; k < 5; k++)
					b[j][k] = 0;
			for (int j = 0; j < 5; j++)
				for (int k = 0; k < 5; k++)
					for (int l = 0; l < 5; l++)
						b[j][k] += a[j][l] * a[l][k];
			for (int j = 0; j < 5; j++)
				for (int k = 0; k < 5; k++)
					a[j][k] = b[j][k];
		}
		long double p2 = a[4][2];
		long double pg = ((c[5][3] * (1-p) + c[4][3]) * (1-p) + c[3][3]) * pow(p, 4) + c[6][3] * pow(p, 3) * pow(1-p, 3) * p2;
		long double pt = (((((c[11][6] * (1-p) + c[10][6]) * (1-p) + c[9][6]) * (1-p) + c[8][6]) * (1-p) + c[7][6]) * (1-p) + c[6][6]) * pow(p, 7) + c[12][6] * pow(p, 6) * pow(1-p, 6) * p2;
		long double ps = ((((c[9][5] * (1-pg) + c[8][5]) * (1-pg) + c[7][5]) * (1-pg) + c[6][5]) * (1-pg) + c[5][5]) * pow(pg, 6) + c[10][5] * pow(pg, 7) * pow(1-pg, 5) + 2 * c[10][5] * pow(pg, 6) * pow(1-pg, 6) * pt;
		long double pm = (1 + 2 * (1-ps)) * ps * ps;
		printf("%.11f %.11f %.11f\n", (double)pg, (double)ps, (double)pm);
	}
	return 0;
}
