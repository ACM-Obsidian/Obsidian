#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 21) + 20;

int d[MAXN], n, m, G[MAXN], dis[MAXN];
pair<int, int> path[MAXN];
vector<int> Ans;
int next[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m), n || m) {
		memset(G, 0, sizeof G); memset(dis, -1, sizeof dis);
		memset(path, -1, sizeof path); Ans.clear(); memset(next, 0, sizeof next);
		for (int i = 1; i <= m; i++) {
			int x, y; scanf("%d%d", &x, &y);
			G[x] |= (1 << y);
			G[y] |= (1 << x);
		}
		int head = 1, tail = 1; dis[ d[1] = (1 << n) - 1 ] = 0;
		while (head <= tail) {
			int now = d[head++];
			for (int i = n - 1; i >= 0; i--) if (now & (1 << i)) {
				next[i] = next[i + 1] | G[i];
			} else next[i] = next[i + 1];

			int last = 0;
			for (int i = 0; i < n; i++) if (now & (1 << i)) {
				int t = last | next[i + 1];
				if (dis[t] == -1) {
					d[++tail] = t;
					dis[t] = dis[now] + 1;
					path[t] = make_pair(i, now);
				}
				last |= G[i];
			}
		}
		if (dis[0] == -1) {
			puts("Impossible");
		} else {
			printf("%d:", dis[0]);
			int tmp = 0;
			while (path[tmp].second != -1) {
				Ans.push_back(path[tmp].first);
				tmp = path[tmp].second;
			}
			for (int i = (int)Ans.size() - 1; i >= 0; i--) printf(" %d", Ans[i]);
			puts("");
		}
	}
	return 0;
}

