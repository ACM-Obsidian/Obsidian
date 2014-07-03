#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 30;
vector<int> ts[N];

int ans[N][N];

int comp (const int& a, const int& b)
{
	return __builtin_popcount(a) < __builtin_popcount(b);
}

int main ()
{
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int x; scanf("%d", &x);
		for (int j = 0; j < x; j++)
		{
			char str[110]; scanf("%s", str);
			int tt = 0;
			int ll = strlen(str);
			for (int k = 0; k < ll; k++) tt |= (1 << (str[k] - 'a'));
			ts[i].push_back(tt);
		}
	}
	memset(ans, -1, sizeof ans);
	for (int s = 0; s < n; s++)
	{
		int now = (1 << s), tnow = now;
		ans[s][s] = 0;
		int now_step = 1;
		while (1)
		{
			for (int i = 0; i < n; i++) if ((now & (1 << i)) == 0)
			{
				for (int j = 0; j < ts[i].size(); j++)
				{
					if ((now & ts[i][j]) == ts[i][j])
					{
						ans[i][s] = now_step;
						tnow |= (1 << i);
						break;
					}
				}
			}
			if (tnow != now)
			{
				now = tnow;
				++now_step;
			}
			else break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", ans[i][j]);
		printf("\n");
	}
	return 0;
}
