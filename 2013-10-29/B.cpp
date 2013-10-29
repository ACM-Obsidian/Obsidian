#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main ()
{
	freopen("beer.in", "r", stdin);
	freopen("beer.out", "w", stdout);
	int n; while (scanf("%d", &n) == 1)
	{
		int a, b, c, area = -1;
		for (int i = 1; i <= n; i++)
		{
			if (i * i * i > n) break;
			for (int j = i; j <= n; j++)
			{
				if (i * j * j > n) break;
				int k = n / (i * j);
				if (i * j * k == n)
				{
					int pa = (i * j) + (i * k) + (j * k);
					if (area == -1 || pa < area)
					{
						area = pa;
						a = i, b = j, c = k;
					}
				}
			}
		}
		printf("%d %d %d\n", a, b, c);
	}
	return 0;
}
