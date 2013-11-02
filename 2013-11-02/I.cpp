#include <cstdio>
int f[101], g[101][200], h[101][200], a[26][26], c[11], n, m, K, p, b[26];
char s[101];
int main() {
	freopen("parallel.in","r",stdin);
	freopen("parallel.out","w",stdout);
	scanf("%d%d%d%d", &n, &m, &K, &p);
	c[1] = K;
	for (int i = 2; i <= K; i++) c[i] = c[i-1]*(K-i+1);
	for (int i = 0; i < p; i++) {
		scanf("%s", s);
		a[s[0]-65][s[1]-65] = a[s[1]-65][s[0]-65] = 1;
	}
	scanf("%s", s);
	f[0] = 0, g[0][0] = 1, h[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) b[j] = 0;
		int j = i;
		for (; j > i-K && j > 0; j--) {
			int flag = 1;
			for (int k = 0; flag && k < m; k++)
				if (b[k] && !a[s[j-1]-65][k]) flag = 0;
			if (!flag) break;
			b[s[j-1]-65] = 1;
		}
		f[i] = f[j]+1;
		for (int k = j; k < i; k++)
			if (f[k]+1 == f[i]) {
				for (int l = 0, s, t = 0; l < 200; l++)
					s = g[i][l]+g[k][l]+t, s >= 10 ? (g[i][l] = s-10, t = 1) : (g[i][l] = s, t = 0);
				for (int l = 0, s, t = 0; l < 200; l++)
					s = h[i][l]+h[k][l]*c[i-k]+t, h[i][l] = s%10, t = s/10;
			}
	}
	printf("%d\n", f[n]);
	int i = 199; for (; i && !g[n][i]; i--); for (; i >= 0; i--) putchar(g[n][i]+48); puts("");
	i = 199; for (; i && !h[n][i]; i--); for (; i >= 0; i--) putchar(h[n][i]+48); puts("");
	return 0;
}
