#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 110;
char map[N][N];

int main ()
{
	int h, w; while (scanf("%d %d", &h, &w) == 2)
	{
		for (int i = 0; i < h; i++) scanf("%s", map[i]);
		int ans = 0;
		for (int i = 0; i < h; i++)
		{
			bool in = false;
			for (int j = 0; j < w; j++)
			{
				if (map[i][j] != '.') ans += 1, in = !in;
				else if (in) ans += 2;
			}
		}
		printf("%d\n", ans / 2);
	}
	return 0;
}
