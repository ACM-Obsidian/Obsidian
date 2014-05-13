#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
std::pair<int, int> tmp[500];
int f[501][501], d[500][500], d2[500][500], a, b, m, n;
std::set<int> t;
std::multiset<std::pair<int, int> > set;
int main() {
	while (scanf("%d%d%d%d", &a, &b, &m, &n) == 4) {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) scanf("%d", &d[i][j]);
		if (a < b) std::swap(a, b);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= a && i <= m; i++) {
			for (int j = 0; j < n; j++) {
				t.clear();
				for (int k = 0; k < i; k++) t.insert(d[k][j]);
				for (int k = 0; k <= m-i; k++) {
					d2[k][j] = *t.begin();
					if (k < m-i) {
						t.erase(t.lower_bound(d[k][j]));
						t.insert(d[k+i][j]);
					}
				}
			}
			for (int j = 0; j <= m-i; j++) {
				for (int k = 0; k < n; k++) tmp[k] = std::make_pair(-d2[j][k], k);
				std::sort(tmp, tmp + n);
				int max = 0, pre = 0;
				set.clear();
				for (int k = 0; k < n; k++) {
					int l = tmp[k].second, r = l;
					std::multiset<std::pair<int, int> >::iterator it = set.lower_bound(std::pair<int, int>(l, l)), it2;
					if (it == set.begin()) it2 = set.end();
					else it2 = it, it2--;
					if (it != set.end() && it->first == tmp[k].second+1)
						r = it->second, set.erase(it);
					if (it2 != set.end() && it2->second == tmp[k].second-1)
						l = it2->first, set.erase(it2);
					if (r-l+1 > max) max = r-l+1;
					set.insert(std::make_pair(l, r));
					if (max > pre) {
						for (int t = pre+1; t <= max && t <= a; t++)
							if (f[i][t] < -tmp[k].first) f[i][t] = -tmp[k].first;
						pre = max;
					}
				}
			}
		}
		long long ans = 0;
		for (int i = 1; i <= a; i++)
			for (int j = 1; j <= b; j++) {
				int dep = std::max(f[i][j], f[j][i]);
				if (dep == 0) continue;
				long long numer = 1LL * m * n * dep, denom = m * n - i * j;
				long long v = 1LL * i * j * ((numer - 1) / denom);
				if (v > ans) ans = v;
			}
		printf("%lld\n", ans);
	}
	return 0;
}
