#include <cstdio>
#include <cstring>
int a[4][8], s[32], b[32], cnt[8], cntall, now[8], u[8];
double p[8], f[8], fsum[8];
int g, m;
void dfs1(int ti, int tj, int dep) {
	if (dep == g) {
		cntall++;
		for (int i = 0; i < g; i++)
			if (now[i] == tj)
				cnt[i]++;
	} else {
		for (int i = 0; i < g; i++)
			if (!u[i] && b[a[ti][i]] != b[a[0][dep]]) {
				u[i] = 1;
				now[dep] = i;
				dfs1(ti, tj, dep+1);
				u[i] = 0;
			}
	}
}
void dfs2(int ti, int dep) {
	if (dep == g) {
		cntall++;
		for (int i = 0; i < g; i++)
			fsum[i] += s[a[ti][now[i]]];
	} else {
		for (int i = 0; i < g; i++)
			if (!u[i] && b[a[ti][i]] != b[a[0][dep]]) {
				u[i] = 1;
				now[dep] = i;
				dfs2(ti, dep+1);
				u[i] = 0;
			}
	}
}
int main() {
	freopen("cheating.in", "r", stdin);
	freopen("cheating.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &g, &m);
		for (int i = 0; i < g*m; i++) scanf("%d", &s[i]);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < g; j++)
				if (i != 0 || j != 0)
					scanf("%d", &a[i][j]);
		int c; scanf("%d", &c);
		for (int i = 0; i < c; i++) {
			int k, x; scanf("%d", &k);
			for (int j = 0; j < k; j++)
				scanf("%d", &x), b[x] = (k > g ? -x-1 : i);
		}
		int t, ti, tj; scanf("%d", &t);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < g; j++)
				if (a[i][j] == t) {
					ti = i, tj = j;
				}
		if (ti == 0) {
			for (int k = 0; k < g; k++)
				p[k] = (k == tj ? 1.0 : 0.0);
		} else {
			memset(cnt, 0, sizeof(cnt));
			cntall = 0;
			dfs1(ti, tj, 0);
			for (int i = 0; i < g; i++)
				p[i] = (double)cnt[i] / cntall;
		}
		memset(f, 0, sizeof f);
		for (int i = 0; i < m; i++)
			if (i != ti)
				if (i == 0) {
					for (int k = 0; k < g; k++)
						f[k] += s[a[0][k]];
				} else {
					cntall = 0;
					memset(fsum, 0, sizeof fsum);
					dfs2(i, 0);
					for (int k = 0; k < g; k++)
						f[k] += fsum[k] / cntall;
				}
		double ans = 0;
		for (int i = 0; i < g; i++)
			ans += f[i] * p[i];
		printf("%.3lf\n", ans);
	}
	return 0;
}
