#include <cstdio>
double s[201][200];
double p[200][200];
int main() {
	freopen("epidemic.in", "r", stdin);
	freopen("epidemic.out", "w", stdout);
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; _++) {
		int n, k, t; scanf("%d%d%d", &n, &k, &t);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%lf", &p[i][j]);
		printf("Case #%d:\n", _);
		s[0][0] = 1;
		for (int i = 1; i <= k; i++) {
			for (int j = 0; j < n; j++) {
				double sp = 1;
				for (int q = 0; q < n; q++)
					sp *= 1 - (s[i-1][q] - (i >= t ? s[i-t][q] : 0)) * p[q][j];
				s[i][j] = s[i-1][j] + (1 - s[i-1][j]) * (1 - sp);
			}
			double sum = 0;
			for (int j = 0; j < n; j++)
				sum += s[i][j] - (i >= t ? s[i-t][j] : 0);
			printf("  Day %d, average number of unhealthy people equals %.8lf\n", i, sum);
		}
	}
	return 0;
}
