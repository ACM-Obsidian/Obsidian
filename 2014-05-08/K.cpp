#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 2510;

int f[MAXN][MAXN];

int a[10010][55], n, cnt[10010], c[MAXN], L = 0, kase;
vector<int> now;

int main(void) {
	while (scanf("%d", &n) == 1) {
		L = 0; memset(a, 0, sizeof a); memset(cnt, 0, sizeof cnt); memset(c, 0, sizeof c);
		now.clear();
		for (int i = 1; i <= n; i++) {
			int t, last = -1; scanf("%d", &t);
			for (int j = 1; j <= t; j++) {
				int x; scanf("%d", &x);
				if (x != last) cnt[x]++;
				a[x][i]++;
				now.push_back(x);
				last = x;
			}
		}
		sort(now.begin(), now.end());
		now.resize(unique(now.begin(), now.end()) - now.begin());
		memset(f, 0x3f, sizeof f);
		for (int i = 1; i <= n; i++) if (a[now[0]][i]) f[0][i] = cnt[now[0]];
		for (int i = 1; i < (int)now.size(); i++) {
			for (int j = 1; j <= n; j++) if (a[now[i]][j]) {
				for (int k = 1; k <= n; k++) {
					if (a[now[i]][k] && (j != k || cnt[now[i]] == 1)) {
						f[i][j] = min(f[i][j], f[i - 1][k] + cnt[now[i]] - 1);
					} else f[i][j] = min(f[i][j], f[i - 1][k] + cnt[now[i]]);
				}
			}
		}
		int Ans = ~0u>>1;
		for (int i = 1; i <= n; i++) Ans = min(Ans, f[now.size() - 1][i]);
//		printf("%d\n", Ans);
		printf("Case %d: %d\n", ++kase, Ans * 2 - n - 1);
	}
	return 0;
}

