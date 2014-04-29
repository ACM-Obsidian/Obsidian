#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 100;

struct Node {
	Node *ch[26], *fail, *go[26]; int mask;
}*root, POOL[MAXN], *data = POOL;

inline Node* Trans(Node* now, int k) {
	if (now->go[k]) return now->go[k];
	Node *ret = now;
	while (ret != root && !ret->ch[k]) ret = ret->fail;
	if (ret->ch[k]) ret = ret->ch[k];
	return now->go[k] = ret;
}

int n, m;

Node *d[MAXN];

struct Path {
	int i, j, k, next;
	Path(int i, int j, int k, int next):i(i), j(j), k(k), next(next){}
	Path(){}
}g[16][MAXN][1110], final;

int f[16][MAXN][1110];

int Ans = 0; char ch[MAXN];

int main(void) {
	freopen("jeerman.in", "r", stdin);
	freopen("jeerman.out", "w", stdout);
	scanf("%d%d", &n, &m);
	root = data++;
	for (int i = 1; i <= m; i++) {
		char ch[20];
		scanf("%s", ch);
		int len = strlen(ch); Node *tmp = root;
		for (int j = 0; j < len; j++) {
			if (!tmp->ch[ch[j] - 'a']) tmp->ch[ch[j] - 'a'] = data++;
			tmp = tmp->ch[ch[j] - 'a'];
		}
		tmp->mask |= 1 << (i - 1);
	}
	int head = 1, tail = 1; d[1] = root;
	while (head <= tail) {
		Node* now = d[head++];
		for (int i = 0; i < 26; i++) if (now->ch[i]) {
			d[++tail] = now->ch[i];
			if (now == root) {
				now->ch[i]->fail = root;
				continue;
			}
			Node *tmp = now->fail;
			while (tmp != root && !tmp->ch[i]) tmp = tmp->fail;
			if (tmp->ch[i] && now != root) tmp = tmp->ch[i];
			now->ch[i]->fail = tmp;
		}
	}
	for (Node *p = POOL + 1; p != data; p++) {
		Node *now = p; int &tmp = p->mask;
		while (now != root) tmp |= now->mask, now = now->fail;
	}
	f[0][0][0] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (data - POOL); j++)
			for (int k = 0; k < (1 << m); k++) if (f[i][j][k]) {
				for (int next = 0; next < 26; next++) {
					Node *nx = Trans(POOL + j, next);
					f[i + 1][nx - POOL][k | nx->mask] = 1;
					g[i + 1][nx - POOL][k | nx->mask] = Path(i, j, k, next);
					if (i + 1 == n && __builtin_popcount(k | nx->mask) > Ans) {
						Ans = __builtin_popcount(k | nx->mask);
						final = Path(i + 1, (int)(nx - POOL), k | nx->mask, next);
					}
				}
			}
	if (Ans == 0) {
		for (int i = 1; i <= n; i++) putchar('x'); puts("");
	} else {
		for (int i = n - 1; i >= 0; i--) {
			final = g[final.i][final.j][final.k];
			ch[i] = final.next + 'a';
		}
		puts(ch);
	}
	return 0;
}

