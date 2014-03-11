#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

void bin (int t, int n)
{
	--t;
	while (t >= 0) printf("%d", !!(n & (1 << t))), --t;
}

int main ()
{
	int m; while (scanf("%d", &m) == 1)
	{
		int t = 0;
		while ((1 << t) < m) ++t;
		int pwr = 1 << t;
		int rem = pwr - m;
		for (int i = 0; i < rem; i++) bin(t - 1, i), printf("\n");
		for (int i = rem; i < (1 << (t - 1)); i++)
		{
			bin(t - 1, i), printf("0\n");
			bin(t - 1, i), printf("1\n");
		}
	}
	return 0;
}
