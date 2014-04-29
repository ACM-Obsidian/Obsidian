#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
const double pi = 3.14159265358979324;
double f[31][30][30][30];
double d[30], d2[30];
int n, k;
int main() {
	freopen("delicious.in", "r", stdin);
	freopen("delicious.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%lf", &d[i]), d[i] = d[i] / 180 * pi;
	double ans = -1;
	if (k == 2) {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				double th = d[k] - d[j];
				if (th < 0) th += 2*pi;
				double tmp = std::min((th - sin(th)) / 2, pi - (th - sin(th)) / 2);
				if (tmp > ans) ans = tmp;
			}
		printf("%.10lf\n", ans);
		return 0;
	}
	for (int j = 0; j < n; j++)
		for (int k = 0; k < n; k++)
			for (int l = 0; l < n; l++)
				if (j != k && k != l && j != l) {
					double th1 = d[j] - d[k], th2 = d[l] - d[k];
					if (th1 < 0) th1 += 2*pi;
					if (th2 < 0) th2 += 2*pi;
					if (th1 > th2) std::swap(th1, th2);
					double s1 = (th1 - sin(th1)) / 2, s2 = pi - (th2 - sin(th2)) / 2, s3 = pi - s1 - s2;
					f[2][j][k][l] = std::min(std::min(s1, s2), s3);
				}
	for (int i = 2; i < k-1; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				for (int l = 0; l < n; l++)
					if (j != k && k != l && j != l) {
						int dir = 1;
						int p = k;
						while (p != l) {
							if (p == j) dir = -1;
							p = (p+1)%n;
						}
						p = (l+dir+n)%n;
						while (p != j) {
							double th = d[p] - d[l];
							if (dir < 0) th = -th;
							if (th < 0) th += 2*pi;
							double tmp = std::min(f[i][j][k][l], (th - sin(th)) / 2);
							if (tmp > f[i+1][j][l][p]) f[i+1][j][l][p] = tmp;
							p = (p+dir+n)%n;
						}
						dir = -dir;
						p = (l+dir+n)%n;
						while (p != j) {
							double th1 = d[p] - d[l];
							if (dir < 0) th1 = -th1;
							double th2 = d[k] - d[l];
							if (dir < 0) th2 = -th2;
							if (th1 < 0) th1 += 2*pi;
							if (th2 < 0) th2 += 2*pi;
							double tmp = std::min(f[i][j][k][l], std::min((th1 - sin(th1)) / 2, ((th2-th1) - (sin(th2)-sin(th1))) / 2));
							if (tmp > f[i+1][k][l][p]) f[i+1][k][l][p] = tmp;
							p = (p+dir+n)%n;
						}
					}
	for (int j = 0; j < n; j++)
		for (int kk = 0; kk < n; kk++)
			for (int l = 0; l < n; l++)
				if (f[k-1][j][kk][l] > ans) ans = f[k-1][j][kk][l];
	printf("%.10lf\n", ans);
	return 0;
}
