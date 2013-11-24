#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main ()
{
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);
	int n; scanf("%d", &n);
	int a = 0, b = 0;
	for (int i = 0; i < n; i++)
	{
		int x; scanf("%d", &x);
		a += x, b += 1 - x;
	}
	printf("%d\n", min(a, b));
	return 0;
}
