#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2020;

int n, m; pair<int, int> info[MAXN], room[MAXN];
vector<int> a[MAXN];

int match[MAXN];
int levelx[MAXN], link[MAXN];

int cur;

inline bool Find(int u) {
	for (vector<int>::iterator it = a[u].begin(); it != a[u].end(); ++it) if (levelx[*it] != cur) {
		levelx[*it] = cur;
		if (!link[*it] || Find(link[*it])) {
			link[*it] = u; match[u] = *it;
			return 1;
		}
	}
	return 0;
}

inline void Match(void) {
	for (int i = 1; i <= n; i++) ++cur, Find(i);
}

inline void clear(void) {
	memset(match, 0, sizeof match);
	memset(link, 0, sizeof link);
	memset(levelx, 0, sizeof levelx);
}

int main(void) {
//	freopen("in", "r", stdin);
	int kase = 0;
	while (scanf("%d", &n), n) {
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &info[i].first, &info[i].second);
			a[i].clear();
		}
		sort(info + 1, info + n + 1);
		reverse(info + 1, info + n + 1);
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			int x, hour, minute; scanf("%d %d:%d", &x, &hour, &minute);
			int d = (hour - 14) * 60 + minute;
			room[i] = make_pair(x, d);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) if (info[i].first <= room[j].first && info[i].second <= room[j].second) {
				a[i].push_back(j);
			}
		}
		clear();
		Match();
		int Ans1 = 0, Ans2 = 0;
		for (int i = 1; i <= n; i++) if (!match[i]) {
			Ans1++;
			Ans2 += info[i].first;
		}
		printf("Trial %d: %d %d\n\n", ++kase, Ans1, Ans2);
	}
	return 0;
}
