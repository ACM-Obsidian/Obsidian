#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
std::bitset<50000> a[50000], b[50000];
std::vector<int> g[50000], g_[50000];
std::pair<int, int> t[50000];
int c[50000], q[50001], u[50000];
int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		x--, y--;
		g[x].push_back(y), g_[y].push_back(x);
	}
	for (int i = 0; i < n; i++) scanf("%d", &c[i]), t[i] = std::make_pair(c[i], i);
	std::sort(t, t + n);
	for (int i = 0; i < n; i++) {
		if (i > 0) b[i] = b[i-1];
		b[i].set(t[i].second, 1);
	}
	int l = 0, r = 0; q[0] = 0, u[0] = 1;
	while (l != (r == n ? 0 : r+1)) {
		int t = q[l];
		u[t] = 0;
		l == n ? l = 0 : l++;
		std::bitset<50000> tmp;
		if (t != 0)
			tmp.set();
		for (int i = 0; i < g_[t].size(); i++)
			if (a[g_[t][i]].test(g_[t][i]))
				tmp &= a[g_[t][i]];
		tmp.set(t, 1);
		if (tmp != a[t]) {
			a[t] = tmp;
			for (int i = 0; i < g[t].size(); i++)
				if (!u[g[t][i]]) {
					u[g[t][i]] = 1;
					r == n ? r = 0 : r++;
					q[r] = g[t][i];
				}
		}
	}
	int q; scanf("%d", &q);
	while (q--) {
		int k, x; scanf("%d", &k);
		std::bitset<50000> tmp;
		tmp.set();
		for (int i = 0; i < k; i++) {
			scanf("%d", &x), x--;
			tmp &= a[x];
		}
		int l = 0, r = n-1;
		while (l < r) {
			int mid = l+r>>1;
			if ((tmp & b[mid]).any())
				r = mid;
			else
				l = mid+1;
		}
		printf("%d\n", t[l].first);
	}
	return 0;
}
