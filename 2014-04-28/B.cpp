#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long lld;

const lld inf = 20000LL << 45;

lld dp[N];
lld max0[N], max1[N];

char rec[N], *prec = rec - 1;

int main ()
{
	freopen("bank.in", "r", stdin);
	freopen("bank.out", "w", stdout);

	int K; scanf("%d", &K);
	scanf("%s", rec);
	dp[0] = 0;
	dp[1] = dp[2] = -inf;
	max0[0] = max1[0] = -inf;
	if (rec[0] == '0' && rec[1] == '1') max0[0] = 0;
	else if (rec[0] == '1') max1[0] = 0;
	max0[1] = max0[2] = max0[0];
	max1[1] = max1[2] = max1[0];
	int len = strlen(rec);
	for (int i = 3; i <= len; i++)
	{
		dp[i] = -inf;
		lld tt = 0;
		for (int t = 1; t <= K && i - t - 2 >= 0; ++t)
		{
			char p = prec[i - t + 1];
			tt |= (long long)(p - '0') << (t - 1);
			if (p != '0')
			{
				long long ltt = tt;
				if (prec[i - t] == '1') ltt = 0;

				// Case 1: Len = 2
				if (i - t - 2 >= 0)
				{
					char a = prec[i - t - 1], b = prec[i - t];
					if (a != b) // ok
					{
						if (a == '0') dp[i] = max(dp[i], dp[i - t - 2] - tt);
						else dp[i] = max(dp[i], dp[i - t - 2] + ltt);
					}
					// printf("dp -> %lld\n", dp[i]);
				}

				// Case 2: General case
				if (i - t - 3 >= 0)
				{
					dp[i] = max(dp[i], max0[i - t - 3] - tt);
					dp[i] = max(dp[i], max1[i - t - 3] + ltt);
					// printf("dp -> %lld\n", dp[i]);
				}
			}
			// printf("i = %d, t = %d, dp[i] = %lld\n", i, t, dp[i]);
		}	
		// Write max-es
		max0[i] = max0[i - 1], max1[i] = max1[i - 1];
		if (i + 2 <= len)
		{
			char a = prec[i + 1], b = prec[i + 2];
			if (a == '0' && b == '1') max0[i] = max(max0[i], dp[i]);
			else if (a == '1') max1[i] = max(max1[i], dp[i]);
		}
	}
	printf("%lld\n", dp[len]);
	return 0;
}
