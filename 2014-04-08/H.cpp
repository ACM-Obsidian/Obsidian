#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 210, M = 10010;

inline int P (int x, int y)
{
	return (x << 1) | y;
}

int hd[N], nxt[M], to[M], mr;
void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
}
void linkOr (int id1, int op1, int id2, int op2)
{
	link(P(id1, op1 ^ 1), P(id2, op2));
	link(P(id2, op2 ^ 1), P(id1, op1));
}

bool sch[N];
void dfs (int x)
{
	for (int p = hd[x]; p != -1; p = nxt[p])
	{
		if (!sch[to[p]]) sch[to[p]] = true, dfs(to[p]);
	}
}
void floodfill (int x)
{
	memset(sch, 0, sizeof sch);
	sch[x] = true;
	dfs(x);
}

int main ()
{
	int b, m, kase = 0; while (scanf("%d %d", &b, &m), b)
	{
		memset(hd, -1, sizeof hd), mr = 0;
		for (int i = 0; i < m; i++)
		{
			int n; scanf("%d", &n);
			int id[4], op[4]; char str[5];
			for (int j = 0; j < n; j++)
			{
				scanf("%d %s", &id[j], str);
				--id[j];
				if (str[0] == 'y') op[j] = 0;
				else op[j] = 1;
			}
			if (n == 1 || n == 2)
			{
				for (int j = 0; j < n; j++) link(P(id[j], op[j] ^ 1), P(id[j], op[j]));
			}
			else
			{
				for (int j = 0; j < n; j++)
					for (int k = j + 1; k < n; k++)
						linkOr(id[j], op[j], id[k], op[k]);
			}
		}
		char ans[N]; bool ok = true;
		for (int i = 0; ok && i < b; i++)
		{
			bool sn = false, sy = false;
			floodfill(P(i, 0));
			if (sch[P(i, 1)]) sn = true;
			floodfill(P(i, 1));
			if (sch[P(i, 0)]) sy = true;
			if (sn && sy) ok = false;
			else if (sn) ans[i] = 'n';
			else if (sy) ans[i] = 'y';
			else ans[i] = '?';
		}
		ans[b] = 0;
		printf("Case %d: ", ++kase);
		if (ok) printf("%s\n", ans);
		else printf("impossible\n");
	}
	return 0;
}
