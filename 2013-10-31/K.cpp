#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210;

int to[2][N];
int rdeg[N], que[N], le, ri;
int ring[N][N], mr;
int deg[2], poly[2][N];
bool sch[N];

int main ()
{
	freopen("stable.in", "r", stdin);
	freopen("stable.out", "w", stdout);
	int r; scanf("%d", &r);
	mr = 0;
	for (int i = 0; i < 2; i++)
	{
		scanf("%d", &deg[i]);
		for (int j = deg[i]; j >= 0; j--) scanf("%d", &poly[i][j]), poly[i][j] %= r;
		for (int j = 0; j < r; j++)
		{
			int res = poly[i][0], tt = 1;
			for (int k = 1; k <= deg[i]; k++)
			{
				tt = (tt * j) % r;
				res += tt * poly[i][k];
				res %= r;
			}
			to[i][j] = res;
		}
		memset(rdeg, 0, sizeof rdeg);
		for (int j = 0; j < r; j++) ++rdeg[to[i][j]];
		le = ri = 0;
		for (int j = 0; j < r; j++) if (rdeg[j] == 0) que[ri++] = j;
		while (ri > le)
		{
			int c = que[le++];
			--rdeg[to[i][c]];
			if (rdeg[to[i][c]] == 0) que[ri++] = to[i][c];
		}
		memset(sch, 0, sizeof sch);
		for (int j = 0; j < r; j++) if (rdeg[j] && !sch[j])
		{
			for (int t = j; !sch[t]; t = to[i][t])
			{
				ring[mr][t] = 1;
				sch[t] = true;
			}
			++mr;
		}
	}
	int piv = 0;
	for (int i = 0; i < r; i++)
	{
		int tp = -1;
		for (int j = piv; tp == -1 && j < mr; j++)
		{
			if (ring[j][i]) tp = j;
		}
		if (tp != -1)
		{
			if (tp != piv)
			{
				for (int k = 0; k < r; k++) swap(ring[tp][k], ring[piv][k]);
			}
			for (int j = piv + 1; j < mr; j++)
				if (ring[j][i]) for (int k = 0; k < r; k++) ring[j][k] ^= ring[piv][k];
			++piv;
		}
	}
	int pwr = mr - piv;
	int ans[200], top = 0;
	memset(ans, 0, sizeof ans);
	ans[0] = 1;
	for (int i = 0; i < pwr; i++)
	{
		for (int j = 0; j <= top; j++) ans[j] *= 2;
		for (int j = 0; j <= top; j++)
		{
			if (ans[j] >= 10)
			{
				if (j == top) ++top;
				ans[j + 1] += ans[j] / 10;
				ans[j] %= 10;
			}
		}
	}
	for (int i = top; i >= 0; i--) printf("%d", ans[i]); printf("\n"); 
	return 0;
}
