#include <cstdio>
#include <set>
#include <algorithm>
std::set<int> T1, T2;
struct rec {
	int a, b;
} a[500000];
int cmp(rec a, rec b) {
	return std::abs(a.b) > std::abs(b.b);
}
void solve() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i].a, &a[i].b);
	std::sort(a, a + n, cmp);
	T1.clear(), T2.clear();
	int ans = -(~0U>>1);
	for (int i = 0; i < n; i++) {
		if (a[i].b < 0) {
			std::set<int>::iterator it = T1.lower_bound(a[i].a);
			if (it != T1.end()) {
				int tmp = (*it - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
			if (it != T1.begin()) {
				--it; int tmp = (a[i].a - *it) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
		} else {
			if (T1.size() > 0) {
				int tmp = std::abs(*T1.begin() - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
				tmp = std::abs(*--T1.end() - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
		}
		if (a[i].b >= 0) {
			std::set<int>::iterator it = T2.lower_bound(a[i].a);
			if (it != T2.end()) {
				int tmp = -(*it - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
			if (it != T2.begin()) {
				--it; int tmp = -(a[i].a - *it) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
		} else {
			if (T2.size() > 0) {
				int tmp = -std::abs(*T2.begin() - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
				tmp = -std::abs(*--T2.end() - a[i].a) * a[i].b;
				if (tmp > ans) ans = tmp;
			}
		}
		if (a[i].b >= 0) T1.insert(a[i].a);
		else T2.insert(a[i].a);
	}
	printf("%d\n", ans);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
