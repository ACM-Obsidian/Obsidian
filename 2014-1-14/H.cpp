#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int B = 32, N = 100010;
int bset[B][N], bmax[B], bptr[B];

int xors[N], arr[N];
vector<int> xset[N];
map<int, int> xsetidx;

int query (int exp_xor, int st, int ed) // [st, ed)
{
	// printf("QUERY %d %d %d\n", exp_xor, st, ed);

	if (xsetidx.find(exp_xor) == xsetidx.end()) return 0;
	int l, r, key = xsetidx[exp_xor];
	l = -1, r = xset[key].size();
	while (r - l > 1)
	{
		int mid = (r + l) >> 1;
		if (xset[key][mid] >= st) r = mid;
		else l = mid;
	}
	int tl = r;
	l = -1, r = xset[key].size();
	while (r - l > 1)
	{
		int mid = (r + l) >> 1;
		if (xset[key][mid] >= ed) r = mid;
		else l = mid;
	}
	// printf("R = %d, TL = %d\n", r, tl);
	return r - tl;
}

int main ()
{
	freopen("hack.in", "r", stdin);
	freopen("hack.out", "w", stdout);

	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	xors[0] = 0;
	int xsetmax = 0;
	for (int i = 1; i <= n; i++)
	{
		xors[i] = xors[i - 1] ^ arr[i];	
		int key = xors[i];
		if (xsetidx.find(key) == xsetidx.end()) xsetidx[key] = xsetmax++;
		xset[xsetidx[key]].push_back(i);
	}
	for (int i = 0; i < B; i++)
	{
		for (int j = 1; j <= n; j++) if (~arr[j] & (1 << i))
			bset[i][bmax[i]++] = j;
		sort(bset[i], bset[i] + bmax[i]);
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		// start from i
		// printf("START FROM %d\n", i);

		for (int j = 0; j < B; j++) while (bptr[j] < bmax[j] && bset[j][bptr[j]] <= i) ++bptr[j];

		int ed[B], emax = 0;
		for (int j = 0; j < B; j++) if ((arr[i] & (1 << j)) && bptr[j] < bmax[j])
		{
			// printf("INTERVAL: BREAK %d, AT %d\n", j, bset[j][bptr[j]]);
			ed[emax] = bset[j][bptr[j]], emax++;
		}
		ed[emax] = n + 1, emax++;
		sort(ed, ed + emax);

		int st = i, exp = arr[i];
		for (int j = 0; j < emax; j++)
		{
			if (st < ed[j]) ans += query(exp ^ xors[i - 1], st, ed[j]);
			st = ed[j];
			exp &= arr[ed[j]];
		}
	}

	cout << ans << endl;
	return 0;
}
