#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
struct rec {
	int a, b, c;
};
int f[21][20][20], _ = 0, __, p[20], c[20], n, u[20][20][20];
std::pair<rec, int> pre[21][20][20];
rec q[20000];
std::vector<int> a[20];
void solve() {
	for (int i = 0; i < n; i++) {
		a[i].clear();
		scanf("%d", &p[i]);
		int t, x; scanf("%d", &t);
		t--; scanf("%d", &x), a[i].push_back(x);
		while (t--) {
			int x; scanf("%d", &x);
			a[i].push_back(x);
		}
	}
	int m; scanf("%d", &m);
	for (__ = 1; __ <= m; __++) {
		int k; scanf("%d", &k);
		for (int i = 0; i < k; i++) scanf("%d", &c[i]);
		memset(f, -1, sizeof f);
		memset(u, 0, sizeof u);
		int ans = ~0U>>1, ansa, ansb, ansc;
		int l = 0, r = 0;
		rec tmp;
		for (int i = 0; i < n; i++) if (a[i][0] == c[0]) {
			int A2 = 1;
			f[A2][i][0] = p[i];
			tmp.a = -1;
			pre[A2][i][0] = std::make_pair(tmp, i);
			q[r].a = A2, q[r].b = i, q[r].c = 0; r++; u[A2][i][0] = 1;
		}
		while (l != r) {
			int A = q[l].a, B = q[l].b, C = q[l].c;
			u[A][B][C] = 0;
			if (A == k) {
				if (f[A][B][C] < ans)
					ans = f[A][B][C], ansa = A, ansb = B, ansc = C;
				l++;
				continue;
			}
			if (C+1 < a[B].size()) {
				int A2 = A; if (a[B][C+1] == c[A]) A2++;
				if ((f[A2][B][C+1] == -1 || f[A2][B][C+1] > f[A][B][C])) {
					if (!u[A2][B][C+1]) q[r].a = A2, q[r].b = B, q[r].c = C+1, r = (r+1)%20000, u[A2][B][C+1] = 1;
					f[A2][B][C+1] = f[A][B][C];
					pre[A2][B][C+1] = pre[A][B][C];
				}
			}
			for (int i = 0; i < n; i++) if (a[i][0] == a[B][C]) {
				if (f[A][i][0] == -1 || f[A][i][0] > f[A][B][C] + p[i]) {
					if (!u[A][i][0]) q[r].a = A, q[r].b = i, q[r].c = 0, r = (r+1)%20000, u[A][i][0] = 1;
					f[A][i][0] = f[A][B][C] + p[i];
					pre[A][i][0] = std::make_pair(q[l], i);
				}
			}
			l = (l+1)%20000;
		}
		std::vector<int> ansv;
		while (ansa >= 0) {
			ansv.push_back(pre[ansa][ansb][ansc].second);
			tmp = pre[ansa][ansb][ansc].first;
			ansa = tmp.a, ansb = tmp.b, ansc = tmp.c;
		}
		printf("Case %d, Trip %d: Cost = %d\n  Tickets used:", _, __, ans);
		for (int i = ansv.size()-1; i >= 0; i--) printf(" %d", ansv[i]+1);
		puts("");
	}
}
int main() {
	while (scanf("%d", &n), n)
		++_, solve();
	return 0;
}
