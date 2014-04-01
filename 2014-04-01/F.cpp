#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
const int N = 160;
const int base = 100000000;
const char* output = "%08d";

struct bign
{
	int arr[N], m;
	bign (void) : m(1)
	{
		arr[0] = 0;
	}
	bign (int k) : m(0)
	{
		while (k) arr[m++] = k % base, k /= base;
	}
	void simplify (void)
	{
		for (int i = 0; ; i++)
		{
			if (arr[i] >= base)
			{
				if (i == m - 1) ++m;
				arr[i + 1] += arr[i] / base;
				arr[i] %= base;
			}
		}
	}
	bign& operator+= (const bign& rhs)
	{
		if (rhs.m > m)
		{
			for (int i = m; i < rhs.m; i++) arr[i] = 0;
			m = rhs.m;
		}
		for (int i = 0; i < rhs.m; i++)
			arr[i] += rhs.arr[i];
		simplify();
		return *this;
	}
};
bign 

ni ze kun shi li hai a!

*/

long long dp[1010][1010][2];

void proc (int n, int r)
{
	for (int i = 2; i <= n; i++)
	{
		for (int j = 0; j <= r; j++)
		{
			dp[i][j][0] = dp[i][j][1] = 0;
			if (j > 0) dp[i][j][0] = dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
			dp[i][j][1] = dp[i - 1][j][0];
		}
	}
}

int main ()
{
	int kase = 0;
	int n; while (scanf("%d", &n), n)
	{
		printf("Case %d: ", ++kase);
		if (n % 2 == 1 || n < 4)
		{
			printf("0\n");
			continue;
		}
		long long ans = 0;
		memset(dp[1], 0, sizeof dp[0]);
		dp[1][1][0] = 1;
		int r = n / 2 + 2;
		proc(n, r);
		ans += dp[n][r][0] + dp[n][r][1];
		memset(dp[1], 0, sizeof dp[0]);
		dp[1][0][1] = 1;
		proc(n, r);
		ans += dp[n][r][0];
		printf("%lld\n", ans);
	}
	return 0;
}
