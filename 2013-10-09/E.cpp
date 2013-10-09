#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 140;

struct Point {
	double x, y;
}a[MAXN];

int n, D, c[MAXN][MAXN], vis[MAXN], Limit, in[MAXN], p[MAXN];

void Dfs(int u) {
	vis[u] = true;
	for (int i = 1; i <= n; i++) if (in[i] && c[u][i] && !vis[i]) {
		Dfs(i);
	}
}

void clear(void) {
	memset(p, 0, sizeof p);
	memset(c, 0, sizeof c);
	memset(vis, 0, sizeof vis);
	memset(in, 0, sizeof in);
}

inline int dis(int i, int j) {
	return ceil(sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y)) - 1e-8);
}

int main(void) {
	//freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &D) == 2) {
		clear();
		for (int i = 1; i <= n; i ++) scanf("%lf%lf", &a[i].x, &a[i].y);
		if (D > 1000000000) {
			printf("1\n");
			continue;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (dis(i, j) <= D) {
				c[i][j] = true;
			}
		for (int i = n; i >= 1; i--) in[i] = true;
		for (Limit = n; Limit >= 1; Limit--) {
			memset(vis, 0, sizeof vis);
			Dfs(1);
			for (int i = 1; i <= n; i++) if (in[i] && !vis[i]) {
				in[Limit + 1] = true;
				break;
			}
			if (!in[Limit + 1]) {
				for (int i = 1; i <= n; i++) if (!in[i]) {
					int best = ~0U>>1;
					for (int j = 1; j <= n; j++) if (in[j] && best > dis(i, j)) {
						best = dis(i, j);
					}
					if ( 2 * best > D) {
						in[Limit + 1] = true;
						break;
					}
				}
			}
			in[Limit] = false;
		}
		if (in[n + 1]) {
			puts("-1");
		} else {
			in[1] = true;
			int t = n;
			while (in[t] == false && t > 1) t--;
			for (int i = t; i >= 1; i--) printf("%d", in[i]); puts("");
		}
	}
	return 0;
}