#include <cstdio>
#include <cstring>
#define P 20160508
int a[1001][10], f[1001], g[1001];
char xs[1002], ys[1002];
int x[1000], y[1000];
int k;
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s%s", xs, ys);
		int n = strlen(ys), m = strlen(xs);
		for (int i = 0; i < n-m; i++)
			x[i] = 0;
		for (int i = 0; i < m; i++)
			x[i+n-m] = xs[i]-'0';
		for (int i = 0; i < n; i++)
			y[i] = ys[i]-'0';
		scanf("%d", &k);
		for (int i = 0; i <= k; i++)
			for (int j = 0; j < 10; j++)
				a[i][j] = -1;
		a[0][0] = 0;
		int n1; scanf("%d", &n1);
		for (int i = 0; i < n1; i++) {
			int m, x;
			scanf("%d%d", &m, &x);
			a[0][m] = x;
		}
		scanf("%d", &n1);
		for (int i = 0; i < n1; i++) {
			int x0, m, x;
			scanf("%d%d%d", &x0, &m, &x);
			a[x0][m] = x;
		}
		int ca = 0, cb = 0;
		for (int i = 0; i <= k; i++)
			f[i] = 0;
		bool eq = true;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= k; j++)
				g[j] = 0;
			if (eq) {
				if (ca != -1)
					for (int j = x[i]+1; j < y[i]; j++)
						if (a[ca][j] != -1)
							g[a[ca][j]] = (g[a[ca][j]]+1)%P;
			} else {
				if (ca != -1)
					for (int j = x[i]+1; j <= 9; j++)
						if (a[ca][j] != -1)
							g[a[ca][j]] = (g[a[ca][j]]+1)%P;
				if (cb != -1)
					for (int j = 0; j < y[i]; j++)
						if (a[cb][j] != -1)
							g[a[cb][j]] = (g[a[cb][j]]+1)%P;
			}
			for (int j = 0; j <= k; j++)
				for (int k = 0; k <= 9; k++)
					if (a[j][k] != -1)
						g[a[j][k]] = (g[a[j][k]]+f[j])%P;
			memcpy(f, g, sizeof g);
			eq = eq && (x[i] == y[i]);
			if (ca != -1)
				ca = a[ca][x[i]];
			if (cb != -1)
				cb = a[cb][y[i]];
		}
		if (eq) {
			if (ca != -1)
				f[ca] = (f[ca]+1)%P;
		} else {
			if (ca != -1)
				f[ca] = (f[ca]+1)%P;
			if (cb != -1)
				f[cb] = (f[cb]+1)%P;
		}
		for (int i = 1; i <= k; i++)
			printf("%d\n", f[i]);
	}
	return 0;
}
