#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

int pwrmod (int a, long long b, int p)
{
	int res = 1, tt = a;
	while (b)
	{
		if (b & 1) res = (ll)res * tt % p;
		tt = (ll)tt * tt % p;
		b >>= 1;
	}
	return res;
}
int haha (long long n, int p)
{
	if (n == 0) return 0;
	else if (n & 1)
	{
		return ((ll)haha(n - 1, p) * 10 + 1) % p;
	}
	else
	{
		int tt = haha(n / 2, p);
		int pp = pwrmod(10, n / 2, p);
		return ((ll)tt * pp + tt) % p;
	}
}

int main ()
{
	freopen("zeroes.in", "r", stdin);
	freopen("zeroes.out", "w", stdout);
	long long n;
	int p; scanf("%lld %d", &n, &p);
	int ans = ((ll)pwrmod(10, n - 1, p) * ((n - 1) % p) + (n % p) - haha(n - 1, p)) % p;
	ans = (ans + p) % p;
	printf("%d\n", ans);
	return 0;
}
