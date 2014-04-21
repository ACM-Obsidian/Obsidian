#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

long long flsum_t (long long a, long long b, long long c, long long n)
{
	if (n < 0) return 0;
	if (c < 0) a = -a, b = -b, c = -c;
	n++; long long res = 0;
	if (a < 0 || a >= c)
	{
		long long ra = (a % c + c) % c;
		long long k = (a - ra) / c;
		res += k * n * (n - 1) / 2;
		a = ra;
	}
	if (b < 0 || b >= c)
	{
		long long rb = (b % c + c) % c;
		long long k = (b - rb) / c;
		res += k * n;
		b = rb;
	}
	if (a * n + b < c) return res;
	else return res + flsum_t(c, (a * n + b) % c, a, (a * n + b) / c - 1);
}

// $ \sum_{x=st}^ed\lfloor\frac{ax+b}c\rfloor $
long long flsum (long long a, long long b, long long c, long long st, long long ed)
{
	return flsum_t(a, b, c, ed) - flsum_t(a, b, c, st - 1);
}

// TEMPLATE ABOVE

long long calc (long long n)
{
	return flsum(-3, n + 2, 2, 1, n / 3);
}
long long calcIn (long long M) // <= M
{
	long long l = 1, r = 2000000000LL;
	while (r - l > 1)
	{
		long long m = (l + r) / 2;
		if (calc(m) > M) r = m;
		else l = m;
	}
	return l;
}

int main ()
{
	long long L, R; scanf("%lld %lld", &L, &R);
	printf("%lld\n", calcIn(R) - calcIn(L - 1));
	return 0;
}
