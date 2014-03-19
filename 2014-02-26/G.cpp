#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, k, arr[100010];

bool ok (int tt)
{
	long long more = 0;
	for (int i = 0; i < n; i++)
	{
		more += (max(arr[i] - tt, 0) + (k - 1)) / k;
	}
	return more <= tt;
}

int main ()
{
	freopen("drying.in", "r", stdin);
	scanf("%d", &n);
	int l = -1, r = 0;
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]), r = max(r, arr[i]);
	scanf("%d", &k); --k;
	if (k == 0) printf("%d\n", r);
	else
	{
		while (r - l > 1)
		{
			int mid = (r + l) / 2;
			if (ok(mid)) r = mid;
			else l = mid;
		}
		printf("%d\n", r);
	}
	return 0;
}
