#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 110;

struct Edge {
	int y; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data = POOL;

int n, need[MAXN], death[MAXN], f[MAXN], sum[MAXN];

vector<int> tmp;

inline bool cmp(int x, int y) {
	return f[x] - sum[x] >= f[y] - sum[y];
}

inline int Dfs(int u, int father) {
	int &ret = f[u]; sum[u] = death[u];
	for (Edge *p = a[u]; p; p = p->next) if (p->y != father) {
		Dfs(p->y, u);
		sum[u] += sum[p->y];
	}
	tmp.clear();
	for (Edge *p = a[u]; p; p = p->next) if (p->y != father) tmp.push_back(p->y);
	sort(tmp.begin(), tmp.end(), cmp);
	ret = need[u]; int t = death[u];
	for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
		ret = max(ret, f[*it] + t);
		t += sum[*it];
	}
	return ret;
}

int main(void) {
	freopen("in", "r", stdin);
	int kase = 0; while (scanf("%d", &n), n) {
		data = POOL; memset(a, 0, sizeof a);
		for (int i = 1, x; i <= n; i++) {
			scanf("%d%d%d", need + i, death + i, &x);
			death[i] += x;
			need[i] = max(need[i], death[i]);
		}
		for (int i = 1; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			Edge *tmp = data++;
			tmp->y = y; tmp->next = a[x]; a[x] = tmp;
			tmp = data++;
			tmp->y = x; tmp->next = a[y]; a[y] = tmp;
		}
		int Ans = ~0U>>1;
		for (int i = 1; i <= n; i++) {
			Ans = min(Ans, Dfs(i, 0));
		}
		printf("Case %d: %d\n", ++kase, Ans);
	}
	return 0;
}

