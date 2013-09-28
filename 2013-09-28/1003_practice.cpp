#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#define M 300001
struct hash_t {
	int x, y, id;
};
std::vector<hash_t> h[M];
int n, m, k, x[500], y[500], b[500][500], b_[500][500], a[125000], c[500], d, s[500], id[500];
std::priority_queue<std::pair<int, int> > q;
int hash(int dx, int dy) {
	return ((dx * 1001 + dy) % M + M) % M;
}
int hash_search(int dx, int dy) {
	int hnum = hash(dx, dy);
	for (int i = 0; i < h[hnum].size(); i++)
		if (h[hnum][i].x == dx && h[hnum][i].y == dy)
			return h[hnum][i].id;
	return -1;
}
void hash_insert(int dx, int dy, int id) {
	int hnum = hash(dx, dy);
	hash_t tmp;
	tmp.x = dx, tmp.y = dy, tmp.id = id;
	h[hnum].push_back(tmp);
}
int main() {
	for (; scanf("%d%d", &n, &m) != EOF; ) {
		for (int i = 0; i < n; i++)
			scanf("%d%d", &x[i], &y[i]), c[i] = 0, s[i] = -1;
		for (int i = 0; i < M; i++) h[i].clear();
		for (; !q.empty(); q.pop());
		k = 0;
		int n_ = 0;
		for (int i = 0; i < n; i++) if (s[i] == -1) {
			id[n_++] = i, s[i] = n_-1;
			for (int j = i+1; j < n; j++) if (s[j] == -1) {
				int dx = x[j]-x[i], dy = y[j]-y[i];
				if (dx == 0 && dy == 0) {
					s[j] = n_-1;
					continue;
				}
				if (dy < 0 || dy == 0 && dx < 0)
					dx = -dx, dy = -dy;
				int t = std::__gcd(std::abs(dx), std::abs(dy));
				dx /= t, dy /= t;
				if ((t = hash_search(dx, dy)) == -1) {
					t = k++;
					hash_insert(dx, dy, t);
					a[t] = 0;
					q.push(std::make_pair(0, t));
				}
				b_[i][j] = b_[j][i] = t;
			}
		}
		n = n_;
		for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++)
				b[i][j] = b[j][i] = b_[id[i]][id[j]];
		d = 0;
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v), v--;
			v = s[v];
			int delta = u ? -1 : 1;
			c[v] += delta;
			if (c[v] == !u) {
				std::set<int> set;
				for (int j = 0; j < n; j++)
					if (j != v && c[j]) set.insert(b[v][j]);
				d += delta;
				for (std::set<int>::iterator it = set.begin(); it != set.end(); it++)
					a[*it] -= delta, q.push(std::make_pair(-a[*it], *it));
				for (; !q.empty() && a[q.top().second] != -q.top().first; q.pop());
			}
			if (q.empty())
				printf("%d\n", d ? 1 : 0);
			else
				printf("%d\n", -q.top().first + d);
		}
		puts("");
	}
	return 0;
}
