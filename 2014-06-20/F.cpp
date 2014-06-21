#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

pair<int, int> a[MAXN], b[MAXN];

int n, d[2][MAXN], top[2];

inline int cmp(const pair<int, int>& x,  const pair<int, int>& y) {
	if (x.first != y.first) return x.first < y.first; else return x.second > y.second;
}

int main(void) {
//	freopen("in", "r", stdin);
	int kase; scanf("%d", &kase); while (kase--) {
		scanf("%d", &n); top[0] = top[1] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &a[i].first, &a[i].second);
			if (a[i].second < a[i].first) swap(a[i].first, a[i].second);
		}
		sort(a + 1, a + n + 1, cmp); a[0].second = ~0u>>1;
		int fail = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i].second <= a[d[0][top[0]]].second) {
				d[0][++top[0]] = i;
			} else 
			if (a[i].second <= a[d[1][top[1]]].second) {
				d[1][++top[1]] = i;
			} else {
				fail = 1;
				break;
			}
		}
		if (fail) {puts("no"); continue;}
		fail = 1;
		for (int _ = 0; _ <= 1 && fail; _++) {
			for (int k = 0; k <= 1 && fail; k++) {
				for (int i = 1; i <= top[k^1]; i++) b[i] = a[d[k^1][i]];
				int tmp = n;
				for (int i = 1; i <= top[k]; i++) {
					b[tmp].first = a[d[k][i]].second; b[tmp].second = a[d[k][i]].first; tmp--;
				}
				int ok = 1;
				for (int i = 2; i <= n; i++) {
					if (!(b[i].first >= b[i - 1].first && b[i].second <= b[i - 1].second)) {
						ok = 0;
						break;
					}
				}
				if (ok) fail = 0;
			}
			if (top[0] && top[1]) swap(d[0][top[0]], d[1][top[1]]);
		}
		if (fail) puts("no"); else {
			puts("yes");
			for (int i = 1; i <= n; i++) printf("%d %d\n", b[i].first, b[i].second);
		}
	}
	return 0;
}

