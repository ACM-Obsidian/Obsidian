#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 110;
char str[N][N];
char tar[N];
int pl[N];

int main ()
{
	freopen("bank.in", "r", stdin);
	freopen("bank.out", "w", stdout);
	int n; scanf("%d", &n);
	memset(str, 0, sizeof str);
	for (int i = 0; i < n; i++) scanf("%s", str[i]);
	scanf("%s", tar);
	int l = strlen(tar);
	bool ok = true;
	for (int i = 0; ok && i < l; i++)
	{
		pl[i] = -1;
		for (int j = 0; pl[i] == -1 && j < n; j++)
		{
			if (str[j][i] == tar[i]) pl[i] = j;
		}
		if (pl[i] == -1) ok = false;
	}
	if (!ok) printf("-1\n");
	else
	{
		int id, mm = 0;
		for (int i = 0; i < n; i++)
		{
			int tm = 0;
			for (int j = 0; j < l; j++) if (str[i][j] == tar[j]) ++tm;
			if (tm > mm)
			{
				mm = tm;
				id = i;
			}
		}
		printf("%d\n", l - mm);
		for (int i = 0; i < l; i++)
		{
			if (str[id][i] != tar[i])
			{
				printf("%d %d %d\n", id + 1, pl[i] + 1, i + 1);
			}
		}
	}
	return 0;
}
