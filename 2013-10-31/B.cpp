#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

bool dp[30][400][2];
int deci1[30][400][2], deci2[30][400][2], last1[30][400][2], last2[30][400][2];
char ori[30];

int main ()
{
	freopen("digitsum.in", "r", stdin);
	freopen("digitsum.out", "w", stdout);
	scanf("%s", ori);
	int len = strlen(ori);
	memset(dp, 0, sizeof dp);
	dp[0][0][0] = true;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 400; j++)
		{
			for (int k = 0; k < 2; k++) if (dp[i][j][k])
			{
				int cc = len - 1 - i;
				int c = ori[cc] - '0';
				for (int a = 0; a < 10; a++)
				{
					int b;
					// case 1
					b = c - a - k;
					if (b >= 0)
					{
						dp[i + 1][j + a + b][0] = true;
						deci1[i + 1][j + a + b][0] = a;
						deci2[i + 1][j + a + b][0] = b;
						last1[i + 1][j + a + b][0] = j;
						last2[i + 1][j + a + b][0] = k;
					}
					b = c + 10 - a - k;
					if (b <= 9)
					{
						dp[i + 1][j + a + b][1] = true;
						deci1[i + 1][j + a + b][1] = a;
						deci2[i + 1][j + a + b][1] = b;
						last1[i + 1][j + a + b][1] = j;
						last2[i + 1][j + a + b][1] = k;
					}
				}
			}
		}
	}
	int l1 = -1, l2 = -1, ans;
	for (int i = 399; l1 == -1 && i >= 0; i--)
	{
		if (dp[len][i][0])
		{
			ans = i;
			l1 = i, l2 = 0;
		}
	}
	long long ans1 = 0, ans2 = 0;
	for (int i = len; i > 0; i--)
	{
		ans1 = ans1 * 10 + deci1[i][l1][l2];
		ans2 = ans2 * 10 + deci2[i][l1][l2];
		int tl1 = last1[i][l1][l2], tl2 = last2[i][l1][l2];
		l1 = tl1, l2 = tl2;
	}
	printf("%d\n%lld %lld\n", ans, ans1, ans2);
	return 0;
}
