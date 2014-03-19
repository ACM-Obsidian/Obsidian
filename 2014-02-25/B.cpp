#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int x[500010], y[500010];

int main ()
{
 	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	int n; while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);
		long long area = 0;
		for (int i = 0; i < n - 1; i++) area += (long long)x[i + 1] * y[i] - (long long)y[i + 1] * x[i];
		area += (long long)x[0] * y[n - 1] - (long long)x[n - 1] * y[0];
		area = llabs(area);
		printf("%I64d.%d\n", area/2, (int)(5*(area&1)));
	}
	return 0;
}
