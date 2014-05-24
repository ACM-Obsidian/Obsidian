#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3010, M = 10010;
char str[N];
int sg[N];
bool mex[M];

int main ()
{
	// freopen("in", "r", stdin);
	scanf("%s", str);
	int len = strlen(str);
	// int len;
	// scanf("%d", &len);
	for (int i = len - 1; i >= 0; i--)
	{
		memset(mex, 0, sizeof mex);
		mex[0] = true;
		for (int d = 1; i + d < len; d++)
		{
			int s = 0, now = i;
			while (now + d < len)
			{
				now += d;
				s ^= sg[now];
				mex[s] = true;
			}
		}
		for (int j = 0; ; j++) if (!mex[j])
		{
			sg[i] = j;
			break;
		}
	}
	int ss = 0;
	for (int i = 0; i < len; i++) if (str[i] == 'N') ss ^= sg[i];
	if (ss == 0) printf("NIE\n");
	else
	{
		for (int i = 0; i < len; i++) if (str[i] == 'N')
		{
			if ((ss ^ sg[i]) < sg[i])
			{
				bool ok = false;
				str[i] = 'N' + 'S' - str[i];
				if ((ss ^ sg[i]) == 0)
				{
					ok = true;
				}
				for (int d = 1; !ok && i + d < len; d++)
				{
					int ts = 0, now = i;
					while (now + d < len)
					{
						now += d;
						ts ^= sg[now];
						if (ts == (ss ^ sg[i]))
						{
							for (int j = i + d; j <= now; j += d)
								str[j] = 'N' + 'S' - str[j];
							ok = true;
							break;
						}
					}
				}
				break;
			}
		}
		printf("%s\n", str);
	}
	return 0;
}
