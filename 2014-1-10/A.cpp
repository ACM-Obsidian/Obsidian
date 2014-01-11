#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 20;
int ans[N][N];
int color[N];

void getnext (int &x, int &y, int w)
{
	if (x & 1)
	{
		if (y == 0) ++x;
		else --y;
	}
	else
	{
		if (y == w - 1) ++x;
		else ++y;
	}
}

int main ()
{
	freopen("addictive.in", "r", stdin);
	freopen("addictive.out", "w", stdout);
	int h, w, c;
	while (scanf("%d %d %d", &h, &w, &c) == 3)
	{
		for (int i = 0; i < c; i++) scanf("%d", &color[i]);
		int x = 0, y = 0;
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < color[i]; j++)
			{
				ans[x][y] = i + 1;
				getnext(x, y, w);
			}
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++) printf("%d", ans[i][j]);
			printf("\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
