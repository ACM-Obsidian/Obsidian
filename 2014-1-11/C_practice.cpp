#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 2010;
const int M = 40;
const int inf = 19931005;

char map[26][M][M], temp[1000], oldc[M], newc[M];
int bit[27][M], dp[M][N], old[N], key[M];
int dpsp[M][N], dpprev[M][N], res[M]; 
int spcnt[N], spcntps[N];

inline int chid (char a)
{
	if (a == ' ') return 26;
	else return a - 'A';
}

int main ()
{
	int m, n, k, smin, smax;
	scanf("%d %d %d %d %d", &m, &n, &k, &smin, &smax);
	int t;
	gets(temp); gets(temp);
	t = (strlen(temp) + 1) / (k + 3);
	char *p = temp;
	for (int i = 0; i < t; i++)
	{
		key[i] = *p - 'A';
		p += 2;
		for (int j = 0; j < k; j++) map[key[i]][0][j] = *(p++);
		++p;
	}
	for (int i = 1; i < m; i++)
		for (int j = 0; j < t; j++) scanf("%s", map[key[j]][i]);
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < k; j++)
		{
			bit[key[i]][j] = 0;
			for (int x = 0; x < m; x++) bit[key[i]][j] |= (map[key[i]][x][j] == '*') << x;
		}
	}
	for (int j = 0; j < k; j++) bit[26][j] = 0;
	gets(temp);
	gets(oldc);
	int oldclen = strlen(oldc);
	int ptr = 0;
	for (int i = 0; i < oldclen; i++)
	{
		int keyc = chid(oldc[i]);
		int sp; scanf("%d", &sp);
		for (int j = 0; j < sp; j++, ptr++) old[ptr] = 0;
		for (int j = 0; j < k; j++, ptr++) old[ptr] = bit[keyc][j];
	}
	
	// for (int i = 0; i < n; i++) printf("%d ", old[i]); printf("\n");
	
	for (; ptr < n; ptr++) old[ptr] = 0;
	gets(temp);
	gets(newc);
	int newclen = strlen(newc);
	
	memset(dp, -1, sizeof dp);
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[0][i] = dp[0][i - 1] + (spcnt[i - 1] = __builtin_popcount(old[i - 1]));
	spcntps[n] = 0;
	for (int i = n - 1; i >= 0; i--) spcntps[i] = spcntps[i + 1] + spcnt[i];
	int ans = inf, status;
	for (int j = 1; j <= newclen; j++)
	{
		int keyc = chid(newc[j - 1]);
		for (int ri = k; ri <= n; ri++) if (dp[j - 1][ri - k] >= 0)
		{
			// printf("=== PROC %d %d\n", j, ri);
			int cur = dp[j - 1][ri - k];
			for (int x = 0; x < k; x++)
				cur += __builtin_popcount(old[ri - k + x] ^ bit[keyc][x]);
			if (j == newclen)
			{
				cur += spcntps[ri];
				if (cur < ans)
				{
					ans = cur;
					// printf("ANS <- %d\n", cur);
					status = ri - k;
				}
			}
			else
			{
				for (int x = 0; x < smin; x++) cur += spcnt[ri + x];
				for (int x = smin; x <= smax && ri + x <= n; x++)
				{
					if (dp[j][ri + x] < 0 || cur <= dp[j][ri + x])
					{
						dp[j][ri + x] = cur;
						// printf("DP %d %d <- %d\n", j, ri + x, cur);
						dpsp[j][ri + x] = x;
						dpprev[j][ri + x] = ri - k;
					}
					cur += spcnt[ri + x];
				}
			}
		}
	}
	for (int j = newclen - 1; j > 0; j--)
		res[j] = dpsp[j][status], status = dpprev[j][status];
	res[0] = status;
	
	// printf("ANS = %d\n", ans);
	for (int j = 0; j < newclen; j++) printf("%d%c", res[j], " \n"[j == newclen - 1]);
	// system("pause");
	return 0;
}
