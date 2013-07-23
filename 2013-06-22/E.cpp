#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 10010, M = 30010, Mi = 19931117;
int hd[N], to[M], nxt[M], mr;
int dis[N];
int cnt[N], lng[N], lmr;
int ans[N];

inline void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
}

int mxl, tar, tot;
void dfs (int x, int bor)
{
	for (int p = hd[x]; p != -1; p = nxt[p]) if (dis[to[p]] < bor)
	{
		dis[to[p]] = dis[x] + 1;
		++tot;
		if (dis[to[p]] > mxl) mxl = dis[to[p]], tar = to[p];
		dfs(to[p], bor);
	}
}

int main ()
{
	int T; scanf("%d", &T);
	for (int TT = 1; TT <= T; TT++)
	{
		int n, m; scanf("%d %d", &n, &m);
		memset(hd, -1, sizeof hd);
		mr = lmr = 0;
		for (int i = 0; i < m; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			link(x - 1, y - 1), link(y - 1, x - 1);
		}
		memset(dis, -1, sizeof dis);
		memset(ans, -1, sizeof ans);
		for (int i = 0; i < n; i++) if (dis[i] == -1)
		{
			dis[i] = 0;
			mxl = 0, tar = i, tot = 1;
			dfs(i, 0);
			cnt[lmr] = tot;
			dis[tar] = Mi;
			mxl = Mi, tar = tar, tot = 1;
			dfs(tar, Mi);
			lng[lmr] = mxl - Mi + 1;
			for (int j = 1; j <= cnt[lmr]; j++)
			{
				int res;
				if (j <= lng[lmr]) res = j - 1;
				else res = (lng[lmr] - 1) + 2 * (j - lng[lmr]);
				if (ans[j] == -1 || res < ans[j]) ans[j] = res;
			}
		}
		printf("Case %d:\n", TT);
		int q; scanf("%d", &q);
		for (int i = 0; i < q; i++)
		{
			int k; scanf("%d", &k);
			if (ans[k] == -1) printf("impossible\n");
			else printf("%d\n", ans[k]);
		}
	}
	return 0;
}