#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 12, T = 5;

int n, t;
int x[N], y[N], z[N];
int score[T][N];
int dp[T][1 << N];

inline int calc_score (int s, int ct)
{
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		if (s & (1 << i)) res += score[ct][i];
	}
	return res;
}
inline bool in_line (int s, int bs)
{
	if (s == 0) return false;
	vector<int> tt;
	for (int i = 0; i < n; i++)
	{
		if (s & (1 << i)) tt.push_back(i);
	}
	if (tt.size() <= 1) return true;
	int dx = x[tt[1]] - x[tt[0]], dy = y[tt[1]] - y[tt[0]], dz = z[tt[1]] - z[tt[0]];
	for (int i = 2; i < tt.size(); i++)
	{
		int tx = x[tt[i]] - x[tt[0]], ty = y[tt[i]] - y[tt[0]], tz = z[tt[i]] - z[tt[0]];
		if (tx * dy != ty * dx || tx * dz != tz * dx) return false;
	}
	for (int i = 0; i < n; i++)
	{
		if ((s & (1 << i)) == 0 && ((bs & (1 << i)) == 0))
		{
			int tx = x[i] - x[tt[0]], ty = y[i] - y[tt[0]], tz = z[i] - z[tt[0]];
			if (tx * dy == ty * dx && tx * dz == tz * dx) return false;
		}
	}
	return true;
}

int main ()
{
	int T; for (scanf("%d", &T); T; --T)
	{
		scanf("%d %d", &n, &t);
		for (int i = 0; i < n; i++) scanf("%d %d %d", &x[i], &y[i], &z[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < t; j++) 
			{
				scanf("%d", &score[j + 1][i]);
			}
		memset(dp, -1, sizeof dp);
		dp[0][0] = 0;
		int mask = (1 << n) - 1;
		int ans = -1;
		for (int i = 0; i < t; i++)
		{
			for (int s = 0; s <= mask; s++) if (dp[i][s] != -1)
			{
				int ms = s ^ mask;
				for (int ts = ms; ; --ts &= ms)
				{
					if (in_line(ts, s))
					{
						int tscore = calc_score(ts, i + 1);
						int &field = dp[i + 1][s | ts];
						if (field == -1 || field < dp[i][s] + tscore)
						{
							field = dp[i][s] + tscore;
						}
					}
					if (ts == 0) break;
				}
			}
			ans = max(ans, dp[i + 1][mask]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
