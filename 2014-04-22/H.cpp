#include <cstdio>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Edge {
	int y; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data = POOL;

inline void AddEdge(int x, int y) {
	Edge *tmp = data++;
	tmp->y = y; tmp->next = a[x]; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->next = a[y]; a[y] = tmp;
}

int m, n;

int dnf[MAXN], low[MAXN], tim, cut[MAXN];


inline void Dfs(int u, int father) {
	dnf[u] = low[u] = ++tim;
	int cnt = 0;
	vector<int> tmp;
	for (Edge *p = a[u]; p; p = p->next) if (p->y != father) {
		if (!dnf[p->y]) {
			tmp.push_back(p->y);
			Dfs(p->y, u);
			low[u] = min(low[u], low[p->y]);
			cnt++;
		} else low[u] = min(low[u], dnf[p->y]);
	}
	if (u != 1) for (int i = 0; i < (int)tmp.size(); i++) cut[u] |= (low[tmp[i]] >= dnf[u]); else
	if (u == 1 && cnt > 1) cut[u] = 1;
}

int cur;
int sum[MAXN];
int vis[MAXN];
set<int> cnt[MAXN]; 

inline void color(int u) {
	vis[u] = cur; sum[cur]++;
	// printf("%d\n", u);
	for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y]) {
		if (!cut[p->y]) {
			color(p->y); 
		}else {
			cnt[cur].insert(p->y);
		}
	}
}

inline void clear(void) {
	memset(vis, 0, sizeof vis);
	memset(dnf, 0, sizeof dnf);
	memset(cut, 0, sizeof cut);
	memset(sum, 0, sizeof sum);
	data = POOL; tim = 0; cur = 0; n = 0;
	memset(a, 0, sizeof a);
}

int main(void) {
	//freopen("in", "r", stdin);
	int kase = 0;
	while (scanf("%d", &m), m) {
		clear();
		for (int i = 1; i <= m; i++) {
			int x, y; scanf("%d%d", &x, &y);
			AddEdge(x, y);
			n = max(n, x); n = max(n, y);
		}
		Dfs(1, 0);
		int tmp = 0;
		for (int i = 1; i <= n; i++) tmp += cut[i];
		if (tmp == 0) {
			printf("Case %d: 2 %lld\n", ++kase, (long long)n * (n - 1) / 2);
			continue;
		}
		// for (int i = 1; i <= n; i++) printf("@%d, dnf: %d, low: %d\n", i, dnf[i], low[i]);
		//for (int i = 1; i <= n; i++) if (cut[i]) printf("%d ", i); puts("");
		for (int i = 1; i <= n; i++) if (!vis[i] && !cut[i]) {
			++cur;
			color(i);
		}
		int Ans = 0; long long ret = 1;
		for (int i = 1; i <= cur; i++) if (cnt[i].size() == 1u) {
			Ans++;
			ret *= (long long)sum[i];
		}
		printf("Case %d: %d %lld\n", ++kase, Ans, ret);
		for (int i = 1; i <= n; i++) cnt[i].clear();
	}
	return 0;
}

