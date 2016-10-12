#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int MAXN = 323;
const int MAXT = 200210;

int n, m, t, s[MAXN], a[MAXN][MAXN];
pair<int, int> Log[MAXT];

int current[MAXN][MAXN], occupied[MAXN];
int vis[MAXN], cur; 

bool deadlock() {
	cur++;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int ok = 1;
		for (int j = 1; j <= m; j++) if (current[i][j] < a[i][j]) {
			ok = 0;
			break;
		}
		if (ok) {
			cnt++;
			for (int j = 1; j <= m; j++) occupied[j] -= current[i][j];
			vis[i] = cur;
		}
	}
	for (int i = 1; i <= n - cnt; i++) {
		int w = -1;
		for (int k = 1; k <= n; k++) if (vis[k] != cur) {
			int ok = 1;
			for (int j = 1; j <= m; j++) if (!(s[j] - occupied[j] >= a[k][j] - current[k][j]) ) {
				ok = 0;
				break;
			}
			if (ok == 1) {w = k; break;}
		}
		vis[w] = cur;
		if (w == -1) return true;
		else {
			for (int j = 1; j <= m; j++) occupied[j] -= current[w][j];
		}
	}
	return false;
}

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= m; i++) scanf("%d", s + i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	for (int i = 1; i <= t; i++) scanf("%d%d", &Log[i].first, &Log[i].second);
	int l = 1, r = t;
	while (l <= r) {
		int mid = (l + r) >> 1;
		memset(current, 0, sizeof current);
		memset(occupied, 0, sizeof occupied);
		for (int i = 1; i <= mid; i++) {
			current[Log[i].first][Log[i].second]++;
			occupied[Log[i].second]++;
		}
		if (deadlock()) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", l == t + 1 ? -1 : l);
	return 0;
}

