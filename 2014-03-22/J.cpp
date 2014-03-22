#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

struct Edge {
	int y, z; Edge *next;
}*a[MAXN], POOL[MAXN], *data = POOL;

inline void AddEdge(int x, int y, int z) {
	Edge *tmp = data++;
	tmp->y = y; tmp->z = z; tmp->next = a[x]; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->z = z; tmp->next = a[y]; a[y] = tmp;
}

int n;long long t[MAXN], k[MAXN];long long dt[MAXN], dw[MAXN], sum[MAXN], father[MAXN];

vector<int> tmp[MAXN];

inline bool cmp(int x, int y) {
	return (long long)dw[x] * dt[y] > (long long)dw[y] * dt[x];
}

long long Dfs(int u, int f = 0) {
	tmp[u].clear(); tmp[u].push_back(u);
	dt[u] = t[u]; dw[u] = k[u];
	long long S = 0;
	for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
		father[p->y] = p->z;
		S += Dfs(p->y, u);
		dt[p->y] += 2 * p->z;
		tmp[u].push_back(p->y);
	}
	sort(tmp[u].begin(), tmp[u].end(), cmp);
	long long t = 0, T = 0;
	for (vector<int>::iterator it = tmp[u].begin(); it != tmp[u].end(); ++it) {
		T += dw[*it] * (t + (*it == u ? 0 : father[*it]));
		t += dt[*it];
	}
	for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
		dt[u] += dt[p->y];
		dw[u] += dw[p->y];
	}
	return T + S;
}

inline void Make(int u) {
	for (vector<int>::iterator it = tmp[u].begin(); it != tmp[u].end(); ++it) if (*it == u) {
		printf("P %d\n", u);
	} else printf("M %d\n", *it), Make(*it), printf("M %d\n", u);
}

int main(void) {
	freopen("beetles.in", "r", stdin);
	freopen("beetles.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%I64d", t + i);
	for (int i = 1; i <= n; i++) scanf("%I64d", k + i);
	for (int i = 1; i <  n; i++) {
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		AddEdge(x, y, z);
	}
	long long ret = Dfs(1);
	for (int i = 1; i <= n; i++) ret += (long long)k[i] * t[i];
	printf("%I64d\n", ret);
	Make(1);
	return 0;
}

