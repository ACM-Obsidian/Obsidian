#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

char str[1010];

int main ()
{
	int kase, tk = 1; for (scanf("%d", &kase); kase; --kase, ++tk)
	{
		scanf("%s", str);
		int len = strlen(str);
		if (len >= 4 && strcmp(str + len - 4, "desu") == 0)
		{
			str[len - 4] = 0;
		}
		printf("Case #%d: %snanodesu\n", tk, str);
	}
}
