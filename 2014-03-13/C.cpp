#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300010, inf = 1000000000;

struct Node {
	Node *ch[2]; int l, r; int cover;
}POOL_[MAXN << 4], *pos = POOL_, *root;

Node *Build(int l, int r) {
	Node *tmp = pos++;
	tmp->l = l, tmp->r = r, tmp->cover = 0;
	if (l == r) return tmp;
	int mid = (l + r) >> 1;
	tmp->ch[0] = Build(l, mid);
	tmp->ch[1] = Build(mid + 1, r);
	return tmp;
}

void Add(Node *now, int L, int R, int t) {
	if (L > R) return;
	if (L <= now->l && now->r <= R) {
		now->cover = max(now->cover, t);
		return;
	}
	int mid = (now->l + now->r) >> 1;
	Add(now->ch[0], L, min(R, mid), t);
	Add(now->ch[1], max(L, mid + 1), R, t);
}

int Cal(Node *now, int h) {
	if (now->l == now->r) return now->cover;
	int mid = (now->l + now->r) >> 1;
	int d = (h > mid);
	return max(now->cover, Cal(now->ch[d], h));
}

struct Edge {
	int y; Edge *next;
}*a[MAXN], POOL[MAXN << 1], *data = POOL;

inline void AddEdge(int x, int y) {
	Edge* tmp = data++; tmp->y = y; tmp->next = a[x]; a[x] = tmp;
	tmp = data++; tmp->y = x; tmp->next = a[y]; a[y] = tmp;
}

int n, A, B;

int father[MAXN], fway[MAXN], d[MAXN], height[MAXN];
vector<int> tmp;

inline void Bfs(void) {
	int head = 1, tail = 1; d[1] = 1;
	while (head <= tail) {
		int now = d[head++];
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			d[++tail] = p->y;
			father[p->y] = now;
		}
	}
	for (int i = n; i >= 1; i--) height[father[d[i]]] = max(height[father[d[i]]], ++height[d[i]]);
	for (int i = 1; i <= n; i++) --height[i];
	root = Build(1, n);
	for (int i = 1; i <= n; i++) {
		int now = d[i];
		int m1 = -inf, w1 = 0, m2 = -inf, w2 = 0;
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			if (height[p->y] > m1) {
				m2 = m1, w2 = w1;
				m1 = height[p->y];
				w1 = p->y;
			} else if (height[p->y] > m2) {
				m2 = height[p->y];
				w2 = p->y;
			}
		}
		m1++, m2++;
		tmp.clear(); tmp.push_back(fway[now]);
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			fway[p->y] = max(fway[p->y], max(p->y == w1 ? m2 : m1, fway[now]) + 1);
			tmp.push_back(height[p->y] + 1);
		}
		sort(tmp.begin(), tmp.end());
		int last = 0, t = tmp.size();
		for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
			Add(root, last + 1, *it, t);
			last = *it; t--;
		}
	}
}

int main(void) {
	freopen("amoeba.in", "r", stdin);
	freopen("amoeba.out", "w", stdout);
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		AddEdge(x, y);
	}
	Bfs();
	for (int i = A; i <= B; i++) {
		printf("%d\n", Cal(root, i));
	}
	return 0;
}

