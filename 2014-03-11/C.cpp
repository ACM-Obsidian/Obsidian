#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 25;

int n, vt, m, k, vs[MAXN], inf;
int map[MAXN][MAXN]; long long a[MAXN][MAXN];
long long f[1 << 10][MAXN];
pair<long long, int> g[1 << 10][MAXN];
int stack[MAXN], top, Ans[MAXN][MAXN], len[MAXN], pow[1 << 20];

priority_queue<pair<long long, int> > Q;

void Dfs(int S, int u) {
	if (g[S][u].second == -1) {
		while (S) {
			int tmp = S & -S;
			memcpy(Ans[pow[tmp]], stack, sizeof(int) * top);
			len[pow[tmp]] = top;
			Ans[pow[tmp]][len[pow[tmp]]++] = u;
			S -= tmp;
		}
		return;
	}
	if (top == 0 || stack[top - 1] != u) stack[top++] = u;
	if (g[S][u].second == u) {
		Dfs(g[S][u].first, u);
		Dfs(S - g[S][u].first, u);
	} else {
		Dfs(g[S][u].first, g[S][u].second);
	}
	if (top != 0 && stack[top - 1] == u) stack[--top] = 0;
}

int main(void) {
	//freopen("in", "r", stdin);
	for (int i = 0; i < 20; i++) pow[1 << i] = i; int kase = 0;
	while (scanf("%d", &n), n != -1) {
		memset(a, 0x3f, sizeof a); scanf("%d%d", &vt, &m);vt--; inf = a[0][0];
		memset(map, 0, sizeof map); memset(g, -1, sizeof g);
		for (int i = 1; i <= m; i++) {
			int x, y, z; scanf("%d%d%d", &x, &y, &z); x--, y--;
			a[x][y] = min(a[x][y], (long long)z);
			a[y][x] = a[x][y];
			map[x][y] = map[y][x] = 1;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) if (a[i][j] != inf) {
				a[i][j] = ((a[i][j] * 20 + 1) << 20) + (1ll << i);
			}
		scanf("%d", &k);
		memset(f, 0x3f, sizeof f);
		for (int i = 0; i < k; i++) scanf("%d", vs + i), vs[i]--, f[1 << i][vs[i]] = 0;
		for (int S = 1; S < (1 << k); S++) {
			// printf("S: %d\n", S);
			for (int i = 0; i < n; i++) {
				for (int x = (S - 1) & S; x; --x&=S) {
					if (f[S][i] > f[x][i] + f[S ^ x][i]) {
						f[S][i] = f[x][i] + f[S ^ x][i];
						g[S][i] =  make_pair(x, i);
					}
				}
				while (!Q.empty()) Q.pop();
				Q.push(make_pair(-f[S][i], i));
				for (int j = 0; j < n - 1; j++) {
					while (!Q.empty() && f[S][Q.top().second] != -Q.top().first) {
						Q.pop();
					}
					if (Q.empty()) break;
					pair<long long, int> now = Q.top(); Q.pop();
					for (int other = 0; other < n; other++) if (map[now.second][other] && f[S][other] > f[S][now.second] + a[now.second][other]) {
						Q.push(make_pair(-(f[S][other] = f[S][now.second] + a[now.second][other]), other));
						g[S][other] = make_pair(S, now.second);
					}
				}
			}
		}
		Dfs((1 << k) - 1, vt);
		printf("Case %d: distance = %d\n", ++kase, (int)((f[(1 << k) - 1][vt] >> 20) / 20));
		for (int i = 0; i < k; i++) {
			printf("   ");
			for (int j = len[i] - 1; j >= 0; j--)
				printf("%d%c", Ans[i][j] + 1, "-\n"[!j]);
		}
		puts("");
	}
	return 0;
}

