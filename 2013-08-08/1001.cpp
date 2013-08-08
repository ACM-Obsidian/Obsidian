#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
typedef long long LL;

inline int inv (int a)
{
	int res = 1, t = a, b = mod - 2;
	while (b)
	{
		if (b & 1) res = (LL)res * t % mod;
		t = (LL)t * t % mod;
		b >>= 1;
	}
	return res;
}

int arr[1000010];

int main ()
{
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		int n; scanf("%d", &n);
		int pi = 1;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
			pi = (LL)pi * arr[i] % mod;
		}
		sort(arr, arr + n);
		int u = n;
		for (int i = 0; i < n - 1; i++)
		{
			int p = (i >> 1);
			int m = arr[n - 1 - p];
			int v = inv(m);
			u = u + mod - v;
			if (u >= mod) u -= mod;
		}
		printf("%I64d\n", (LL)u * pi % mod);
	}
	return 0;
}
