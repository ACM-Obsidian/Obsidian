#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 16;
const int inf = 19931005;

typedef pair<int, int> pii;
#define X first
#define Y second

int dist (pii a, pii b)
{
	return abs(a.X - b.X) + abs(a.Y - b.Y);
}

pii wall[N], plc[N];
int dp[1 << N];

int calc (int n)
{
	dp[0] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		dp[i] = inf;
		int p = __builtin_popcount(i);
		for (int j = 0; j < n; j++) if (i & (1 << j))
		{
			dp[i] = min(dp[i], dp[i ^ (1 << j)] + dist(wall[p - 1], plc[j]));
		}
	}
	return dp[(1 << n) - 1];
}

int main ()
{
	int n, kase = 0; while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; i++)
			scanf("%d %d", &plc[i].X, &plc[i].Y), --plc[i].X, --plc[i].Y;
		// row
		int ans = inf;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) wall[j] = pii(i, j);
			ans = min(ans, calc(n));
		}
		// col
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) wall[j] = pii(j, i);
			ans = min(ans, calc(n));
		}
		// diag1
		for (int i = 0; i < n; i++) wall[i] = pii(i, i);
		ans = min(ans, calc(n));
		// diag2
		for (int i = 0; i < n; i++) wall[i] = pii(i, n - 1 - i);
		ans = min(ans, calc(n));
		printf("Board %d: %d moves required.\n\n", ++kase, ans);
	}
	return 0;
}
