#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 210;
char str1[N], str2[N];

int main ()
{
	int kase; scanf("%d", &kase);
	for (int _ = 1; _ <= kase; _++)
	{
		scanf("%s %s", str1, str2);
		int tt = 0;
		int len = strlen(str1);
		for (int i = 0; i < len; i++)
		{
			if (str1[i] == '0' && str2[i] == '1') --tt;
			if (str1[i] == '1' && str2[i] == '0') ++tt;
		}
		bool ok = true;
		int c0 = 0;
		if (tt > 0)
		{
			for (int i = 0; tt > 0 && i < len; i++)
			{
				if (str1[i] == '?' && str2[i] == '1') str1[i] = '0', --tt, ++c0;
			}
			if (tt > 0) ok = false;
		}
		if (!ok)
		{
			printf("Case %d: -1\n", _);
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				if (str1[i] == '0' && str2[i] == '1') ++c0;
				if (str1[i] == '?') ++c0;
			}
			printf("Case %d: %d\n", _, c0);
		}
	}
	return 0;
}
