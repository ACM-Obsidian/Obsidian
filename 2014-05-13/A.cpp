#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 500010, M = 1000010;

inline int P (int id, int dir, int in)
{
	return 104 + ((id << 3) | (dir << 1) | in);
}
inline int Sta (int id, int dir)
{
	return (id << 1) | dir;
}

int hd[N], to[M], nxt[M], deg[N], mr;
void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
	++deg[b];
}

int que[N];

int main ()
{
	int n; while (scanf("%d", &n) == 1)
	{
		memset(deg, 0, sizeof deg);
		memset(hd, -1, sizeof hd);
		mr = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++) if (j != k)
					link(P(i, j, 1), P(i, k, 0));
			char str[20];
			scanf("%s", str);
			for (int j = 0; j < 4; j++)
			{
				char t1 = str[j * 2], t2 = str[j * 2 + 1];
				if (t1 != '0')
				{
					int id = ((t1 - 'A') << 1) | ((t2 == '+') ? 0 : 1);
					int idr = ((t1 - 'A') << 1) | ((t2 == '+') ? 1 : 0);
					link(P(i, j, 0), Sta(id, 0));
					link(Sta(idr, 1), P(i, j, 1));
				}
			}
		}
		for (int i = 0; i < 52; i++) link(Sta(i, 0), Sta(i, 1));
		int tot = 104 + n * 8;
		int l = 0, r = 0;
		for (int i = 0; i < tot; i++) if (deg[i] == 0) que[r++] = i;
		while (r > l)
		{
			int c = que[l++]; --tot;
			for (int p = hd[c]; p != -1; p = nxt[p])
			{
				--deg[to[p]];
				if (deg[to[p]] == 0) que[r++] = to[p];
			}
		}
		if (tot) printf("unbounded\n");
		else printf("bounded\n");
	}
	return 0;
}
