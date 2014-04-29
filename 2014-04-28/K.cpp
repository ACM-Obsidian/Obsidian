#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Node {
	Node *ch[2]; int l, r; int sum;
}*root[MAXN], POOL[3000000], *data = POOL;

Node* Build(int L, int R) {
	Node *tmp = data++;
	tmp->l = L, tmp->r = R; tmp->sum = 0;
	if (L == R) return tmp;
	int mid = (L + R) >> 1;
	tmp->ch[0] = Build(L, mid);
	tmp->ch[1] = Build(mid + 1, R);
	return tmp;
}

Node* Insert(Node *now, int h, int x) {
	Node *ret = data++; *ret = *now;
	if (ret->l == ret->r) {
		ret->sum += x;
		return ret;
	}
	int d = h > ((now->l + now->r) >> 1);
	ret->ch[!d] = now->ch[!d];
	ret->ch[d] = Insert(now->ch[d], h, x);
	ret->sum = ret->ch[0]->sum + ret->ch[1]->sum;
	return ret;
}

int Cal(Node *L, Node *R, int S) {
	if (L->l == L->r) return L->l;
	int Lsum = R->ch[0]->sum - L->ch[0]->sum;
	if (Lsum >= S) {
		return Cal(L->ch[0], R->ch[0], S);
	} else {
		return Cal(L->ch[1], R->ch[1], S - Lsum);
	}
}

struct Edge {
	int y; Edge *next;
}*a[MAXN], POOL_edge[MAXN], *pos = POOL_edge;

int n, c[MAXN]; int deep[MAXN], list[MAXN]; pair<int, int> interval[MAXN]; int tim;

void Dfs(int u) {
	list[++tim] = u; interval[u].first = tim;
	for (Edge *p = a[u]; p; p = p->next) deep[p->y] = deep[u] + 1, Dfs(p->y);
	interval[u].second = tim;
}

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i);
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		Edge *tmp = pos++;
		tmp->y = i; tmp->next = a[x]; a[x] = tmp;
	}
	deep[1] = 1; Dfs(1);
	root[0] = Build(1, n);
	for (int i = 1; i <= n; i++) root[i] = Insert(root[i - 1], deep[list[i]], c[list[i]]);
	int m; scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int x, S; scanf("%d%d", &x, &S);
		int L = interval[x].first, R = interval[x].second;
		if (root[R]->sum - root[L - 1]->sum < S) puts("-1"); else {
			printf("%d\n", Cal(root[L - 1], root[R], S) - deep[x]);
		}
		fflush(stdout);
	}
	return 0;
}

