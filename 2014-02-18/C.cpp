#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

const int N = 260;

char map[N * 2][N * 2];

int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

int r, c;
inline bool in (int x, int y)
{
	return x >= 0 && x < r && y >= 0 && y < c;
}
inline bool bd (int x, int y)
{
	return in(x, y) && (x == 0 || x == r - 1 || y == 0 || y == c - 1);
}
inline bool able (int x, int y, int d)
{
	return map[2 * x + 1 + dx[d]][2 * y + 1 + dy[d]] == '.';
}
inline bool inable (int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		if (!in(x + dx[i], y + dy[i]) && able(x, y, i)) return true;
	}
	return false;
}
inline int ind (int x, int y, int d)
{
	if (x == 0 && (d == 2 || d == 3)) return 0;
	else if (x == r - 1 && (d == 2 || d == 3)) return 1;
	else if (y == 0 && (d == 0 || d == 1)) return 2;
	else if (y == c - 1 && (d == 0 || d == 1)) return 3;
	// assert(false);
	return -1;
}
inline int dir (int x1, int y1, int x2, int y2)
{
	for (int i = 0; i < 8; i++)
	{
		if (x1 + dx[i] == x2 && y1 + dy[i] == y2)
		{
			return i;
		}
	}
	return -1;
}

int dist[N * 2][N * 2][9];

struct trip
{
	int x, y, d;
	trip (void) {}
	trip (int x0, int y0, int d0) :
		x(x0), y(y0), d(d0) {}
};

trip que[3000010];

int main ()
{
	scanf("%d %d", &r, &c); gets(map[0]);
	for (int i = 0; i <= 2 * r; i++) gets(map[i]);
	int x1, y1, x2, y2;
	for (int x = 0; x < r; x++)
	{
		for (int y = 0; y < c; y++)
		{
			// printf("MAP %d %d: %c\n", x, y, map[x * 2 + 1][y * 2 + 1]);
			if (map[x * 2 + 1][y * 2 + 1] == '1') x1 = x, y1 = y;
			else if (map[x * 2 + 1][y * 2 + 1] == '2') x2 = x, y2 = y;
		}
	}
	// printf("x1 = %d, y1 = %d, x2 = %d, y2 = %d\n", x1, y1, x2, y2);
	int d0 = dir(x1, y1, x2, y2);
	int ql = 0, qr = 0; int ans = 100000000;
	memset(dist, -1, sizeof dist);
	que[qr++] = trip(x1, y1, d0);
	dist[x1][y1][d0] = 0;
	while (qr > ql)
	{
		int x1, y1, x2, y2, d;
		x1 = que[ql].x, y1 = que[ql].y, d = que[ql].d; ql++;
		// printf("QUE %d %d %d = %d\n", x1, y1, d, dist[x1][y1][d]);
		if (d != 8) x2 = x1 + dx[d], y2 = y1 + dy[d];

		// First person
		for (int i = 0; i < 4; i++) if (able(x1, y1, i))
		{
			int td;
			int xx1 = x1 + dx[i], yy1 = y1 + dy[i];
			if (d == 8)
			{
				if (!in(xx1, yy1))
				{
					// printf("-> %d %d\n", xx1, yy1);
					ans = min(ans, dist[x1][y1][d] + 1);
					continue;
				}
				// else if (!bd(xx1, yy1) || ind(x1, y1, i)) continue;
				else if (!bd(xx1, yy1)) continue;
				td = 8;
			}
			else
			{
				td = dir(xx1, yy1, x2, y2);
				if (td == -1) continue;
				if (!in(xx1, yy1))
				{
					if (dist[x2][y2][8] == -1)
					{
						dist[x2][y2][8] = dist[x1][y1][d] + 1;
						que[qr++] = trip(x2, y2, 8);
					}
					continue;
				}
			}
			if (dist[xx1][yy1][td] == -1)
			{
				dist[xx1][yy1][td] = dist[x1][y1][d] + 1;
				que[qr++] = trip(xx1, yy1, td);
			}
		}

		// Second person
		if (d == 8)
		{
			for (int i = 0; i < 4; i++)
			{
				int xx2 = x1 + dx[i], yy2 = y1 + dy[i]; // Yes, xx2 = x1 + ..., yy2 = y1 + ...
				if (!bd(xx2, yy2)) continue;
				// printf("X1 = %d, Y1 = %d, I = %d (XX2 = %d, YY2 = %d)\n", x1, y1, i, xx2, yy2);

				// int dd = ind(x1, y1, i);
				// if (dd == -1) continue;
				// if (bd(xx2, yy2) && able(xx2, yy2, dd))
				if (bd(xx2, yy2) && inable(xx2, yy2))
				{
					if (dist[x1][y1][i] == -1)
					{
						dist[x1][y1][i] = dist[x1][y1][d] + 1;
						que[qr++] = trip(x1, y1, i);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++) if (able(x2, y2, i))
			{
				int xx2 = x2 + dx[i], yy2 = y2 + dy[i], td;
				td = dir(x1, y1, xx2, yy2);
				if (td == -1) continue;
				if (!in(xx2, yy2)) td = 8;
				if (dist[x1][y1][td] == -1)
				{
					dist[x1][y1][td] = dist[x1][y1][d] + 1;
					que[qr++] = trip(x1, y1, td);
				}
			}
		}
	}
	if (ans == 100000000) printf("Death\n");
	else printf("%d\n", ans);
	return 0;
}
