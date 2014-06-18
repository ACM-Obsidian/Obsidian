#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N = 1000010;
int arr[N];

int main ()
{
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		int n; scanf("%d", &n);
		if (n > 100000)
		{
			memset(arr, 0, sizeof arr);
			for (int i = 0; i < n; i++)
			{
				int x; scanf("%d", &x);
				++arr[x];
			}
			int ans = 0, dirty = 0;
			for (int i = 0; i < N; i++)
			{
				arr[i + 1] += (arr[i] >> 1);
				arr[i] &= 1;
				if (arr[i]) ans = max(ans, i + dirty), dirty = 1;
			}
			printf("%d\n", ans);
		}
		else
		{
			priority_queue<int, vector<int>, greater<int> > pq;
			for (int i = 0; i < n; i++)
			{
				int x; scanf("%d", &x);
				pq.push(x);
			}
			int ans = 0, dirty = 0;
			while (!pq.empty())
			{
				int a = pq.top(); pq.pop();
				ans = max(ans, a + dirty);
				if (!pq.empty())
				{
					int b = pq.top();
					if (a == b)
					{
						pq.pop();
						pq.push(a + 1);
					}
					else dirty = 1;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
