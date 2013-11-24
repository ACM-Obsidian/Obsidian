#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

const int N = 10010;
int arr[N];
int ans[N * 100], mr;

void calc (int le, int ri, bool pos)
{
	if (ri - le == 1)
	{
		if ((arr[le] < arr[ri]) == pos)
		{
			ans[mr++] = arr[le];
			ans[mr++] = arr[le];
			ans[mr++] = arr[ri];
			ans[mr++] = arr[ri];
		}
		else
		{
			ans[mr++] = arr[le];
			ans[mr++] = arr[ri];
			ans[mr++] = arr[ri];
			ans[mr++] = arr[le];
		}
	}
	else
	{
		int m = (le + ri) >> 1;
		calc(le, m, !pos);
		for (int i = le; i <= m; i++)
		{
			ans[mr++] = arr[i];
		}
		reverse(arr + le, arr + m + 1);
		calc(m + 1, ri, pos);
		int ll = le, rr = m + 1;
		while (ll <= m || rr <= ri)
		{
			if (rr > ri)
			{
				ans[mr++] = arr[ll];
				++ll;
			}
			else if (ll > m || ((arr[ll] > arr[rr]) == pos))
			{
				ans[mr++] = arr[rr];
				ans[mr++] = arr[rr];
				++rr;
			}
			else
			{
				ans[mr++] = arr[ll];
				++ll;
			}
		}
	}
	if (pos) sort(arr + le, arr + ri + 1);
	else sort(arr + le, arr + ri + 1, greater<int>());
}

int main ()
{
	freopen("railsort.in", "r", stdin);
	freopen("railsort.out", "w", stdout);
	int n; scanf("%d", &n);
	int m = (1 << n);
	for (int i = 0; i < m; i++) scanf("%d", &arr[i]);
	mr = 0;
	calc(0, m - 1, true);
	for (int i = 0; i < mr; i++)
	{
		printf("%d%c", ans[i], " \n"[i == mr - 1]);
	}
	return 0;
}
