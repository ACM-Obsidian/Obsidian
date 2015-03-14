#include <cstdio>
#include <cstring>
struct node {
	int s[26], p;
} a[1000000];
char s[10001], ans[101];
int n, m, k, N;
bool dfs(int n, int dep) {
	if (dep == m)
		return false;
	for (int i = 0; i < k; i++)
		if (a[n].s[i] == -1) {
			ans[dep] = i+97;
			for (int j = dep+1; j < m; j++)
				ans[j] = 97;
			ans[m] = 0;
			return true;
		} else {
			ans[dep] = i+97;
			if (dfs(a[n].s[i], dep+1))
				return true;
		}
	return false;
}
int main() {
	freopen("hacking.in", "r", stdin);
	freopen("hacking.out", "w", stdout);
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d%d", &n, &m, &k);
		scanf("%s", s);
		memset(a[0].s, -1, sizeof(a[0].s));
		N = 1;
		for (int i = 0; i <= n-m; i++) {
			int p = 0;
			for (int j = 0; j < m; j++) {
				if (a[p].s[s[i+j]-97] == -1) {
					int q = N++;
					memset(a[q].s, -1, sizeof(a[q].s));
					a[q].p = p;
					a[p].s[s[i+j]-97] = q;
				}
				p = a[p].s[s[i+j]-97];
			}
		}
		dfs(0, 0);
		printf("%s\n", ans);
	}
	return 0;
}
