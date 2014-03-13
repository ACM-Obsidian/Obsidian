#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;

int sg[N];
bool tt[110];

void proc (int n, int m)
{
	int l = n / (m + 1), r = n / m; // (l, r]
	int c = r - l;
	if (c == 0) return;
	int d1 = m, d2 = m + 1;
	int st = l + 1;
	int n1 = st - (n % st), n2 = n % st;
	int r1 = m + 1, r2 = m;
	tt[(n1 & 1 ? sg[d1] : 0) ^ (n2 & 1 ? sg[d2] : 0)] = true;
	if (r1 % 2 == 1 && c > 1)
		tt[(n1 & 1 ? 0 : sg[d1]) ^ (n2 & 1 ? sg[d2] : 0)] = true;
	if (r2 % 2 == 1 && c > 1)
		tt[(n1 & 1 ? sg[d1] : 0) ^ (n2 & 1 ? 0 : sg[d2])] = true;
	if (r1 % 2 == 1 && r2 % 2 == 1 && c > 1)
		tt[(n1 & 1 ? 0 : sg[d1]) ^ (n2 & 1 ? 0 : sg[d2])] = true;
}

int main ()
{
	freopen("nimg.in", "r", stdin);
	freopen("nimg.out", "w", stdout);
	int r, f; scanf("%d %d", &r, &f);
	for (int i = 0; i < f; i++) sg[i] = 0;
	int sq = 0;
	for (int i = f; i < N; i++)
	{
		while ((sq + 1) * (sq + 1) <= i) ++sq;
		memset(tt, 0, sizeof tt);
		for (int j = 1; j <= sq; j++) proc(i, j);
		int l = i / (sq + 1);
		for (int j = 2; j <= l; j++)
		{
			int d1, n1, d2, n2;
			d1 = i / j, n1 = j - i % j, d2 = d1 + 1, n2 = j - n1;
			tt[(n1 & 1 ? sg[d1] : 0) ^ (n2 & 1 ? sg[d2] : 0)] = true;
		}
		for (int j = 0; ; j++) if (!tt[j])
		{
			sg[i] = j;
			break;
		}
	}
	for (int i = 0; i < r; i++)
	{
		int cnt; scanf("%d", &cnt);
		int x = 0;
		for (int j = 0; j < cnt; j++)
		{
			int t; scanf("%d", &t);
			x ^= sg[t];
		}
		printf("%d%c", !!x, " \n"[i == r - 1]);
	}
	return 0;
}
