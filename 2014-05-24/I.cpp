#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 500010, M = 2000010;

int hd[N], to[M], nxt[M], mr, dep[N], gaotime[N], deg[N], pa[N];

void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
}
void dfs_dep (int x)
{
	for (int p = hd[x]; p != -1; p = nxt[p]) if (to[p] != pa[x])
	{
		pa[to[p]] = x;
		++deg[x], dep[to[p]] = dep[x] + 1;
		dfs_dep(to[p]);
	}
}
bool sch[N];
int dfs_subtree (int x)
{
	sch[x] = true;
	int res = 1;
	for (int p = hd[x]; p != -1; p = nxt[p]) if (to[p] != pa[x] && !sch[to[p]])
	{
		res += dfs_subtree(to[p]);
	}
	return res;
}

int arr[N];
bool comp (const int& a, const int& b)
{
	return gaotime[a] + dep[a] > gaotime[b] + dep[b];
}

int main ()
{
	memset(hd, -1, sizeof hd);
	mr = 0;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &gaotime[i]);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b; scanf("%d %d", &a, &b); --a, --b;
		link(a, b); link(b, a);
	}
	memset(deg, 0, sizeof deg);
	dep[0] = 0, pa[0] = -1;
	dfs_dep(0);

	int ans = -1, clock = 0;
	for (int i = 0; i < n; i++) arr[i] = i;
	sort(arr, arr + n, comp);
	memset(sch, 0, sizeof sch);
	for (int i = 0; i < n; i++)
	{
		if (!sch[arr[i]])
		{
			int tt = dfs_subtree(arr[i]);
			clock += tt;
			ans = max(ans, clock - 1 + gaotime[arr[i]] + dep[arr[i]]);
		}
	}	

	printf("%d\n", ans);
	return 0;
}
