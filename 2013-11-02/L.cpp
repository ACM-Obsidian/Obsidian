#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100010;

char src[N], dst[N];
char ts[N], td[N];
bool val[26][26];
bool sch[26];
int cnts[26], cntd[26];

int main ()
{
	freopen("traces.in", "r", stdin);
	freopen("traces.out", "w", stdout);
	memset(val, false, sizeof val);
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		char ss[5];
		scanf("%s", ss);
		val[ss[0] - 'a'][ss[1] - 'a'] = val[ss[1] - 'a'][ss[0] - 'a'] = true;
	}
	scanf("%s%s", src, dst);
	int l1 = strlen(src), l2 = strlen(dst);
	if (l1 != l2) printf("NO\n");
	else
	{
		bool ok = true;
		for (int i = 0; i < l1; i++)
		{
			sch[src[i] - 'a'] = sch[dst[i] - 'a'] = true;
			++cnts[src[i] - 'a'];
			++cntd[dst[i] - 'a'];
		}
		for (int i = 0; ok && i < 26; i++)
		{
			if (cnts[i] != cntd[i]) ok = false;
		}
		for (int i = 0; ok && i < 26; i++)
			for (int j = 0; ok && j < 26; j++)
				if (!val[i][j] && sch[i] && sch[j])
				{
					int tl1 = 0, tl2 = 0;
					for (int k = 0; k < l1; k++)
					{
						int t = src[k] - 'a';
						if (t == i || t == j) ts[tl1++] = src[k];
					}
					for (int k = 0; k < l2; k++)
					{
						int t = dst[k] - 'a';
						if (t == i || t == j) td[tl2++] = dst[k];
					}
					if (tl1 != tl2) ok = false;
					for (int k = 0; ok && k < tl1; k++)
					{
						if (ts[k] != td[k]) ok = false;
					}
				}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
