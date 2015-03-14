#include <cstdio>
#include <cstring>
#include <algorithm>

#define cl(a) memset(a, 0, sizeof a)
using namespace std;

const int MAXN = 100010;

struct Edge {
	int y; Edge *next;
}*a[MAXN], POOL[MAXN], *data = POOL, *e[MAXN], POOL_T[MAXN], *data_t;

int n, m;

int vis[MAXN], inp[MAXN];
int low[MAXN], tim[MAXN], stack[MAXN], belong[MAXN], sum[MAXN], in_stack[MAXN];
int stamp, top, cnt;

void Dfs(int u) {
	tim[u] = low[u] = ++stamp;
	in_stack[ stack[++top] = u ] = true;
	for (Edge *p = a[u]; p; p = p->next) {
		if (!tim[p->y]) {
			Dfs(p->y);
			low[u] = min(low[u], low[p->y]);
		} else if (in_stack[p->y]) low[u] = min(low[u], tim[p->y]);
	}
	if (low[u] == tim[u]) {
		cnt++;
		int j;
		do {
			in_stack[ j = stack[top--] ] = false;
			belong[j] = cnt;
			sum[cnt]++;
		} while (j != u);
	}
}

void AddEdge(int x, int y, Edge **a, Edge*& data) {
	Edge *tmp = data++;
	tmp->y = y; tmp->next = a[x]; a[x] = tmp;
}

void color(int u) {
	vis[u] = 1;
	for (Edge *p = e[u]; p; p = p->next) if (!vis[p->y]) color(p->y);
}

int main(void) {
	freopen("field.in", "r", stdin);
	freopen("field.out", "w", stdout);
	int kase; scanf("%d", &kase); while (kase--) {
		scanf("%d%d", &n, &m);
		cl(a); cl(e);
		data = POOL; data_t = POOL_T;
		cl(vis); cl(inp); cl(low); cl(tim); cl(stack); cl(belong); cl(sum); cl(in_stack); stamp = 0; top = 0; cnt = 0;
		for (int i = 1; i <= m; i++) {
			int x, y; scanf("%d%d", &x, &y); x++, y++;
			AddEdge(x, y, a, data);
		}
		for (int i = 1; i <= n; i++) if (!tim[i]) {
			Dfs(i);
		}
		for (int i = 1; i <= n; i++) 
			for (Edge *p = a[i]; p; p = p->next) if (belong[i] != belong[p->y]) {
				AddEdge(belong[i], belong[p->y], e, data_t);
				inp[belong[p->y]]++;
			}
		int w = -1;
		for (int i = 1; i <= cnt; i++) if (inp[i] == 0) {w = i; break;}
		color(w);
		int count = 0;
		for (int i = 1; i <= cnt; i++) count += vis[i];
		if (count == cnt) {
			for (int i = 1; i <= n; i++) if (belong[i] == w) printf("%d\n", i - 1);
		} else puts("Confused");
		puts("");
	}
	return 0;
}

