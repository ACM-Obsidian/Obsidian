#include <cstdio>
#include <map>
#include <set>
#include <algorithm>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

const int MAXN = 100010;

set<int> S; map<int, int> M; int fim[MAXN];

int n, m, a[MAXN], L;

struct Node {
	Node *ch[2]; int size, l, r;
}*root[MAXN], POOL[MAXN * 30], *data = POOL;

Node *Build(int l, int r) {
	Node *ret = data++;
	ret->l = l, ret->r = r, ret->size = 0;
	if (l == r) return ret;
	int mid = (l + r) >> 1;
	ret->ch[0] = Build(l, mid);
	ret->ch[1] = Build(mid + 1, r);
	return ret;
}

Node *Insert(Node* now, int h) {
	Node *ret = data++; *ret = *now; ret->size++;
	if (now->l == now->r) return ret;
	int mid = (now->l + now->r) >> 1;
	int d = (h > mid);
	ret->ch[d] = Insert(ret->ch[d], h);
	return ret;
}

int Cal(Node *L, Node *R, int k) {
	if (L->l == L->r) return L->l;
	if (k <= R->ch[0]->size - L->ch[0]->size) {
		return Cal(L->ch[0], R->ch[0], k);
	} else {
		return Cal(L->ch[1], R->ch[1], k - (R->ch[0]->size - L->ch[0]->size));
	}
}

int main(void) {
	freopen("kth.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), S.insert(a[i]);
	foreach(it, S) M[*it] = ++L;
	root[0] = Build(1, L);
	for (int i = 1; i <= n; i++) {
		int t = M[a[i]];
		fim[t] = a[i]; a[i] = t;
		root[i] = Insert(root[i - 1], t);
	}
	for (int i = 1; i <= m; i++) {
		int l, r, k; scanf("%d%d%d", &l, &r, &k);
		int x = Cal(root[l - 1], root[r], k);
		printf("%d\n", fim[x]);
	}
	return 0;
}

