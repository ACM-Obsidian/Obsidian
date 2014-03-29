#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010, M = 500010;
char color[N];

int ex[N], ey[N]; bool build[N];
int ufs[N], cnt[N];
int odd_cnt;

int uq (int x)
{
	return x == ufs[x] ? x : (ufs[x] = uq(ufs[x]));
}

int hd[N], nxt[M], to[M], mr;
int pere[N], tree_cnt[N];

void link (int x, int y)
{
	nxt[mr] = hd[x], to[mr] = y; hd[x] = mr++;
}
void dfs (int x)
{
	tree_cnt[x] = (color[x] == 'B');
	for (int p = hd[x]; p != -1; p = nxt[p])
	{
		if (to[p] != pere[x])
		{
			pere[to[p]] = x;
			dfs(to[p]);
			tree_cnt[x] += tree_cnt[to[p]];
		}
	}
}

int main ()
{
	freopen("uprtoff.in", "r", stdin);
	freopen("uprtoff.out", "w", stdout);
	int n, m; scanf("%d %d", &n, &m);
	scanf("%s", color);
	odd_cnt = 0;
	for (int i = 0; i < n; i++)
	{
		ufs[i] = i;
		if (color[i] == 'B') ++odd_cnt, cnt[i] = 1;
		else cnt[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &ex[i], &ey[i]);
		--ex[i], --ey[i];
		build[i] = false;
	}
	int upper = -1;
	if (odd_cnt == 0) upper = m;
	for (int i = m - 1; upper == -1 && i >= 0; i--)
	{
		int x = uq(ex[i]), y = uq(ey[i]);
		if (x != y)
		{
			build[i] = true;
			if ((cnt[x] & 1) && (cnt[y] & 1)) odd_cnt -= 2;
			ufs[y] = x;
			cnt[x] += cnt[y];
			if (odd_cnt == 0)
			{
				upper = i;
				break;
			}
		}
	}
	if (upper == -1) printf("0\n");
	else
	{
		memset(hd, -1, sizeof hd);
		mr = 0;
		for (int i = upper; i < m; i++) if (build[i])
		{
			link(ex[i], ey[i]);
			link(ey[i], ex[i]);
		}
		memset(pere, -1, sizeof pere);
		for (int i = 0; i < n; i++) if (pere[i] == -1) dfs(i);
		for (int i = upper; i < m; i++)
		{
			if (pere[ex[i]] == ey[i]) swap(ex[i], ey[i]);
			if (build[i] && (tree_cnt[ey[i]] & 1)) printf("%d ", i + 1);
		}
		printf("\n");
	}
	return 0;
}
