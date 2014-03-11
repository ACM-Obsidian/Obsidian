#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <sstream>

using namespace std;

const int MAXN = 50010;

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN], *e[MAXN];

map<string, int> M; int L = 0; string st, ss;
int n; char str[MAXN];

inline int get(const string& st) {
	if (M.find(st) == M.end()) return M[st] = ++L; else return M[st];
}

int tim[MAXN], low[MAXN], cnt = 0, sum[MAXN], belong[MAXN], in_stack[MAXN], stack[MAXN], top = 0, scc = 0;

inline void Dfs(int u) {
	tim[u] = low[u] = ++cnt; in_stack[u] = 1;
	stack[++top] = u;
	for (Edge *p = a[u]; p; p = p->next) {
		if (!tim[p->y]) {
			Dfs(p->y);
			low[u] = min(low[u], low[p->y]);
		} else 
			if (in_stack[p->y]) low[u] = min(low[u], tim[p->y]);
	}
	if (low[u] == tim[u]) {
		int j; ++scc;
		do {
			j = stack[top--];
			in_stack[j] = false;
			belong[j] = scc;
			sum[scc]++;
		} while (j != u);
	}
}

int inp[MAXN], d[MAXN], f[MAXN], g[MAXN], Ans[MAXN];pair<int, int> h[MAXN];
int author[MAXN];

int main(void) {
	freopen("join.in", "r", stdin);
	freopen("join.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) h[i].first = -1;
	for (int i = 1; i <= n; i++) {
		scanf("%s", str); str[strlen(str) - 1] = 0; st = str;
		int x = get(st);
		gets(str); st = str; istringstream fin(st);
		int t = 0, w = 0;
		while (fin >>ss) {
			if (ss[0] == '@') {
				int y = get(ss); if (y == x) continue;
				if (h[y].first > t) t = h[y].first, w = h[y].second;
			}
		}
		if (t + 1 > h[x].first) h[x].first = t + 1, h[x].second = i;
		f[i] = t + 1, g[i] = w;
	} 
	int t = 0, w = 0;
	for (int i = 1; i <= n; i++) if (f[i] > t) t = f[i], w = i;
	while (w) {
		Ans[++top] = w;
		w = g[w];
	}
	printf("%d\n", t);
	for (int i = top; i >= 1; i--) printf("%d ", Ans[i]);
	return 0;
}

