#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 210000, inf = ~0u>>1;

struct Edge {
	int y; Edge *next, *opt; int f;
}*a[MAXN], POOL[2000000], *e[MAXN], *data = POOL;

inline void AddEdge(int x, int y, int flow) {
	Edge *tmp = data++;
	tmp->y = y; tmp->next = a[x]; tmp->f = flow; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->next = a[y]; tmp->f = 0; a[y] = tmp;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
//	printf("Add %d %d %d\n", x, y, flow);
}

int n, k, m, vs, vt, vs_; char ch[110][1100];

int level[MAXN], d[MAXN];
inline int Bfs(void) {
	memset(level, -1, sizeof level);
	d[1] = vs; level[vs] = 0;
	int head = 1, tail = 1;
	while (head <= tail) {
		int now = d[head++];
		e[now] = a[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1) 
			level[d[++tail] = p->y] = level[now] + 1;
	}
	return level[vt] != -1;
}

inline int Extend(int u, int sum) {
	if (u == vt) return sum;
	int r = 0, t;
	for (Edge *p = e[u]; p && r < sum; p = p->next) if (level[p->y] == level[u] + 1 && p->f > 0) {
		t = min(sum - r, p->f);
		t = Extend(p->y, t);
		p->f -= t, p->opt->f += t, r += t;
		e[u] = p;
	}
	if (!r) level[u] = -1;
	return r;
}

inline int Dinic(void) {
	int r = 0, t;
	while (Bfs()) {
		while (t = Extend(vs, inf)) r += t;
	}
	return r;
}

inline int getId(int i, int j) {return (i - 1) * m + j;}
inline int In(int i, int j) {return getId(i, j) * 2 - 1;}
inline int Out(int i, int j) {return getId(i, j) * 2;}
inline int Midin(int j) {return Out(n, m) + j * 2 - 1;}
inline int Midout(int j) {return Out(n, m) + j * 2;}
inline int getRow(int k) {return (((k + 1) / 2) - 1) / m + 1;}

vector<pair<int, pair<int, int> > > trans;
vector<int> init;

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", ch[i] + 1);
	vs = Midout(m - 1) + 1, vs_ = vs + 1, vt = vs_ + 1;
//	printf("vs %d, vs_  %d, vt %d\n", vs, vs_, vt);

	AddEdge(vs, vs_, k);
	for (int i = 1; i <= n; i++) AddEdge(vs_, In(i, 1), 1);
	for (int i = 1; i <= n; i++) AddEdge(Out(i, m), vt, 1);
	for (int j = 1; j < m; j++) {
		for (int i = 1; i <= n; i++) if (ch[i][j] == '1') {
			AddEdge(Out(i, j), Midin(j), 1);
		}
		for (int i = 1; i <= n; i++) if (ch[i][j + 1] == '1') {
			AddEdge(Midout(j), In(i, j + 1), 1);
		}
		for (int i = 1; i <= n; i++) if (ch[i][j] == '1' && ch[i][j + 1] == '1') {
			AddEdge(Out(i, j), In(i, j + 1), 1);
		}
		AddEdge(Midin(j), Midout(j), 1);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) if (ch[i][j] == '1') AddEdge(In(i, j), Out(i, j), 1);

	int ret = Dinic();
	if (ret != k) puts("FAIL"); else {
		puts("WIN");
		for (Edge *p = a[vs_]; p; p = p->next) if (p->f == 0) init.push_back(getRow(p->y));
		for (int i = 0; i < (int)init.size(); i++) printf("%d%c", init[i], " \n"[i == (int)init.size() - 1]);
		for (int j = 1; j < m; j++) {
			for (Edge *p = a[Midin(j)]; p; p = p->next) if (p->y == Midout(j) && p->f == 0) {
				int x, y;
				for (Edge *q = a[Midin(j)]; q; q = q->next) if (q->y != Midout(j) && q->f == 1) {
					x = getRow(q->y);
				//	break;
				}
				for (Edge *q = a[Midout(j)]; q; q = q->next) if (q->y != Midin(j) && q->f == 0) {
					y = getRow(q->y);
				//	break;
				}
				//printf("@%d exchange: %d %d\n", j, x, y);
				if (x != y) {
					trans.push_back(make_pair(j, make_pair(x, y)));
				}
				break;
			}
		}
		printf("%lu\n", trans.size());
		for (int i = 0; i < (int)trans.size(); i++) printf("%d %d %d\n", trans[i].first, trans[i].second.first, trans[i].second.second);
	}
	return 0;
}

