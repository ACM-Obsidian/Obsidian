#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef pair<short, short> pii;
#define X first
#define Y second

const int N = 4010;
char map[N][N];
int dist[N][N];

const int quemax = 16000010;
pii que[quemax];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int h, w;

inline bool in (int x, int y)
{
	return x >= 0 && x < h && y >= 0 && y < w;
}

int main ()
{
	int T; for (scanf("%d", &T); T; --T)
	{
		scanf("%d %d", &h, &w);
		for (int i = 0; i < h; i++)
		{
			scanf("%s", map[i]);
		}
		if (map[0][0] == '.')
		{
			printf("0\n");
			continue;
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) dist[i][j] = -1;
		int l = 0, r = 0, ans = 1;
		que[r++] = pii(0, 0);
		dist[0][0] = 1;
		int qcnt = 1;
		while (qcnt > 0)
		{
			pii c = que[l++]; --qcnt;
			int tx = c.X, ty = c.Y;
			ans = max(ans, dist[tx][ty]);
			if (l == quemax) l = 0;
			for (int k = 0; k < 4; k++)
			{
				int rx = tx + dx[k], ry = ty + dy[k];
				if (!in(rx, ry) || map[rx][ry] == '.') continue;
				int ll = (map[rx][ry] == map[tx][ty] ? 0 : 1);
				if (ll == 0)
				{
					if (dist[rx][ry] == -1)
					{
						dist[rx][ry] = dist[tx][ty];
						--l;
						if (l == -1) l = quemax - 1;
						que[l] = pii(rx, ry);
						++qcnt;
					}
				}
			}
			for (int k = 0; k < 4; k++)
			{
				int rx = tx + dx[k], ry = ty + dy[k];
				if (!in(rx, ry) || map[rx][ry] == '.') continue;
				int ll = (map[rx][ry] == map[tx][ty] ? 0 : 1);
				if (ll == 1)
				{
					if (dist[rx][ry] == -1)
					{
						dist[rx][ry] = dist[tx][ty] + 1;
						que[r] = pii(rx, ry);
						++r;
						if (r == quemax) r = 0;
						++qcnt;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
