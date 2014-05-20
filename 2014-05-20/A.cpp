#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN= 1000010;

int n, next[MAXN], hash[MAXN];
int a[MAXN], Ans[MAXN], L;

struct Node {
	Node *ch[2]; int l, r, value;
}*root, POOL[4000010], *data = POOL;

Node *Build(int l, int r) {
	Node *ret = data++;
	ret->l = l, ret->r = r; ret->value = ~0u>>1;
	if (l == r) return ret;
	int mid = (l + r) >> 1;
	ret->ch[0] = Build(l, mid);
	ret->ch[1] = Build(mid + 1, r);
	return ret;
}

void insert(Node *now, int h, int x) {
	if (now->l == now->r) {
		now->value = min(now->value, x);
		return;
	}
	int d = (h > (now->l + now->r) / 2);
	insert(now->ch[d], h, x);
	now->value = min(now->ch[0]->value, now->ch[1]->value);
}

int Cal(Node *now, int L, int R) {
	if (L > R) return ~0u>>1;
	if (L <= now->l && now->r <= R) return now->value;
	int mid = (now->l + now->r) >> 1;
	return min(Cal(now->ch[0], L, min(R, mid)), Cal(now->ch[1], max(mid + 1, L), R));
}

vector<pair<int, int> > list[MAXN];

int main(void) {
	// freopen("in", "r", stdin); 
	memset(a, 0x3f, sizeof a);
	scanf("%d", &n); root = Build(1, n + 1);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), L = max(L, i);
	int m; scanf("%d", &m);
	for (int i = 1, l, r; i <= m; i++) {
		scanf("%d%d", &l, &r);
		list[l].push_back(make_pair(r, i));
	}
	for (int i = 0; i < MAXN; i++) hash[i] = n + 1;
	for (int i = n; i >= 1; i--) next[i] = hash[a[i]], hash[a[i]] = i;
	for (int i = L + 1; i >= 0; i--) insert(root, hash[i], i);
	for (int i = 1; i <= n; i++) {
		for (vector<pair<int, int> >::iterator it = list[i].begin(); it != list[i].end(); ++it) {
			int tmp = Cal(root, it->first + 1, n + 1);
			Ans[it->second] = tmp;
		}
	//	printf("%d\n", inv(next[i]), a[i]);
		insert(root, next[i], a[i]);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
	return 0;
}

