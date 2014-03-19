#include <cstdio>
#include <cassert>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

inline int OPT(int u) {assert(u >= 0 && u < 4); return u ^ 2;}

const int MAXN = 50000;

int n, m; char ch[MAXN];
vector<int> list[MAXN]; int len[MAXN], f[MAXN];
set<int> sum[MAXN];

int must[MAXN];
int double_trans[MAXN][4], is_double[MAXN];

inline int get(int x) {return x == f[x] ? x : (f[x] = get(f[x]));}
inline void Merge(int x, int y) {
	int X = get(x);
	int Y = get(y);
	if (X != Y) f[X] = Y;
}

char fim[4] = {'A', 'G', 'T', 'C'};
int hash[255];

inline int getMust(const set<int>& T, int index, int group) {
	if (T.size() == 4) return -1;
	if (T.size() == 1) return 0;
	if (T.size() == 2) {
		__typeof(T.begin()) it = T.begin();
		int x = hash[*it];
		int y = hash[*++it];
		if (abs(x - y) == 2) return 1; else {
			is_double[index] = 1;
			double_trans[index][x] = group * 2 - 1;
			double_trans[index][y] = group * 2;
			return 0;
		}
	}
	for (int i = 0; i < 4; i++) if (T.find(fim[i]) == T.end()) {
		return fim[OPT(i)];
	}
	assert(false);
}

struct Edge {
	int y; Edge *next;
	Edge(){}
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN], POOL[MAXN << 1], *data;

inline void AddEdge(int x, int y) {
	Edge *tmp = data++;
	tmp->next = a[x]; tmp->y = y; a[x] = tmp; 
}

inline void connect(int x, int y) {
	if (is_double[x] && is_double[y]) {
		AddEdge(double_trans[x][OPT(fim[ch[x]])], double_trans[y][fim[ch[y]]]);
		AddEdge(double_trans[y][OPT(fim[ch[y]])], double_trans[x][fim[ch[x]]]);
	}
	if (is_double[x] && must[y]) {
		AddEdge(double_trans[x][OPT(fim[ch[x]])], double_trans[x][fim[ch[x]]]);
	}
	if (must[x] && is_double[y]) {
		AddEdge(double_trans[y][OPT(fim[ch[y]])], double_trans[y][fim[ch[y]]]);
	}
}

int tim, dnf[MAXN], low[MAXN], belong[MAXN], stack[MAXN], in_stack[MAXN], Sum = 0, top;

int Dfs(int u) {
	dnf[u] = low[u] = ++tim; in_stack[stack[++top] = u] = 1;
	for (Edge *p = a[u]; p ; p = p ->next) {
		if (!dnf[p->y]) {
			Dfs(p->y);
			low[u] = min(low[u], low[p->y]);
		} else if (in_stack[p->y])
			low[u] = min(low[u], dnf[p->y]);
	}
	if (dnf[u] == low[u]) {
		Sum++; int j;
		do {
			j = stack[top--];
			in_stack[j] = 0;
			belong[j] = 1;
		} while (j != u);
	}
}

inline void clear(void) {
	for (int i = 1; i <= n; i++) f[i] = i, sum[i].clear(); memset(sum, 0, sizeof sum);
	memset(must, 0, sizeof must);
	memset(double_trans, 0, sizeof double_trans);
	memset(is_double, 0, sizeof is_double);
	memset(a, 0, sizeof a);
	data = POOL;

	tim = 0; memset(dnf, 0, sizeof dnf); memset(low, 0, sizeof low);
	top = 0; memset(belong, 0, sizeof belong); Sum = 0;
}

int main(void) {
	hash['A'] = 0; hash['G'] = 1; hash['T'] = 2; hash['C'] = 3;
	while (scanf("%d%d", &n, &m), n || m) {
		scanf("%s", ch + 1);
		for (int i = 1; i <= m; i++) {
			scanf("%d:", len + i); list[i].clear();
			for (int j = 1; j <= len[i]; j++) {
				int x; scanf("%d", &x);
				list[i].push_back(x + 1);
			}
			int l = 0, r = len[i] - 1;
			while (l < r) Merge(l++, r--);
		}
		for (int i = 1; i <= n; i++) {
			int t = get(i);
			sum[t].insert(ch[i]);
		}
		bool _4 = false;
		for (int i = 1; i <= n; i++) {
			int g = get(i);
			must[i] = getMust(sum[g], i, g);
			if (must[i] < 0) {_4 = true; break;}
		}
		if (_4) {puts("NO"); continue;}
		for (int i = 1; i < n; i++) if (must[i] != 0 && must[i + 1] != 0) {
			_4 = true;
		}
		if (_4) {puts("NO"); continue;}

		// Build
		for (int i = 1; i < n; i++) {
			connect(i, i + 1);
		}
		for (int i = 1; i <= n * 2; i++) if (!dnf[i]) Dfs(i);
		for (int i = 1; i <= n; i++) if (belong[i * 2] == belong[i * 2 - 1]) {
			_4 = true;
			break;
		}
		puts(_4 ? "NO" : "YES");
	}
	return 0;
}

