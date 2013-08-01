#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int mod = 10007;

char str[1010];
int dp[1010][1010], f[1010][1010];

int main ()
{
	int tt = 0;
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		++tt;
		scanf("%s", str);
		memset(dp, 0, sizeof dp);
		memset(f, 0, sizeof f);
		int len = strlen(str);
		for (int i = 0; i < len; i++) dp[i][i] = 1, f[i][i] = 1;
		for (int l = 1; l < len; l++)
		{
			for (int i = 0; i + l < len; i++)
			{
				int j = i + l;
				if (str[i] != str[j])
				{
					f[i][j] = 0;
				}
				else
				{
					f[i][j] = (l == 1 ? 1 : dp[i + 1][j - 1] + 1) % mod;
					// printf("F %d %d = %d\n", i, j, f[i][j]);
				}
				dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + mod - (l == 1 ? 0 : dp[i + 1][j - 1]) + f[i][j];
				dp[i][j] %= mod;
				// printf("DP %d %d = %d\n", i, j, dp[i][j]);
			}
		}
		printf("Case %d: %d\n", tt, dp[0][len - 1]);
	}
	return 0;
}
