#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
struct itv {
	int l, r, x;
};
bool operator < (itv a, itv b) {
	return a.x < b.x || a.x == b.x && a.l < b.l;
}
std::vector<itv> h, h2, v, v2;
std::vector<int> a[500000], d[500000], u[500000], opi[500000], b[500000];
std::vector<int> f[500000];
std::map<std::pair<int, int>, int> T;
int n, m, k, N, x[500000], y[500000], g[500000], q[500000];
int judge(int x1, int y1, int fid) {
	int cnt = 0;
	double th = 1.0*rand()/RAND_MAX*1.5+0.02;
	double dx = cos(th), dy = sin(th);
	for (int i = 0; i < f[fid].size(); i++) {
		int p = f[fid][i], q = f[fid][(i+1)%f[fid].size()];
		if (x[p] == x[q] && x[p] > x1) {
			double yy = (x[p] - x1) / dx * dy + y1;
			if ((yy - y[p]) * (yy - y[q]) < 0) cnt++;
		} else if (y[p] == y[q] && y[p] > y1) {
			double xx = (y[p] - y1) / dy * dx + x1;
			if ((xx - x[p]) * (xx - x[q]) < 0) cnt++;
		}
	}
	return cnt & 1;
}
void solve() {
	h.clear(), v.clear();
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 == x2 && y1 == y2) continue;
		itv tmp;
		if (x1 == x2) {
			tmp.l = y1, tmp.r = y2, tmp.x = x1;
			if (y1 > y2) std::swap(tmp.l, tmp.r);
			v.push_back(tmp);
		} else {
			tmp.l = x1, tmp.r = x2, tmp.x = y1;
			if (x1 > x2) std::swap(tmp.l, tmp.r);
			h.push_back(tmp);
		}
	}
	int xh, yh, xu, yu;
	scanf("%d%d%d%d", &xh, &yh, &xu, &yu);
	h2.clear();
	std::sort(h.begin(), h.end());
	for (int i = 0, j = 0; i < h.size(); i = j) {
		while (j < h.size() && h[i].x == h[j].x) j++;
		int l1 = h[i].l, r1 = h[i].r;
		for (int k = i+1; k < j; k++)
			if (h[k].l > r1) {
				itv tmp; tmp.l = l1, tmp.r = r1, tmp.x = h[i].x;
				h2.push_back(tmp);
				l1 = v[k].l, r1 = v[k].r;
			} else if (h[k].r > r1) r1 = h[k].r;
		itv tmp; tmp.l = l1, tmp.r = r1, tmp.x = h[i].x;
		h2.push_back(tmp);
	}
	v2.clear();
	std::sort(v.begin(), v.end());
	for (int i = 0, j = 0; i < v.size(); i = j) {
		while (j < v.size() && v[i].x == v[j].x) j++;
		int l1 = v[i].l, r1 = v[i].r;
		for (int k = i+1; k < j; k++)
			if (v[k].l > r1) {
				itv tmp; tmp.l = l1, tmp.r = r1, tmp.x = v[i].x;
				v2.push_back(tmp);
				l1 = v[k].l, r1 = v[k].r;
			} else if (v[k].r > r1) r1 = v[k].r;
		itv tmp; tmp.l = l1, tmp.r = r1, tmp.x = v[i].x;
		v2.push_back(tmp);
	}
	h = h2, v = v2;
	h2.clear(), v2.clear();
	T.clear(); N = 0;
	for (int i = 0; i < h.size(); i++) {
		std::vector<int> tmp;
		tmp.push_back(h[i].l), tmp.push_back(h[i].r);
		for (int j = 0; j < v.size(); j++)
			if (v[j].x >= h[i].l && v[j].x <= h[i].r && h[i].x >= v[j].l && h[i].x <= v[j].r)
				tmp.push_back(v[j].x);
		std::sort(tmp.begin(), tmp.end());
		tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
		for (int j = 0; j < tmp.size(); j++) {
			T.insert(std::make_pair(std::make_pair(tmp[j], h[i].x), N));
			x[N] = tmp[j], y[N] = h[i].x, a[N].clear(), u[N].clear(), opi[N].clear(), d[N++].clear();
		}
		for (int j = 0; j+1 < tmp.size(); j++) {
			int x = T[std::make_pair(tmp[j], h[i].x)], y = T[std::make_pair(tmp[j+1], h[i].x)];
			a[x].push_back(y), a[y].push_back(x);
			d[x].push_back(0), d[y].push_back(2);
			u[x].push_back(-1), u[y].push_back(-1);
			opi[x].push_back(a[y].size()-1), opi[y].push_back(a[x].size()-1);
		}
	}
	for (int i = 0; i < v.size(); i++) {
		std::vector<int> tmp;
		tmp.push_back(v[i].l), tmp.push_back(v[i].r);
		for (int j = 0; j < h.size(); j++)
			if (h[j].x >= v[i].l && h[j].x <= v[i].r && v[i].x >= h[j].l && v[i].x <= h[j].r)
				tmp.push_back(h[j].x);
		std::sort(tmp.begin(), tmp.end());
		tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
		for (int j = 0; j+1 < tmp.size(); j++) {
			int x = T[std::make_pair(v[i].x, tmp[j])], y = T[std::make_pair(v[i].x, tmp[j+1])];
			a[x].push_back(y), a[y].push_back(x);
			d[x].push_back(1), d[y].push_back(3);
			u[x].push_back(-1), u[y].push_back(-1);
			opi[x].push_back(a[y].size()-1), opi[y].push_back(a[x].size()-1);
		}
	}
	/*
	for (int i = 0; i < N; i++) {
		printf("%d %d: ", x[i], y[i]);
		for (int j = 0; j < a[i].size(); j++)
			printf("%d %d,", x[a[i][j]], y[a[i][j]]);
		puts("");
	}
	*/
	m = 0;
	int outside = -1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < a[i].size(); j++)
			if (u[i][j] == -1) {
				u[i][j] = m;
				int p = a[i][j], pd = d[i][j];
				f[m].clear();
				while (1) {
					f[m].push_back(p);
					int mind = -1, minp, mink;
					for (int k = 0; k < a[p].size(); k++)
						if (mind == -1 || (d[p][k]-pd-2&3) > (mind-pd-2&3)) {
							mind = d[p][k], minp = a[p][k], mink = k;
						}
					u[p][mink] = m;
					p = minp, pd = mind;
					if (p == a[i][j] && pd == d[i][j]) break;
				}
				long long size = 0;
				for (int p = 0; p < f[m].size(); p++) {
					int q = (p+1)%f[m].size();
					size += 1LL*x[f[m][p]]*y[f[m][q]]-1LL*y[f[m][p]]*x[f[m][q]];
				}
				if (size <= 0) outside = m;
				m++;
			}
	/*
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < f[i].size(); j++)
			printf("%d %d ", x[f[i][j]], y[f[i][j]]);
		puts("");
	}
	*/
	int sf = outside, tf = outside;
	for (int i = 0; i < m; i++)
		if (i != outside && judge(xh, yh, i)) sf = i;
	for (int i = 0; i < m; i++)
		if (i != outside && judge(xu, yu, i)) tf = i;
	for (int i = 0; i < m; i++) b[i].clear();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < a[i].size(); j++)
			b[u[i][j]].push_back(u[a[i][j]][opi[i][j]]);
	memset(g, -1, sizeof g);
	g[sf] = 0;
	int l = 0, r = 0; q[0] = sf;
	while (l <= r) {
		for (int i = 0; i < b[q[l]].size(); i++)
			if (g[b[q[l]][i]] == -1) {
				g[b[q[l]][i]] = g[q[l]]+1;
				q[++r] = b[q[l]][i];
			}
		l++;
	}
	printf("Peter has to cross %d streets\n", g[tf]);
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("City %d\n", ++_), solve();
	return 0;
}
