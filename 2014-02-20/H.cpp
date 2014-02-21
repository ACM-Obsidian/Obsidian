#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20010;
const int MAXM = MAXN;

char ch[555]; int n, k;

struct Edge {
	int y; Edge *next; int flag, num;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];
inline void AddEdge(int x, int y, int num = 0) {
	a[x] = new Edge(y, a[x]);
	a[y] = new Edge(x, a[y]);
	a[x]->flag = true; a[x]->num = num;
	a[y]->flag = false; a[y]->num = num;
}

long long pow[MAXM], sum[MAXM], base = 13331;
set<long long> L, R; map<long long, int> ML, MR;
pair<long long, long long> E[MAXN];
int nl, nr;

int cur, vis[MAXN], link[MAXN], hash[MAXM];;

bool Find(int u) {
	for (Edge *p = a[u]; p; p = p->next) if (vis[p->y] != cur && p->flag) {
		vis[p->y] = cur;
		if (!link[p->y] || Find(link[p->y])) {
			link[p->y] = u;
			return true;
		}
	}
	return false;
}

void Dfs(int u) {
	vis[u] =cur;
	for (Edge *p = a[u]; p; p = p->next) if (vis[p->y] != cur && p->flag) {
		vis[p->y] = cur;
		Dfs(p->y);
	}
}

vector<int> list[MAXM]; int top = 0, used[MAXM];

int main(void) {
	freopen("heavy.in", "r", stdin);
	freopen("heavy.out", "w", stdout);
	scanf("%d%d", &n, &k);
	pow[0] = 1; for (int i = 1; i < MAXM; i++) pow[i] = pow[i - 1] * base;
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch + 1);
		int len = strlen(ch + 1);
		for (int j = 1; j <= len; j++) sum[j] = sum[j - 1] * base + ch[j] - 'A' + 1;
		long long l = sum[k], r = sum[len] - sum[len - k] * pow[k];
		L.insert(l);
		R.insert(r);
		E[i] = make_pair(l, r);
	}
	for (set<long long>::iterator it = L.begin(); it != L.end(); it++) ML[*it] = ++nl; nr = nl;
	for (set<long long>::iterator it = R.begin(); it != R.end(); it++) MR[*it] = ++nr;
	for (int i = 1; i <= n; i++) AddEdge(ML[E[i].first], MR[E[i].second], i);

	int Ans = 0;
	for (int i = 1; i <= nl; i++) {
		++cur;
		Ans += Find(i);
	}
	for (int i = nl + 1; i <= nr; i++) hash[link[i]] = i;

	int vs = nl + nr + 1, vt = vs + 1;
	for (int i = 1; i <= nl; i++) {
		if (!hash[i]) {
			AddEdge(vs, i);
		} else {
			AddEdge(i, vs);
		}
	}
	for (int i = nl + 1; i <= nr; i++) {
		if (!link[i]) {
			AddEdge(i, vt);
		} else {
			AddEdge(vt, i);
		}
	}
	for (int i = 1; i <= nl; i++) {
		for (Edge *p = a[i]; p; p = p->next) if (p->y != vs && link[p->y] == i) {
			p->flag = 0;
		}
	}
	for (int i = nl + 1; i <= nr; i++) {
		for (Edge *p = a[i]; p; p = p->next) if (p->y != vt && hash[p->y] == i) {
			p->flag = 1;
		}
	}
	++cur;
	Dfs(vs);
	for (int i = 1; i <= nl; i++) if (vis[i] != cur) {
		++top;
		for (Edge *p = a[i]; p; p = p->next) if (p->y != vs && !used[p->num]) {
			list[top].push_back(p->num);
			used[p->num] = true;
		}
	}
	for (int i = nl + 1; i <= nr; i++) if (vis[i] == cur) {
		++top;
		for (Edge *p = a[i]; p; p = p->next) if (p->y != vt && !used[p->num]) {
			list[top].push_back(p->num);
			used[p->num] = true;
		}
	}
	printf("%d\n", Ans);
	for (int i = 1; i <= top; i++) {
		sort(list[i].begin(), list[i].end());
		printf("%lu ", list[i].size());
		for (int j = 0; j < (int)list[i].size(); j++) printf("%d%c", list[i][j], " \n"[j + 1 == (int)list[i].size()]);
	}
	return 0;
}

