#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
struct rec {
	int x, y;
} a[100];
int n, b1, b2, pre[100][100][2];
double g[100][100][2];
std::vector<int> ansv1, ansv2;
int cmp(rec a, rec b) { return a.x < b.x; }
double dis(int x, int y) {
	return sqrt((a[y].x - a[x].x) * (a[y].x - a[x].x) + (a[y].y - a[x].y) * (a[y].y - a[x].y));
}
void solve() {
	for (int i = 0; i < n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	if (b1 > b2) std::swap(b1, b2);
	memset(g, 0x5d, sizeof g);
	g[0][0][0] = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			for (int f = 0; f < (i > b1 && i < b2 ? 2 : 1); f++)
				if (j == i-1) {
					for (int k = 0; k < (i-1 ? i-1 : 1); k++) {
						int f2 = (i > b1 && i < b2 ? !f : 0);
						double tmp = g[i-1][k][f2] + dis(k, i);
						if (tmp < g[i][j][f])
							g[i][j][f] = tmp, pre[i][j][f] = k;
					}
				} else {
					int f2 = (i > b1 && i < b2 ? f : (i == b2 ? 1 : 0));
					double tmp = g[i-1][j][f2] + dis(i-1, i);
					if (tmp < g[i][j][f])
						g[i][j][f] = tmp, pre[i][j][f] = i-1;
				}
	double ans = 1e10;
	int x = n-1, y = -1, f = 0, flag = 0;
	for (int i = 0; i < n-1; i++) {
		double tmp = g[n-1][i][0] + dis(i, n-1);
		if (tmp < ans) ans = tmp, y = i;
	}
	ansv1.clear(), ansv2.clear();
	while (x > 0) {
		if (x < n-1)
			if (flag) ansv2.push_back(x);
			else ansv1.push_back(x);
		if (pre[x][y][f] == x-1) {
			if (x == b2) f = 1;
			x--;
		} else {
			int tmp = pre[x][y][f];
			if (x > b1 && x < b2) f = !f;
			x = tmp;
			std::swap(x, y);
			flag = !flag;
		}
	}
	printf("%.2lf\n", ans);
	printf("0 ");
	if (ansv1[ansv1.size()-1] > ansv2[ansv2.size()-1]) std::swap(ansv1, ansv2);
	for (int i = ansv1.size()-1; i >= 0; i--)
		printf("%d ", ansv1[i]);
	printf("%d ", n-1);
	for (int i = 0; i < ansv2.size(); i++)
		printf("%d ", ansv2[i]);
	puts("0");
}
int main() {
	int _ = 0;
	while (scanf("%d%d%d", &n, &b1, &b2), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
