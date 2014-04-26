#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
	int x, y;
} a[200000];
int n, m;
std::vector<int> g[200000];
int u[200000], cnt;

int dfs(int n) {
	cnt++;
	int ret = 1;
	for (int i = 0; i < g[n].size(); i++)
		if (!u[g[n][i]]) {
			u[g[n][i]] = -u[n];
			int r = dfs(g[n][i]);
			ret = ret && r;
		} else if (u[g[n][i]] == u[n]) 
			ret = 0;
	return ret;
}

int main ()
{
	scanf("%d%d", &n, &m);
	memset(a, -1, sizeof a);
	for (int i = 0; i < 2*m; i++) {
		int r, c; scanf("%d%d", &r, &c), r--, c--;
		if (a[c].x == -1) a[c].x = r;
		else a[c].y = r;
	}
	for (int i = 0; i < m; i++)
		g[a[i].x].push_back(a[i].y), g[a[i].y].push_back(a[i].x);
	int ans = 0;
	for (int i = 0; i < n; i++)
		if (!u[i]) {
			u[i] = 1;
			cnt = 0;
			if (dfs(i)) ans += cnt-1;
			else ans += cnt;
		}
	printf("%d\n", ans);
	return 0;
}
