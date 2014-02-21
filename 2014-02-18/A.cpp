#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1010;

int arr[N];

int main ()
{
	int res, m, n; while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
		res = 0, m = 0;
		for (int i = 1; i + 1 < n; i++)
		{
			int tt = arr[i - 1] + arr[i] + arr[i + 1];
			if (tt > m) m = tt, res = i;
		}
		printf("%d %d\n", m, res + 1);
	}
	return 0;
}
