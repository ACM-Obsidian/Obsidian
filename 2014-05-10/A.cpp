#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 200010;
struct Circle {
	int x, y, r;
}a[MAXN];

struct Query {
	int type, id; long long tim;
}c[MAXN << 1];

long long now;

inline double getL(int id) {
	return a[id].y - sqrt((long long)a[id].r * a[id].r - ((long long)now - a[id].x) * ((long long)now - a[id].x));
}
inline double getR(int id) {
	return a[id].y + sqrt((long long)a[id].r * a[id].r - ((long long)now - a[id].x) * ((long long)now - a[id].x));
}

struct lPos {
	int id;
	inline friend bool operator <(const lPos& x, const lPos& y) {
		return getL(x.id) + 1e-12 < getL(y.id);
	}
};
struct rPos {
	int id;
	inline friend bool operator <(const rPos& x, const rPos& y) {
		return getR(x.id) + 1e-12 < getR(y.id);
	}
};

set<lPos> L; set<lPos>::iterator lfim[MAXN];
set<rPos> R; set<rPos>::iterator rfim[MAXN];

int kase, n;

inline bool cmp(const Query& x, const Query& y) {
	if (x.tim != y.tim) return x.tim < y.tim; else return x.type < y.type;
}

int cnt[MAXN], father[MAXN];
struct Edge {
	int y; Edge *next;
}*e[MAXN], POOL[MAXN], *data;

inline void AddEdge(int x, int y) {
	Edge *tmp = data++;
	tmp->y = y; tmp->next = e[x]; e[x] = tmp;
	father[y] = x;
}

inline void Dfs(int u, int deep) {
	cnt[deep]++;
	for (Edge *p = e[u]; p; p = p->next) Dfs(p->y, deep + 1);
}

inline void clear(void) {
	memset(e, 0, sizeof e);
	data = POOL;
	L.clear(); R.clear();
	memset(cnt, 0, sizeof cnt);
}

int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d", &kase); while (kase--) {
		clear();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].r);
			c[i * 2 - 1].type = 1;
			c[i * 2 - 1].tim = (long long)a[i].x - a[i].r;
			c[i * 2 - 1].id = i;
			c[i * 2].type = -1;
			c[i * 2].tim = (long long)a[i].x + a[i].r;
			c[i * 2].id = i;
		}
		sort(c + 1, c + n * 2 + 1, cmp); 
		for (int i = 1; i <= n * 2; i++) {
			lPos l; rPos r; l.id = r.id = c[i].id;
			now = c[i].tim;
			if (c[i].type == 1) {
				set<rPos>::iterator it = R.lower_bound(r);
				if (it == R.end()) AddEdge(0, c[i].id); else {
					int id = it->id;
					if (*lfim[id] < l) AddEdge(id, c[i].id); else {
						set<lPos>::iterator it = L.lower_bound(l);
						AddEdge(father[it->id], c[i].id);
					}
				}
				lfim[c[i].id] = L.insert(l).first;
				rfim[c[i].id] = R.insert(r).first;
			} else {
				L.erase(lfim[c[i].id]);
				R.erase(rfim[c[i].id]);
			}
		}
		Dfs(0, 0);
		for (int i = 1; ; i++) if (cnt[i]) printf("%d\n", cnt[i]); else break;
	}
	return 0;
}
