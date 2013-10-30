#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
const int maxSum = 50000010;
const int maxN = 1000;
int H[N];
bool sch[maxSum];

int main ()
{
	freopen("hrundy.in", "r", stdin);
	freopen("hrundy.out", "w", stdout);
	int n; scanf("%d", &n);
	H[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = H[i - 1] + 1; ; j++)
		{
			bool ok = true;
			for (int k = 1; ok && k < i; k++)
			{
				if (sch[H[k] + j]) ok = false;
			}
			if (ok)
			{
				H[i] = j;
				for (int k = 1; k <= i; k++) sch[H[k] + H[i]] = true;
				break;
			}
		}
	}
	printf("%d\n", H[n]);
	return 0;
}
