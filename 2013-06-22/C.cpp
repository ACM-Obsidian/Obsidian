#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int squ[30010];
int arr[1005000], mr;
int x[1010], y[1010];

int main ()
{
	for (int i = 0; i < 30010; i++) squ[i] = i * i;
	int T; scanf("%d", &T); 
	for (int TT = 1; TT <= T; ++TT)
	{
		int n; 
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		mr = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				arr[mr++] = squ[abs(x[i] - x[j])] + squ[abs(y[i] - y[j])];
		sort(arr, arr + mr);
		int ans = 1;
		for (int i = 0; i < mr; i++)
		{
			if (i == 0 || arr[i] != arr[i - 1]) ++ans;
		}
		printf("Case %d: %d\n", TT, ans);
	}
	return 0;
}