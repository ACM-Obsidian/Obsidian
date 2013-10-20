#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main ()
{
	int x1, y1, x2, y2, x3, y3; while (scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) == 6)
	{
		printf("%s\n", x3 >= min(x1, x2) && x3 <= max(x1, x2) && y3 >= min(y1, y2) && y3 <= max(y1, y2) ? "Yes" : "No");
	}
	return 0;
}
