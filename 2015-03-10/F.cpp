#include <cstdio>
#include <vector>
std::vector<int> g[200000];
int in[200001], out[200001], f[200000], fid[200000], u[200000], next[200001], inid[200000], outid[200000];
// 0 null, 1 in, 2 out
bool dfs(int n) {
	u[n] = 1;
	std::vector<int> sons;
	for (int i = 0; i < g[n].size(); i++)
		if (!u[g[n][i]]) {
			sons.push_back(g[n][i]);
			if (!dfs(g[n][i]))
				return false;
		}
	if (inid[n] != -1 && outid[n] != -1) {
		for (int i = 0; i < sons.size(); i++)
			if (f[sons[i]] != 0)
				return false;
		f[n] = 0;
		next[inid[n]] = outid[n];
	} else if (inid[n] != -1 || outid[n] != -1) {
		int cnt = 0, val = 0, valid = 0;
		for (int i = 0; i < sons.size(); i++)
			if (f[sons[i]] != 0)
				cnt++, val = f[sons[i]], valid = fid[sons[i]];
		if (cnt > 1 || cnt == 1 && (inid[n] != -1 && val == 1 || outid[n] != -1 && val == 2))
			return false;
		if (cnt == 1) {
			f[n] = 0;
			if (inid[n] != -1)
				next[inid[n]] = valid;
			else
				next[valid] = outid[n];
		} else
			f[n] = (inid[n] != -1 ? 1 : 2), fid[n] = (inid[n] != -1 ? inid[n] : outid[n]);
	} else {
		int cnt = 0, val1 = 0, val2 = 0, valid1 = 0, valid2 = 0;
		for (int i = 0; i < sons.size(); i++)
			if (f[sons[i]] != 0) {
				if (cnt == 0) val1 = f[sons[i]], valid1 = fid[sons[i]];
				else val2 = f[sons[i]], valid2 = fid[sons[i]];
				cnt++;
			}
		if (cnt > 2 || cnt == 2 && val1 + val2 != 3)
			return false;
		if (cnt == 1)
			f[n] = val1, fid[n] = valid1;
		else if (cnt == 2) {
			if (val1 == 1)
				next[valid1] = valid2;
			else
				next[valid2] = valid1;
			f[n] = 0;
		} else
			f[n] = 0;
	}
	return true;
}
int main() {
	freopen("last.in", "r", stdin);
	freopen("last.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		int n, m, t, x, y;
		scanf("%d%d%d%d%d", &n, &m, &t, &x, &y);
		for (int i = 0; i < n; i++)
			g[i].clear(), u[i] = 0;
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		bool flag = true;
		for (int i = 0; i < n; i++)
			inid[i] = outid[i] = -1;
		for (int i = 0; i <= t; i++) {
			if (i < t)
				scanf("%d%d", &in[i], &out[i]);
			else
				in[i] = y, out[i] = x;
			if (outid[in[i]] != -1 || inid[out[i]] != -1)
				flag = false;
			outid[in[i]] = inid[out[i]] = i;
		}
		t++;
		for (int i = 0; flag && i < n; i++)
			if (!u[i] && (!dfs(i) || f[i] != 0))
				flag = false;
		if (!flag) puts("IMPOSSIBLE");
		else {
			int i = t-1, cnt = 1;
			for (i = next[i]; i != t-1; cnt++, i = next[i]);
			puts(cnt < t ? "IMPOSSIBLE" : "POSSIBLE");
		}
	}
	return 0;
}
