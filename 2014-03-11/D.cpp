#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int wrap[11][52];
int deck[11][52];

void do_shuffle (int from[], int to[])
{
	for (int i = 0; i < 52; i++)
		to[i] = wrap[1][from[i]];
}

int same (int a[], int b[])
{
	int res = 0;
	for (int i = 0; i < 52; i++)
		if (a[i] == b[i]) ++res;
	return res;
}

int now[52], err[11], nowerr[11];

int best = 100, last;
void dfs (int level, int cha)
{
	if (level == last + 1)
	{
		if (same(now, wrap[last]) == 52 && cha < best)
		{
			best = cha;
			memcpy(err, nowerr, sizeof err);
		}
	}
	else
	{
		int diff = 52 - same(now, wrap[last]);
		int least = (diff + 1) / 2;
		if (level + least - 1 > last) return;
		if (cha + least >= best) return;

		dfs(level + 1, cha);

		for (int i = 0; i < 51; i++)
		{
			int x = deck[level][i], y = deck[level][i + 1];
			swap(now[x], now[y]);
			nowerr[level] = i;
			dfs(level + 1, cha + 1);
			swap(now[x], now[y]);
			nowerr[level] = -1;
		}
	}
}

int main ()
{
	for (int i = 0; i <= 25; i++) wrap[1][i] = 2 * i + 1;
	for (int i = 26; i <= 51; i++) wrap[1][i] = 2 * (i - 26);

	for (int i = 2; i <= 10; i++) do_shuffle(wrap[i - 1], wrap[i]);

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 52; j++)
			deck[i][wrap[i][j]] = j;
	}

	/* for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 52; j++) printf("%d ", deck[i][j]);
		printf("\n");
	} */

	int kase; scanf("%d", &kase); for (int kk = 1; kk <= kase; ++kk)
	{
		for (int i = 0; i < 52; i++)
		{
			int x; scanf("%d", &x);
			now[x] = i;
		}
		int res = -1, s = 0;
		for (int i = 1; i <= 10; i++)
		{
			int ss = same(now, wrap[i]);
			if (ss > s) s = ss, res = i;
		}
		printf("Case %d\nNumber of shuffles = %d\n", kk, res);

		memset(nowerr, -1, sizeof nowerr);
		last = res;
		best = 100;
		dfs(1, 0);

		bool have = false;
		for (int i = 1; i <= last; i++) if (err[i] != -1)
		{
			printf("Error in shuffle %d at location %d\n", i, err[i]);
			have = true;
		}
		if (!have) printf("No error in any shuffle\n");
		puts("");
	}
	return 0;
}
