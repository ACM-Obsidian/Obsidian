#include <cstdio>
#include <cstring>
long double a[3001][3001], ans;
int n, ss, tt;
long long s, t;
int main() {
	freopen("bonus.in", "r", stdin);
	freopen("bonus.out", "w", stdout);
	scanf("%d%d%d", &n, &ss, &tt);
	s = ss, t = tt;
	s++;
	a[0][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i && j <= s; j++)
			if (a[i][j] > 0) {
				ans += a[i][j] * 2 / (2*s+t-j-i);
				a[i+1][j+1] += a[i][j] * (2*(s-j-1)) / (2*s+t-j-i);
				a[i+1][j] += a[i][j] * (t+j-i) / (2*s+t-j-i);
			}
	printf("%.12lf\n", (double)ans);
	ans = 0;
	s--, t++;
	memset(a, 0, sizeof a);
	a[0][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= i && j <= s; j++)
			if (a[i][j] > 0) {
				ans += a[i][j] / (2*s+t-j-i);
				a[i+1][j+1] += a[i][j] * (2*(s-j)) / (2*s+t-j-i);
				a[i+1][j] += a[i][j] * (t+j-i-1) / (2*s+t-j-i);
			}
	printf("%.12lf\n", (double)ans);
	return 0;
}
