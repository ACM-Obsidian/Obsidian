#include <cstdio>
#include <cstring>
#include <vector>
#define maxn 4000000
int f[65536][17], u[65536][17], h[65536], n, m;
struct rec {
	int y, z;
} q[maxn];
std::vector<std::pair<int, int> > g[17];
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) g[i].clear();
	for (int i = 0; i < m; i++) {
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		x--, y--;
		g[x].push_back(std::pair<int, int>(y, v));
		g[y].push_back(std::pair<int, int>(x, v));
	}
	int k, mask = 0;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int x;
		scanf("%d", &x);
		mask |= 1 << x-2;
	}
	memset(f, 0x3F, sizeof f);
	memset(u, 0, sizeof u);
	f[0][0] = 0;
	int ql = 0, qr = 0;
	q[0].y = 0, q[0].z = 0;
	u[0][0] = 1;
	for (; ql != (qr==maxn-1?0:qr+1); ql==maxn-1?ql=0:ql++) {
		int y = q[ql].y, z = q[ql].z;
		for (int i = 0; i < g[z].size(); i++)
			if (f[y][z]+g[z][i].second < f[g[z][i].first?y|1<<g[z][i].first-1:y][g[z][i].first]) {
				f[g[z][i].first?y|1<<g[z][i].first-1:y][g[z][i].first] = f[y][z] + g[z][i].second;
				if (!u[g[z][i].first?y|1<<g[z][i].first-1:y][g[z][i].first]) {
					qr==maxn-1?qr=0:qr++;
					q[qr].y = (g[z][i].first?y|1<<g[z][i].first-1:y), q[qr].z = g[z][i].first;
					u[g[z][i].first?y|1<<g[z][i].first-1:y][g[z][i].first] = 1;
				}
			}
		u[y][z] = 0;
	}
	memset(h, 0x3F, sizeof h);
	for (int i = 0; i < 1<<n-1; i++) {
		for (int j = 0; j < n; j++)
			if (f[i][j] < h[i]) h[i] = f[i][j];
		for (int j = 0; j < n; j++)
			if (!(mask&1<<j) && !(i&1<<j) && h[i] < h[i|1<<j]) h[i|1<<j] = h[i];
	}
	int ans = ~0U>>1;
	for (int i = 0; i < 1<<n-1; i++) {
		for (int j = ~i&(1<<n-1)-1; j; j--, j &= ~i&(1<<n-1)-1) {
			int tmp = h[i];
			if (h[j] > tmp) tmp = h[j];
			if (h[(1<<n-1)-1-i-j] > tmp) tmp = h[(1<<n-1)-1-i-j];
			if (tmp < ans) ans = tmp;
		}
		int tmp = h[i];
		if (h[(1<<n-1)-1-i] > tmp) tmp = h[(1<<n-1)-1-i];
		if (tmp < ans) ans = tmp;
	}
	if (ans >= ~0U>>3) puts("-1");
	else printf("%d\n", ans);
}
int main() {
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; printf("Case %d: ", _), _++, solve());
	return 0;
}
