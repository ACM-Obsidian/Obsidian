#include <cstdio>
#include <vector>
#include <algorithm>
std::vector<int> g[100000];
int u[100000];
void dfs(int x, int &ra, int &rb) {
	std::vector<int> va, vb;
	u[x] = 1;
	int flag = 0;
	for (int i = 0; i < g[x].size(); i++)
		if (!u[g[x][i]]) {
			flag = 1;
			int a, b;
			dfs(g[x][i], a, b);
			va.push_back(a);
			if (b != -1) vb.push_back(b);
		}
	if (!flag) {
		ra = x, rb = -1;
		return;
	}
	int t = va.size();
	if (!(va.size()&1) && !(vb.size()&1)) t -= 2;
	for (int i = 0; i+1 < t; i += 2)
		printf("%d %d\n", va[i]+1, va[i+1]+1);
	for (int i = 0; i+1 < vb.size(); i += 2)
		printf("%d %d\n", vb[i]+1, vb[i+1]+1);
	if (va.size()&1)
		if (vb.size()&1)
			ra = va[va.size()-1], rb = vb[vb.size()-1];
		else
			ra = va[va.size()-1], rb = -1;
	else if (vb.size()&1)
		ra = vb[vb.size()-1], rb = -1;
	else
		ra = va[va.size()-2], rb = va[va.size()-1];
}
int main() {
	freopen("kingdom.in", "r", stdin);
	freopen("kingdom.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if (n == 2) {
		printf("1\n1 2\n");
		return 0;
	}
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y); x--, y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
		if (g[i].size() == 1) ans++;
	printf("%d\n", ans+1>>1);
	int r = 0, flag = 0;
	while (g[r].size() == 1) r++;
	u[r] = 1;
	std::vector<int> va, vb;
	for (int i = 0; i < g[r].size(); i++) {
		int a, b;
		dfs(g[r][i], a, b);
		va.push_back(a);
		if (b != -1) vb.push_back(b);
		if (i == g[r].size()-1) flag = (b != -1);
	}
	if (flag) std::swap(va, vb);
	for (int i = 0; i+1 < va.size(); i += 2)
		printf("%d %d\n", va[i]+1, va[i+1]+1);
	for (int i = vb.size()&1; i < vb.size(); i += 2)
		printf("%d %d\n", vb[i]+1, vb[i+1]+1);
	if (va.size()&1)
		if (vb.size()&1)
			printf("%d %d\n", va[va.size()-1]+1, vb[0]+1);
		else
			printf("%d %d\n", va[va.size()-1]+1, r+1);
	else if (vb.size()&1)
		printf("%d %d\n", vb[0]+1, r+1);
	return 0;
}
