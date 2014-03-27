#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 1010;

int a[MAXN][MAXN], n, vis[MAXN]; char ch[MAXN]; int cur;
int link[MAXN];

int Dfs(int u) {
	for (int i = 1; i <= n; i++) if (a[u][i] && vis[i] != cur) {
		vis[i] = cur;
		if (!link[i] || Dfs(link[i])) {
			link[i] = u;
			return 1;
		}
	}
	return 0;
}

int main(void) {
	int kase = 0;
	while (scanf("%s", ch + 1), strcmp(ch + 1, "end") != 0) {
		printf("Case %d: ", ++kase);
		memset(a, 0, sizeof a);
		memset(link, 0, sizeof link);
		n = strlen(ch + 1);
		for (int i = 1; i <= n; i++) {
			int same = 0;
			for (int j = i + 1; j <= n; j++) {
				if (ch[j] < ch[i]) {
					a[i][j] = 1;
				} else if (!same && ch[j] == ch[i]) {
					same = 1;
					a[i][j] = 1;
				}
			}
		}
		int Ans = n;
		for (int i = 1; i <= n; i++) ++cur, Ans -= Dfs(i);
		printf("%d\n", Ans);
	}
	return 0;
}

