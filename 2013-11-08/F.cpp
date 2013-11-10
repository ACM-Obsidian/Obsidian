#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 10010, M = 1000010;
char map[110][110];
int id[110][110];
int hd[N], nxt[M], to[M], mr;

int asrow[N], ascol[N];

void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
}

int toleft[N]; bool sch[N];
int match (int x)
{
	for (int p = hd[x]; p != -1; p = nxt[p])
	{
		if (!sch[to[p]])
		{
			sch[to[p]] = true;
			if (toleft[to[p]] == -1 || match(toleft[to[p]]))
			{
				toleft[to[p]] = x;
				return 1;
			}
		}
	}
	return 0;
}

int main ()
{
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		mr = 0;
		memset(hd, -1, sizeof hd);
		int n, m; scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) map[i][j] = '.';
		int p; scanf("%d", &p);
		for (int i = 0; i < p; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			map[x - 1][y - 1] = '*';
		}
		int w; scanf("%d", &w);
		for (int i = 0; i < w; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			map[x - 1][y - 1] = '#';
		}
		int lemr = 0, idm = 0;
		for (int i = 0; i < n; i++)
		{
			bool found = false;
			for (int j = 0; j <= m; j++)
			{
				if (j == m || map[i][j] == '#')
				{
					if (found)
					{
						found = false;
						++lemr;
					}
				}
				else if (map[i][j] == '*')
				{
					id[i][j] = idm++;
					found = true;
					asrow[id[i][j]] = lemr;
				}
			}
		}
		int rimr = 0;
		for (int j = 0; j < m; j++)
		{
			bool found = false;
			for (int i = 0; i <= n; i++)
			{
				if (i == n || map[i][j] == '#')
				{
					if (found)
					{
						found = false;
						++rimr;
					}
				}
				else if (map[i][j] == '*')
				{
					found = true;
					ascol[id[i][j]] = rimr;
				}
			}
		}
		for (int i = 0; i < idm; i++)
			link(asrow[i], ascol[i]);
		int ans = 0;
		memset(toleft, -1, sizeof toleft);
		for (int i = 0; i < lemr; i++)
		{
			memset(sch, 0, sizeof sch);
			ans += match(i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
