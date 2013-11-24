#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 510, M = 50010;
const int inf = 1000010;
int hd[N], nxt[M], to[M], mr;
inline void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
}
int map[N][N], fst[N][N];
int que[N];
void bfs (int x)
{
	int l = 0, r = 0;
	que[r++] = x;
	while (r > l)
	{
		int c = que[l++];
		for (int p = hd[c]; p != -1; p = nxt[p])
		{
			if (map[x][to[p]] == -1)
			{
				map[x][to[p]] = map[x][c] + 1;
				if (c == x) fst[x][to[p]] = to[p];
				else fst[x][to[p]] = fst[x][c];
				que[r++] = to[p];
			}
			else if (map[x][to[p]] == map[x][c] + 1)
			{
				if (fst[x][c] != fst[x][to[p]])
					fst[x][to[p]] = -1;
			}
		}
	}
}

int main ()
{
	int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; ++_)
	{
		int n, m; scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				map[i][j] = -1;
			map[i][i] = 0;
			hd[i] = -1;
		}
		mr = 0;
		for (int i = 0; i < m; i++)
		{
			int a, b; scanf("%d %d", &a, &b);
			link(a, b), link(b, a);
		}
		int ans = inf;
		for (int i = 0; i < n; i++) bfs(i);
		for (int i = 0; i < n; i++)
		{
			for (int p = hd[i]; p != -1; p = nxt[p])
			{
				int j = to[p];
				if (i > j) continue;
				for (int k = 0; k < n; k++) if (k != i && k != j && fst[i][k] != j && fst[j][k] != i)
				{
					ans = min(ans, 1 + map[i][k] + map[k][j]);
				}
			}
		}
		printf("Case %d: ", _);
		if (ans == inf) printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
