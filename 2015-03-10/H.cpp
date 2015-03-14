#include <cstdio>
long long a[4][500];
int main() {
	freopen("polynomial.in", "r", stdin);
	freopen("polynomial.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%I64d", &a[0][i]);
		for (int i = 1; i < 4; i++)
			for (int j = 0; j < 4-i; j++)
				a[i][j] = a[i-1][j+1] - a[i-1][j];
		for (int j = 1; j < n; j++)
			a[3][j] = a[3][0];
		bool flag = true;
		for (int i = 2; i >= 0; i--)
			for (int j = 4-i; j < n; j++) {
				long long tmp = a[i][j-1] + a[i+1][j-1];
				if (i > 0)
					a[i][j] = tmp;
				else if (a[i][j] != tmp) {
					flag = false;
					break;
				}
			}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
