#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;

pair<long long, int> arr[N];

int main ()
{
	int n, k; scanf("%d %d", &n, &k);
	arr[0].first = 0, arr[0].second = 1;
	for (int i = 1; i < n; i++)
	{
		int x; scanf("%d", &x);
		arr[i].first = arr[i - 1].first + x;
		arr[i].second = i + 1;
	}
	sort(arr, arr + n);
	long long ans = -1; int s;
	for (int i = 0; i + k - 1 < n; i++)
	{
		long long td = arr[i + k - 1].first - arr[i].first;
		if (ans == -1 || td < ans) ans = td, s = i;
	}
	printf("%lld\n", ans);
	for (int i = 0; i < k; i++) printf("%d%c", arr[s + i].second, " \n"[i == k - 1]);
	return 0;
}
