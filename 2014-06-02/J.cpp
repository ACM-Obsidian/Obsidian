#include <cstdio>
struct node {
	int lc, rc, p;
} a[21523360];
int sc[21523360], ans[21523360][2], n;
int xortree(int lt, int rt) {
	int t = n++;
	sc[t] = sc[lt] ^ sc[rt];
	if (a[lt].lc != -1) {
		a[t].lc = xortree(a[lt].lc, a[rt].lc);
		a[t].rc = xortree(a[lt].rc, a[rt].rc);
	} else {
		a[t].lc = a[t].rc = -1;
	}
	return t;
}
void dfs(int n) {
	if (a[n].lc != -1) {
		dfs(a[n].lc);
		dfs(a[n].rc);
		int ret = xortree(a[n].lc, a[n].rc);
		dfs(ret);
		ans[n][0] = !ans[ret][!sc[n]] || !ans[a[n].lc][!sc[n]] || !ans[a[n].rc][!sc[n]];
		ans[n][1] = !ans[ret][sc[n]] || !ans[a[n].lc][sc[n]] || !ans[a[n].rc][sc[n]];
	} else {
		ans[n][0] = !sc[n];
		ans[n][1] = sc[n];
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) a[i].p = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &a[i].lc, &a[i].rc, &sc[i]);
		a[i].lc--, a[i].rc--;
		if (a[i].lc != -1) a[a[i].lc].p = i;
		if (a[i].rc != -1) a[a[i].rc].p = i;
	}
	int m = n;
	int root = 0; while (a[root].p != -1) root = a[root].p;
	dfs(root);
	for (int i = 0; i < m; i++) puts(ans[i][0] ? "Ksusha" : "Sasha");
	return 0;
}
