#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 100510;
const int MAXM = MAXN;

int n, m, L;

int Swap[MAXM];

char c1[50510][200], c2[50510][200];
vector<int> neibor[MAXM];
set<string> S;
set<pair<int, int> > straight;
set<pair<int, int> > E;
set<int> End;
pair<int, int> req[MAXM];
map<string, int> M;
map<pair<int, int>, int> number;

int vis[MAXM], B_E[MAXN];

struct Edge {
	int y; Edge *next, *opt;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

inline void AddEdge(int x, int y) {
	y += n;
	a[x] = new Edge(y, a[x]);
	a[y] = new Edge(x, a[y]);
	a[x]->opt = a[y]; a[y]->opt = a[x];
}

int match[MAXN];
int levelx[MAXN], levely[MAXN], Link[MAXN];
int d[MAXN];

inline bool Bfs(void) {
	int head = 1, tail = 0;
	memset(levely, 0, sizeof levely);
	for (int i = 1; i <= n; i++) {
		if (!match[i]) d[++tail] = i;
		levelx[i] = 0;
	}
	bool ret = false;
	while (head <= tail) {
		int now = d[head++];
		for (Edge *p = a[now]; p; p = p->next) if (levely[p->y] == 0) {
			levely[p->y] = levelx[now] + 1;
			if (Link[p->y] == 0) ret = true;
			else levelx[Link[p->y]] = levely[p->y] + 1, d[++tail] = Link[p->y];
		}
	}
	return ret;
}

bool Find(int u) {
	for (Edge *p = a[u]; p; p = p->next) if (levely[p->y] == levelx[u] + 1) {
		levely[p->y] = 0;
		if (Link[p->y] == 0 || Find(Link[p->y])) {
			match[u] = p->y; Link[p->y] = u;
			return true;
		}
	}
	return false;
}

inline int Match(void) {
	int ret = 0;
	while (Bfs())
		for (int i = 1; i <= n; i++)
			if (!match[i]) ret += Find(i);
	return ret;
}

inline void MakeGraph(void) {
	for (set<pair<int, int> >::iterator it = E.begin(); it != E.end(); ++it) {
		neibor[it->first].push_back(it->second);
		neibor[it->second].push_back(it->first);
	}
	for (int i = 1; i <= L; i++) sort(neibor[i].begin(), neibor[i].end());
	for (int i = 1; i <= n; i++) if (vis[i] == 0) {
		int x = req[i].first, y = req[i].second;
		if (neibor[x].size() > neibor[y].size()) swap(x, y);
		vector<int> &X = neibor[x], &Y = neibor[y];
		for (vector<int>::iterator it = X.begin(); it != X.end(); ++it) if (!B_E[*it]) {
			vector<int>::iterator tmp = lower_bound(Y.begin(), Y.end(), *it);
			if (tmp != Y.end() && *tmp == *it) {
				//printf("%d %d\n", i, *it);
				AddEdge(i, *it);
			}
		}
	}
}

int main(void) {
	freopen("tickets.in", "r", stdin);
	freopen("tickets.out", "w", stdout);
	scanf("%d%d\n", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%[^,], %[^\r\n]\n", c1[i], c2[i]);
		S.insert(string(c1[i]));
		S.insert(string(c2[i]));
	}
	for (int i = 1; i <= m; i++) {
		scanf("%[^,], %[^\r\n]\n", c1[i + n], c2[i + n]);
		S.insert(string(c1[i + n]));
		S.insert(string(c2[i + n]));
	}
	for (set<string>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++L;
	for (int i = 1; i <= n; i++) {
		int x = M[string(c1[i])];
		int y = M[string(c2[i])];
		if (End.find(y) != End.end()) {
			puts("NO");
			exit(0);
		}
		End.insert(y);
		if (x > y) swap(x, y), Swap[i] = true;
		B_E[x] = B_E[y] = true;
		req[i].first = x; req[i].second = y;
	}
	for (int i = 1; i <= m; i++) {
		int x = M[string(c1[i + n])];
		int y = M[string(c2[i + n])];
		if (x > y) swap(x, y);
		E.insert(make_pair(x, y));
		number[make_pair(x, y)] = i;
	}
	for (int i = 1; i <= n; i++) {
		int x = req[i].first, y = req[i].second;
		if (E.find(make_pair(x, y)) != E.end()) {
			straight.insert(make_pair(x, y));
			E.erase(make_pair(x, y));
			vis[i] = number[make_pair(x, y)];
		}
	}
	MakeGraph();
	int Tmp = Match();
	if (Tmp != n - (int)straight.size()) {
		puts("NO");
	} else {
		puts("YES");
		for (int i = 1; i <= n; i++) {
			if (vis[i]) {
				printf("1 %d\n", vis[i]);
			} else {
				int x = req[i].first;
				int y = req[i].second;
				int z = match[i] - n;
				if (Swap[i]) swap(x, y);
				//printf("%d %d %d\n", x, y, z);
				printf("2 %d %d\n", number[make_pair(min(x, z), max(x, z))], number[make_pair(min(y, z), max(y, z))]);
			}
		}
	}
	return 0;
}

