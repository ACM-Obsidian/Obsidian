#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 100010, M = 500010;

int hd[N], nxt[M], to[M], mr;

void link (int a, int b)
{
	nxt[mr] = hd[a], to[mr] = b; hd[a] = mr++;
}

int pere[N], downdep[N], dep2[N];

void dfs1 (int x)
{
	downdep[x] = 0;
	for (int p = hd[x]; p != -1; p = nxt[p])
	{
		if (to[p] != pere[x])
		{
			pere[to[p]] = x;
			dfs1(to[p]);
			downdep[x] = max(downdep[x], downdep[to[p]] + 1);
		}
	}
}
void dfs2 (int x)
{
	int key = -1;
	for (int p = hd[x]; p != -1; p = nxt[p]) if (to[p] != pere[x])
	{
		if (key == -1 || downdep[to[p]] > downdep[key])
			key = to[p];
	}
	if (key != -1)
	{
		dep2[key] = dep2[x] + 1;
		dfs2(key);
		for (int p = hd[x]; p != -1; p = nxt[p]) if (to[p] != pere[x] && to[p] != key)
		{
			dep2[to[p]] = 1;
			dfs2(to[p]);
		}
		dep2[x] = 0;
	}
}

int main ()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int n, m; scanf("%d %d", &n, &m);
	memset(hd, -1, sizeof hd);
	mr = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		--x, --y;
		link(x, y), link(y, x);
	}
	pere[0] = -1; dfs1(0);
	dep2[0] = 0; dfs2(0);
	sort(dep2, dep2 + n, greater<int>());
	int ans = 0;
	for (int i = 0; i < m; i++) ans += dep2[i];
	printf("%d\n", ans);
	return 0;
}
