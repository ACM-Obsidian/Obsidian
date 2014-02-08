// no test data, examined by comparing with brute force
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
typedef int int128_t __attribute__((mode(TI)));
struct qtype {
	long long x, y;
	int id;
} a[200000];
std::vector<std::pair<int, int> > g[100000];
std::priority_queue<std::pair<long long, int> > q;
typedef std::pair<long long, long long> tuple;
std::set<tuple> t;
typedef std::pair<tuple, tuple> quad;
struct compare {
	bool operator () (quad a, quad b) {
		return (int128_t)a.first.first * b.first.second < (int128_t)a.first.second * b.first.first;
	}
};
std::set<quad, compare> t2;
long long d1[100000], d2[100000], ans[100000];
bool cmp(qtype a, qtype b) {
	return (int128_t)a.x * b.y > (int128_t)a.y * b.x;
}
void set_insert(tuple p) {
	std::set<tuple>::iterator it = t.insert(p).first, it1 = it, it2 = it;
	if (it != t.begin()) {
		it1--; t2.insert(quad(tuple(p.first - it1->first, p.second - it1->second), *it1));
	}
	if (it != --t.end()) {
		it2++; t2.insert(quad(tuple(it2->first - p.first, it2->second - p.second), p));
	}
	if (it != t.begin() && it != --t.end())
		t2.erase(quad(tuple(it2->first - it1->first, it2->second - it1->second), *it1));
}
void set_erase(tuple p) {
	std::set<tuple>::iterator it = t.find(p), it1 = it, it2 = it;
	if (it != t.begin()) {
		it1--; t2.erase(quad(tuple(p.first - it1->first, p.second - it1->second), *it1));
	}
	if (it != --t.end()) {
		it2++; t2.erase(quad(tuple(it2->first - p.first, it2->second - p.second), p));
	}
	if (it != t.begin() && it != --t.end())
		t2.insert(quad(tuple(it2->first - it1->first, it2->second - it1->second), *it1));
	t.erase(it);
}
void process(int len) {
	t.clear(); t2.clear();
	for (int i = 0; i < len; i++) {
		if (a[i].id == -1) {
			std::set<tuple>::iterator it = t.lower_bound(tuple(a[i].x, a[i].y)), it2, it3;
			if (it != t.begin() && it != t.end()) {
				it2 = it; it2--;
				if ((int128_t)(it->first - it2->first) * (it->second - a[i].y) >= (int128_t)(it->second - it2->second) * (it->first - a[i].x))
					continue;
			}
			if (it != t.begin()) {
				it2 = it; it2--;
				while (it2 != t.begin()) {
					it3 = it2; it3--;
					if ((int128_t)(it3->first - it2->first) * (it2->second - a[i].y) < (int128_t)(it3->second - it2->second) * (it2->first - a[i].x))
						break;
					set_erase(*it2);
					it2 = it3;
				}
			}
			if (it != t.end()) {
				it2 = it;
				while (it2 != --t.end()) {
					it3 = it2; it3++;
					if ((int128_t)(it3->first - it2->first) * (it2->second - a[i].y) > (int128_t)(it3->second - it2->second) * (it2->first - a[i].x))
						break;
					set_erase(*it2);
					it2 = it3;
				}
			}
			set_insert(tuple(a[i].x, a[i].y));
		} else {
			if (!t.size()) continue;
			long long x, y;
			if (!t2.size()) {
				x = t.begin()->first, y = t.begin()->second;
			} else {
				std::set<quad, compare>::iterator it = t2.lower_bound(quad(tuple(a[i].x, a[i].y), tuple(0, 0)));
				if (it == t2.end()) {
					it--; x = it->first.first + it->second.first, y = it->first.second + it->second.second;
				} else {
					x = it->second.first, y = it->second.second;
				}
			}
			if (x * a[i].y - y * a[i].x < ans[a[i].id])
				ans[a[i].id] = x * a[i].y - y * a[i].x;
		}
	}
}
void solve() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		g[i].clear();
		d1[i] = d2[i] = ~0ULL>>1;
	}
	while (m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--, v--;
		g[u].push_back(std::make_pair(v, w));
		g[v].push_back(std::make_pair(u, w));
	}
	d1[0] = 0;
	q.push(std::make_pair(0, 0));
	while (1) {
		while (!q.empty() && d1[q.top().second] != -q.top().first) q.pop();
		if (q.empty()) break;
		int u = q.top().second; q.pop();
		for (int i = 0; i < g[u].size(); i++)
			if (d1[g[u][i].first] > d1[u] + g[u][i].second) {
				d1[g[u][i].first] = d1[u] + g[u][i].second;
				q.push(std::make_pair(-d1[g[u][i].first], g[u][i].first));
			}
	}
	d2[n-1] = 0;
	q.push(std::make_pair(0, n-1));
	while (1) {
		while (!q.empty() && d2[q.top().second] != -q.top().first) q.pop();
		if (q.empty()) break;
		int u = q.top().second; q.pop();
		for (int i = 0; i < g[u].size(); i++)
			if (d2[g[u][i].first] > d2[u] + g[u][i].second) {
				d2[g[u][i].first] = d2[u] + g[u][i].second;
				q.push(std::make_pair(-d2[g[u][i].first], g[u][i].first));
			}
	}
	for (int i = 0; i < k; i++)
		scanf("%lld%lld", &a[i].y, &a[i].x), a[i].id = i, ans[i] = ~0ULL>>1;
	int len = k;
	for (int i = 0; i < n; i++)
		if (d1[i] < ~0ULL>>1 && d2[i] < ~0ULL>>1) {
			a[len].x = d1[i], a[len].y = d2[i], a[len].id = -1;
			len++;
		}
	std::sort(a, a+len, cmp);
	process(len);
	for (int i = 0; i < len; i++)
		std::swap(a[i].x, a[i].y);
	std::reverse(a, a+len);
	process(len);
	for (int i = 0; i < k; i++)
		printf("%lld\n", ans[i]);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
