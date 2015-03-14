#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int inf = 1000000000;

int vs, vt;
int c[10][10];
int id[10][10];

struct Edge {
	int y, f, c; Edge *next, *opt; int dir;
}POOL[100000], *data, *a[MAXN], *e[MAXN];

inline void AddEdge(Edge **a, int x, int y, int f, int c) {
	Edge *tmp = data++;
	tmp->y = y; tmp->f = f; tmp->c = c; tmp->next = a[x]; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->f = 0; tmp->c = -c; tmp->next = a[y]; a[y] = tmp;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
	a[x]->dir = 1; a[y]->dir = -1;
}

char ch[MAXN];
const int bias[] = {32, 0}; 
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

inline int get(int x, int y) {return id[x][y];}

inline pair<int, int> get_coo(int id) {
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) if (get(i, j) == id) {
			return make_pair(i, j);
		}
	assert(false);
	return make_pair(0, 0);
}

void Makegraph(Edge **a) {
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) if (c[i][j]) {
			AddEdge(a, vs, get(i, j), 1, 0);
		}
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) {
			for (int k = 0; k < 8; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if (nx >= 1 && nx <= 8 && ny >= 1 && ny <= 8) {
					AddEdge(a, get(i, j), get(nx, ny), inf, 1);
				}
			}
		}
}

int d[MAXN], vis[MAXN], dis[MAXN]; Edge *path[MAXN];
inline pair<int, int> Spfa(Edge **a) {
    int Flow = 0, Cost = 0;
    while (true) {
        memset(vis, 0, sizeof vis);
        memset(dis, 0x7f, sizeof dis);
        memset(path, 0, sizeof path);
        int head = 1, tail = 1, sum = 1; d[1] = vs; vis[vs] = true; dis[vs] = 0;
        while (sum) {
            int now = d[head++]; if (head == MAXN) head = 1; sum--;
            for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
                dis[p->y] = dis[now] + p->c;
                path[p->y] = p;
                if (!vis[p->y]) {
                    ++tail; if (tail == MAXN) tail = 1; sum++;
                    d[tail] = p->y;
                    vis[p->y] = true;
                }
            }
            vis[now] = false;
        }
        if (dis[vt] == dis[0]) return make_pair(Flow, Cost);
        int tmp = vt, Min = ~0U>>1;
        while (path[tmp]) {
            Min = min(Min, path[tmp]->f);
            tmp = path[tmp]->opt->y;
        }
        Flow += Min;
        tmp = vt;
        while (path[tmp]) {
            path[tmp]->f -= Min;
            path[tmp]->opt->f += Min;
            Cost += Min * path[tmp]->c;
            tmp = path[tmp]->opt->y;
        }
    }
    return make_pair(Flow, Cost);
}

vector<int> steps[MAXN];
int cur;

bool Dfs(int u, Edge **a) {
	if (u == vt) return true;
	if (u != vs) steps[cur].push_back(u);
	vis[u] = 1;
	for (Edge *p = a[u]; p; p = p->next) if (p->dir == 1 && !vis[p->y] && p->opt->f > 0) {
		p->opt->f -= 1; p->f += 1;
		if (Dfs(p->y, a)) return true;
		p->opt->f += 1; p->f =- 1;
	}
	return false;
}

vector<pair<int, int> > buf[10][10];

void output(pair<int, int> a, pair<int, int> b) {
	printf("%c%d-%c%d\n",  'a' - 1 + a.second, -a.first + 9, 'a' - 1 + b.second,- b.first + 9) ;
}

void jump(pair<int, int> a, pair<int, int> b) {
	if (c[b.first][b.second]) {
		buf[b.first][b.second].push_back(a);
		return;
	} else {
		output(a, b);
		c[b.first][b.second] = 1;
		c[a.first][a.second] = 0;
		if (buf[a.first][a.second].size()) {
			pair<int, int> tmp = buf[a.first][a.second].back();
			buf[a.first][a.second].pop_back();
			jump(tmp, a);
		}
	}
}

// 1..32 -> sum is odd (e.g. 1 + 1) 33..64 -> (1, 2)
int main(void) {
	freopen("knights.in", "r", stdin);
	freopen("knights.out", "w", stdout);
	int cnt[2] = {0, 0};
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) id[i][j] = ++cnt[(i + j) & 1] + bias[(i + j) & 1];
	vs = 32 + 32 + 1, vt = vs + 1;

	/*
	for (int i = 1; i <= 8; i++, puts("") )
			for (int j = 1; j <= 8; j++) printf("%d ", id[i][j]); */
	while (scanf("%s", ch + 1) == 1) {
		cur = 0;
		memset(a, 0, sizeof a);
		memset(e, 0, sizeof e);
		memset(c, 0, sizeof c);
		data = POOL;
		for (int j = 1; j <= 8; j++) if (ch[j] == 'N') c[1][j] = 1;
		for (int i = 2; i <= 8; i++) {
			scanf("%s", ch + 1);
			for (int j = 1; j <= 8; j++) if (ch[j] == 'N') c[i][j] = 1;
		}
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				buf[i][j].clear();
			}

		for (int i = 1; i <= 32; i++) AddEdge(a, i, vt, 1, 0);
		for (int i = 33; i <= 64; i++) AddEdge(e, i, vt, 1, 0);
		Makegraph(a);
		Makegraph(e);
		pair<int, int> Ans1 = Spfa(a);
		pair<int, int> Ans2 = Spfa(e);
		Edge **w = Ans1.second < Ans2.second ? a : e;
		printf("%d\n", min(Ans1.second, Ans2.second));

		while (true) {
			cur++; memset(vis, 0, sizeof vis);
			steps[cur].clear();
			if (!Dfs(vs, w)) {cur--; break;}
		}

		/*
		for (int i = 1; i<= cur; i++, puts("")) {
			for (int j = 0; j < steps[i].size(); ++j) printf("%d ", steps[i][j]);
		}
		*/

		for (int i = 1; i <= cur; i++) if (steps[i].size() > 1) {
			vector<pair<pair<int, int>, pair<int, int> > > Ans;
			for (int j = 0; j <= (int)steps[i].size() - 2; j++) {
				pair<int, int> now = get_coo(steps[i][j]);
				pair<int, int> next = get_coo(steps[i][j + 1]);
				jump(now, next);
			}
		}
		puts("");
/*		for (int i = 1; i <= 8; i++, puts(""))
			for (int j = 1; j <= 8; j++) printf("%d ", c[i][j]); */
	}
	return 0;
}

