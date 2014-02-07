#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 200010;
const long long inf = 100000000000000ll;

struct Edge {
    int y; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data;

inline void AddEdge(int x, int y) {
    Edge *tmp = data++; tmp->next = a[x]; tmp->y = y; a[x] = tmp;
    tmp = data++; tmp->next = a[y]; tmp->y = x; a[y] = tmp;
}

long long c[MAXN]; int n, t;

typedef multiset<pair<long long, long long> > MII;

MII P[MAXN], *pos;
MII *s[MAXN];

inline void Merge(MII *&A, MII *&B) {
    if (A->size() < B->size()) swap(A, B);
    for (MII::iterator it = B->begin(); it != B->end(); it++) {
        A->insert(*it);
    }
	B->clear();
}

void Dfs(int u, int f) {
    MII *now = pos++; now->clear();
    for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
        Dfs(p->y, u);
        Merge(now, s[p->y]);
    }
    pair<long long, long long> tmp; 
    if (c[u] < 0) tmp = make_pair(-c[u], 0); else tmp = make_pair(0, c[u]);
    while (!now->empty() && (now->begin()->first <= tmp.first || tmp.first >= tmp.second)) {
		if (now->begin()->first > tmp.second) {
            tmp.first += now->begin()->first - tmp.second;
            tmp.second = now->begin()->second;
        } else tmp.second += -now->begin()->first + now->begin()->second;
        now->erase(now->begin());
    }
    if (tmp.first < tmp.second) now->insert(tmp);
    s[u] = now;
}

inline void solve(void) {
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++) scanf(LL, c + i);
    for (int i = 1; i <  n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        AddEdge(x, y);
    }
    c[++n] = inf; AddEdge(n, t);
    Dfs(1, 0);
    long long hp = 0, M = 0;
    for (MII::iterator it = s[1]->begin(); it != s[1]->end(); ++it) {
        if (hp >= it->first) hp += it->second - it->first; else break;
        M = max(hp, M);
    }
    puts(M > inf / 10 ? "escaped" : "trapped");
}

inline void clear(void) {
    data = POOL; pos = P;
    memset(a, 0, sizeof a);
}

int main(void) {
    int kase;
    for (scanf("%d", &kase); kase--; clear(), solve());
    return 0;
}
