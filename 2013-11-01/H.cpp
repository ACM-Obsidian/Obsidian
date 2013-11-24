#include <cstdio>
#include <vector>
using namespace std;

vector<int> group[110];

int main ()
{
	freopen("roads.in", "r", stdin);
	freopen("roads.out", "w", stdout);
	int n, r; scanf("%d %d", &n, &r);
	--r;
	for (int i = 0; i < n; i++) group[i % r].push_back(i + 1);
	int ans = n * (n - 1) / 2;
	for (int i = 0; i < r; i++)
	{
		int s = group[i].size();
		ans -= s * (s - 1) / 2;
	}
	printf("%d\n", ans);
	for (int i = 0; i < r; i++)
	{
		for (int j = i + 1; j < r; j++)
		{
			int si = group[i].size(), sj = group[j].size();
			for (int a = 0; a < si; a++)
			{
				for (int b = 0; b < sj; b++)
					printf("%d %d\n", group[i][a], group[j][b]);
			}
		}
	}
	return 0;
}

