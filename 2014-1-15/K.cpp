#include <cstdio>
#include <vector>
#include <algorithm>
int g[26][26], u[26], u2[26], t[26], deg[26], f[26], f2[26], top;
char s[3];
std::vector<int> v, cycle, res;
int dfs(int n) {
	u[n] = u2[n] = 1;
	v.push_back(n);
	for (int i = 0; i < 26; i++)
		if (g[n][i])
			if (u2[i]) {
				int j = 0;
				for (; j < v.size(); j++)
					if (v[j] == i) break;
				for (; j < v.size(); j++)
					cycle.push_back(v[j]);
				return 1;
			} else if (!u[i] && dfs(i))
				return 1;
	u2[n] = 0;
	v.pop_back();
	return 0;
}
void solve() {
	cycle.clear();
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			g[i][j] = 1;
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		g[s[0]-97][s[1]-97] = 0;
	}
	for (int i = 0; i < 26; i++) u[i] = u2[i] = 0;
	v.clear();
	for (int i = 0; i < 26; i++)
		if (!u[i] && dfs(i)) {
			for (int j = 0; j < 20; printf("\n"), j++)
				for (int k = 0; k < 20; k++)
					putchar(cycle[(j+k)%cycle.size()]+97);
			return;
		}
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			if (g[i][j]) deg[j]++;
	for (int i = 0; i < 26; i++)
		if (!deg[i]) t[top++] = i;
	res.clear();
	while (top) {
		int i = t[top-1]; top--;
		res.push_back(i);
		for (int j = 0; j < 26; j++)
			if (g[i][j]) {
				deg[j]--;
				if (!deg[j]) t[top++] = j;
			}
	}
	for (int i = 0; i < 26; i++) f[i] = 1;
	int max = -1, maxi;
	for (int i = 0; i < 26; i++) {
		if (f[i] > max) max = f[i], maxi = i;
		for (int j = 0; j < 26; j++)
			if (g[res[i]][res[j]] && f[i]+1 > f[j]) {
				f[j] = f[i]+1;
				f2[j] = i;
			}
	}
	int len = max+1>>1;
	for (int i = 0, j = maxi; i < len*2-1; i++, j = f2[j])
		cycle.push_back(res[j]);
	std::reverse(cycle.begin(), cycle.end());
	for (int i = 0; i < len; printf("\n"), i++)
		for (int j = 0; j < len; j++)
			putchar(cycle[i+j]+97);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
