#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1010][10010];
bool deci[1010][10010];
int len[1010], id[1010];

struct edge
{
	int x, y, l, id;
	edge (void) {}
	edge (int _x, int _y, int _l, int _id) :
		x(_x), y(_y), l(_l), id(_id) {}
	bool operator < (const edge& a) const
	{
		return l < a.l;
	}
} side[10010];

int ufs[1010];
int que (int a)
{
	return ufs[a] == a ? a : (ufs[a] = que(ufs[a]));
}

int main ()
{
	freopen("domestic.in", "r", stdin);
	freopen("domestic.out", "w", stdout);
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int x, y, l;
		scanf("%d %d %d", &x, &y, &l);
		side[i] = edge(x - 1, y - 1, l, i + 1);
	}
	sort(side, side + m);
	for (int i = 0; i < n; i++) ufs[i] = i;
	int mr = 1, sum = 0;
	for (int i = 0; i < m; i++)
	{
		if (que(side[i].x) != que(side[i].y))
		{
			len[mr] = side[i].l, id[mr] = side[i].id;
			sum += len[mr];
			++mr;
			ufs[que(side[i].x)] = que(side[i].y);
		}
	}
	int p1, q1, p2, q2, r1 = 5, r2 = 6; scanf("%d %d %d %d", &p1, &q1, &p2, &q2);
	if (p1 > p2) swap(p1, p2), swap(q1, q2), swap(r1, r2);
	for (int i = 0; i <= q1; i++) dp[0][i] = 0;
	for (int i = 1; i < mr; i++)
	{
		for (int j = 0; j <= q1; j++)
		{
			if (j >= len[i] && dp[i - 1][j] < dp[i - 1][j - len[i]] + len[i])
			{
				dp[i][j] = dp[i - 1][j - len[i]] + len[i];
				deci[i][j] = true;
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
				deci[i][j] = false;
			}
		}
	}
	if (mr != n || sum - dp[mr - 1][q1] > q2)
	{
		printf("Impossible\n");
	}
	else
	{
		printf("%d\n", dp[mr - 1][q1] * p1 + (sum - dp[mr - 1][q1]) * p2);
		int b = q1;
		for (int i = mr - 1; i >= 1; i--)
		{
			if (deci[i][b]) printf("%d %d\n", id[i], r1), b -= len[i];
			else printf("%d %d\n", id[i], r2);
		}
	}
	return 0;
}
