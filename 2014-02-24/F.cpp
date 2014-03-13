#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1000010;
const int mod = 100000007;

int deg[N], dlt[N];
int kmp[N], n;

inline int dlt2 (int x)
{
	if (x < n) return dlt[x];
	else return dlt[x - n];
}

inline int pwr (int a, int b)
{
	int res = 1, m = a;
	while (b)
	{
		if (b & 1) res = (long long)res * m % mod;
		m = (long long)m * m % mod;
		b >>= 1;
	}
	return res;
}

int gcd (int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int main ()
{
	int cc; while (scanf("%d %d", &cc, &n), n != -1)
	{
		for (int i = 0; i < n; i++) scanf("%d", &deg[i]);
		sort(deg, deg + n);
		for (int i = 0; i < n - 1; i++) dlt[i] = deg[i + 1] - deg[i];//, printf("DLT %d = %d\n", i, dlt[i]);
		dlt[n - 1] = deg[0] + 360000 - deg[n - 1];
		// printf("DLT %d = %d\n", n - 1, dlt[n - 1]);
		kmp[0] = -1;
		for (int i = 1; i <= n; i++)
		{
			int j = kmp[i - 1];
			while (j != -1 && dlt[i - 1] != dlt[j]) j = kmp[j];
			kmp[i] = j + 1;
			// printf("KMP %d = %d\n", i, kmp[i]);
		}
		int ans = 0, cnt = 0, p = 0;
		for (int i = 0; i < n + n - 1; i++)
		{
			while (p != -1 && dlt2(i) != dlt[p]) p = kmp[p];
			++p;
			// printf("I = %d, P = %d\n", i, p);
			if (p == n)
			{
				int s = i - n + 1;
				int rr = gcd(s, n);
				// printf("RR = %d\n", rr);
				ans += pwr(cc, rr); ans %= mod;
				// printf("ADD %d\n", pwr(cc, rr));
				++cnt;
				p = kmp[p];
			}
		}
		// printf("CNT = %d\n", cnt);
		ans = (long long)ans * pwr(cnt, mod - 2) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
