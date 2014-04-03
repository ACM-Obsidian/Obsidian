#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

char now[50];
int l, r, n, m, id;

void dfs (char *pcheck, char *pscan)
{
	if (pcheck != NULL && pcheck == now)
	{
		*pscan = 0;
		++id;
		if (id >= l) printf("%s\n", now);
		if (id >= r) return;
	}
	if (pscan - now < n) for (int i = (pcheck ? *pcheck - 'a' : 0); i < m; i++)
	{
		*pscan = 'a' + i;
		if (pcheck == NULL) dfs(now, pscan + 1);
		else if (*pcheck == *pscan) dfs(pcheck + 1, pscan + 1);
		else dfs(now, pscan + 1);
		if (id >= r) return;
	}
}

int main ()
{
	int kase = 0; while (scanf("%d %d %d %d", &n, &m, &l, &r) == 4)
	{
		printf("Case %d:\n", ++kase);
		id = 0;
		dfs(NULL, now);
	}
	return 0;
}
