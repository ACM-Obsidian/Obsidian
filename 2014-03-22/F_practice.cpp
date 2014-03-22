#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
int p[100000][18], d[100000], dis[100000], l[100000], r[100000], u[100000], ts = 0;
int S[100000], D[100000], T[100000], SS, DD, Tl, Tr, v;
std::vector<int> g[100000], gd[100000];
void dfs(int n) {
	l[n] = ts++;
	u[n] = 1;
	for (int i = 0; i < g[n].size(); i++)
		if (!u[g[n][i]]) {
			d[g[n][i]] = d[n]+1;
			dis[g[n][i]] = dis[n]+gd[n][i];
			p[g[n][i]][0] = n;
			for (int j = 0; p[g[n][i]][j] != -1; j++)
				p[g[n][i]][j+1] = p[p[g[n][i]][j]][j];
			dfs(g[n][i]);
		}
	r[n] = ts++;
	u[n] = 0;
}
void up(int &n, int d) {
	for (int i = 0; d; d >>= 1, i++)
		if (d & 1) n = p[n][i];
}
int lca(int x, int y) {
	if (d[x] > d[y]) up(x, d[x] - d[y]);
	else if (d[y] > d[x]) up(y, d[y] - d[x]);
	if (x == y) return x;
	for (int i = 16; i >= 0; i--)
		if (p[x][i] != p[y][i]) x = p[x][i], y = p[y][i];
	return p[x][0];
}
int isparent(int x, int y) {
	return l[x] < l[y] && r[x] > r[y];
}
int calcdis(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}
int main() {
	freopen("sapsan.in", "r", stdin);
	freopen("sapsan.out", "w", stdout);
	memset(p, -1, sizeof p);
	int n; scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		x--, y--;
		g[x].push_back(y), g[y].push_back(x);
		gd[x].push_back(z), gd[y].push_back(z);
	}
	dfs(0);
	int m; scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &S[i], &D[i], &T[i]), S[i]--, D[i]--;
	scanf("%d%d%d%d%d", &SS, &DD, &v, &Tl, &Tr), SS--, DD--;
	int FF = lca(SS, DD);
	std::vector<std::pair<double, std::pair<double, int> > > evt;
	int ans;
	for (int i = 0; i < m; i++) {
		int F = lca(S[i], D[i]), vs = -1, vt = -1, f1, f2;
		if (isparent(FF, F) && (f1 = lca(D[i], DD), isparent(F, f1)))
			vs = F, vt = f1;
		else if (isparent(FF, F) && (f1 = lca(S[i], SS), isparent(F, f1)))
			vs = f1, vt = F;
		else if (isparent(F, FF) && (f1 = lca(S[i], SS), isparent(FF, f1)))
			vs = f1, vt = FF;
		else if (isparent(F, FF) && (f1 = lca(D[i], DD), isparent(FF, f1)))
			vs = FF, vt = f1;
		else if (F == FF) {
			f1 = lca(SS, S[i]), f2 = lca(DD, D[i]);
			vs = f1, vt = f2;
		}
		if (vs == vt) continue;
		double t1 = T[i] + calcdis(S[i], vs) - 1.0 * calcdis(SS, vs) / v;
		double t2 = t1 + calcdis(vs, vt) * (1 - 1.0 / v);
		evt.push_back(std::make_pair(t1, std::make_pair(t1, 1)));
		evt.push_back(std::make_pair(t2, std::make_pair(t1, -1)));
	}
	std::sort(evt.begin(), evt.end());
	if (!evt.size()) ans = Tl;
	else if (Tl >= evt[evt.size()-1].first-1e-8 || Tl <= evt[0].first+1e-8) ans = Tl;
	else if (Tr >= (long long)(ceil(evt[evt.size()-1].first-1e-8))) ans = int(ceil(evt[evt.size()-1].first-1e-8));
	else {
		int tmpk = 0; double tmpb = 0; double min = 1e30;
		for (int i = 0; i < evt.size(); i++) {
			if (evt[i].second.second == 1) tmpk++, tmpb -= evt[i].first;
			else tmpk--, tmpb += evt[i].second.first;
			long long lp = ceil(evt[i].first-1e-8);
			if (i+1 < evt.size() && lp < evt[i+1].first+1e-8)
				if (Tl >= evt[i].first-1e-8 && Tl <= evt[i+1].first+1e-8) {
					if (1.0*Tl*tmpk+tmpb < min) ans = Tl, min = 1.0*Tl*tmpk+tmpb;
				} else if (Tl <= lp && Tr >= lp) {
					if (1.0*lp*tmpk+tmpb < min) ans = lp, min = 1.0*ans*tmpk+tmpb;
				}
		}
	}
	printf("%d\n", ans);
	return 0;
}
