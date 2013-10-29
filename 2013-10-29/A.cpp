#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

string s[100010];
bool forb[100010][26];
int cnt[100010];
int ra[100010], rb[100010];
char tmp[100010];

int main ()
{
	freopen("aplusb.in", "r", stdin);
	freopen("aplusb.out", "w", stdout);
	int n, k; while (scanf("%d %d", &n, &k) == 2)
	{
		memset(forb, 0, sizeof forb);
		for (int i = 0; i < k; i++)
		{
			scanf("%s", tmp);
			s[i] = string(tmp);
			for (int j = 0; j < n; j++) forb[j][tmp[j] - 'a'] = true;
		}
		for (int i = 0; i < n; i++)
		{
			cnt[i] = 0;
			for (int j = 0; j < 26; j++) if (!forb[i][j]) ++cnt[i];
		}
		scanf("%s", tmp);
		for (int i = 0; i < n; i++)
		{
			ra[i] = 0;
			for (int j = 0; j < tmp[i] - 'a'; j++) if (!forb[i][j]) ++ra[i];
		}
		scanf("%s", tmp);
		for (int i = 0; i < n; i++)
		{
			rb[i] = 0;
			for (int j = 0; j < tmp[i] - 'a'; j++) if (!forb[i][j]) ++rb[i];
		}
		for (int i = n - 1; i >= 0; i--)
		{
			ra[i] += rb[i];
			if (ra[i] >= cnt[i])
			{
				ra[i] -= cnt[i];
				if (i) ra[i - 1] += 1;
			}
		}
		for (int i = 0; i < n; i++)
		{
			int c = 0;
			for (int j = 0; j < 26; j++)
			{
				if (!forb[i][j]) ++c;
				if (c > ra[i])
				{
					printf("%c", 'a' + j);
					break;
				}
			}
		}
		printf("\n");
	}
}
