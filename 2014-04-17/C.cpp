#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int N = 2010;

int tx[N], ty[N];
int cx[N], cy[N];
map<int, int> xh, yh;

char dp[N][N];
// -1: undetermined; 0: ok; 1: stuck

struct rect
{
	int x1, y1, x2, y2;
	rect (void) {}
	rect (int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
	rect& disc (void)
	{
		// printf("DISC: %d %d %d %d\n", x1, y1, x2, y2);
		x1 = xh[x1], x2 = xh[x2];
		y1 = yh[y1], y2 = yh[y2];
		return (*this);
	}
	rect& brush (void)
	{
		// printf("BRUSH (%d, %d) -> (%d, %d)\n", x1, y1, x2, y2);
		for (int i = x1; i < x2; i++)
			for (int j = y1; j < y2; j++)
				dp[i][j] = 1;
		return (*this);
	}
};

rect trect[N];

int main ()
{
	int x, y, n, kase = 0; while (scanf("%d %d %d", &y, &x, &n), x)
	{
		xh.clear(), yh.clear();
		n += 2;
		int m = n * 2;
		for (int i = 0; i < n; i++)
		{
			int x1, y1, x2, y2;
			if (i == n - 2)
				x1 = x, y1 = 0, x2 = x, y2 = y - 2;
			else if (i == n - 1)
				x1 = 0, y1 = y, x2 = x - 2, y2 = y;
			else scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			++x2, ++y2;
			tx[i * 2] = x1, tx[i * 2 + 1] = x2, ty[i * 2] = y1, ty[i * 2 + 1] = y2;
			trect[i] = rect(x1, y1, x2, y2);
		}
		sort(tx, tx + m), sort(ty, ty + m);
		int xm = 0;
		for (int i = 0; i < m; i++) if (i == 0 || tx[i] != tx[i - 1])
		{
			// printf("X: %d -> %d\n", tx[i], xm);
			xh[tx[i]] = xm, cx[xm++] = tx[i];
		}
		int ym = 0;
		for (int i = 0; i < m; i++) if (i == 0 || ty[i] != ty[i - 1])
		{
			// printf("X: %d -> %d\n", ty[i], ym);
			yh[ty[i]] = ym, cy[ym++] = ty[i];
		}
		for (int i = 0; i < xm; i++)
			for (int j = 0; j < ym; j++) dp[i][j] = -1;
		for (int i = 0; i < n; i++)
			trect[i].disc().brush();
		dp[xm - 1][ym - 1] = 0;
		long long ans = 0;
		for (int i = xm - 1; i >= 0; i--)
			for (int j = ym - 1; j >= 0; j--)
			{
				if (dp[i][j] == -1)
				{
					dp[i][j] = 1;
					if (i + 1 < xm && dp[i + 1][j] == 0) dp[i][j] = 0;
					else if (j + 1 < ym && dp[i][j + 1] == 0) dp[i][j] = 0;
					if (dp[i][j] == 1)
						ans += (long long)(cy[j + 1] - cy[j]) * (cx[i + 1] - cx[i]);
				}
				// printf("DP %d %d = %d\n", i, j, dp[i][j]);
			}
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}
