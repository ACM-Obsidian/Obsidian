#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 101;

std::map<std::pair<int, long long>, bool> M;

int inf = ~0U>>1;
int n, m, Ans = inf, c[MAXN];
int stack[MAXN], top, in[MAXN], a[MAXN][MAXN];

long long G[MAXN];

inline int gao(long long S, long long new_S) {
	int ret = 0;
	for (int i = 1; i <= n; i++) if ((S & (1ll << (i - 1))) == 0 && (new_S & (1ll << (i - 1))) != 0) {
		ret += c[i];
	}
	return ret;
}

void Dfs(int u, int sum, long long S) {
	if (u == n) {
		Ans = std::min(Ans, sum);
		return;
	}
	std::pair<int, long long> tmp = std::make_pair(u, S);
	if (sum >= Ans) return;
	auto _ = M.find(tmp);
	if (_ != M.end()) return;

	in[ stack[++top] = u ] = true;
	for (int i = 1; i <= n; i++) if (a[u][i] && !in[i]) {
		long long next_S = S | G[i];
		int d = gao(S, next_S);
		Dfs(i, sum + d, next_S);
	}
	in[ stack[top--] ] = false;
	M[tmp] = true;
}

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = a[y][x] = 1;
	}
	for (int i = 1; i <= n; i++) {
		G[i] = 1ll << (i - 1);
		for (int j = 1; j <= n; j++) if (a[i][j]) G[i] |= 1ll << (j - 1);
	}
	Dfs(1, gao(0, G[1]), G[1]);
	printf("%d\n", Ans);
	return 0;
}

