#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100010, mod = 1000000007;

struct Node {
	Node *ch[2]; int l, r; long long A[2], AB, d[2];
	inline void Update(void) {
		A[0] = (ch[0]->A[0] + ch[1]->A[0]) % mod;
		A[1] = (ch[0]->A[1] + ch[1]->A[1]) % mod;
		AB = (ch[0]->AB + ch[1]->AB) % mod;
	}
	inline void Add(long long x, int dir) {
		d[dir] = (d[dir] + x) % mod;
		A[dir] = (A[dir] + x * (r - l + 1)) % mod;
		AB = (AB + x * A[dir ^ 1]) % mod;
	}
	inline void Push(void) {
		for (int i = 0; i < 2; i++) {
			if (d[i]) {
				ch[0]->Add(d[i], i);
				ch[1]->Add(d[i], i);
				d[i] = 0;
			}
		}
	}
}*root, POOL[MAXN * 4], *data = POOL;

inline Node* Build(int L, int R) {
	Node *ret = data++;
	ret->l = L, ret->r = R; ret->A[0] = ret->A[1] = ret->AB = ret->d[0] = ret->d[1] = 0;
	if (L == R) return ret;
	int mid = (L + R) >> 1;
	ret->ch[0] = Build(L, mid);
	ret->ch[1] = Build(mid + 1, R);
	return ret;
}

inline void Add(Node *now, int L, int R, int dir, long long x) {
	if (L > R) return;
	if (L <= now->l && now->r <= R) {
		now->Add(x, dir);
		return;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	Add(now->ch[0], L, min(mid, R), dir, x);
	Add(now->ch[1], max(mid + 1, L), R, dir, x);
	now->Update();
}

inline long long Cal(Node *now, int L, int R) {
	if (L > R) return 0;
	if (L <= now->l && now->r <= R) {
		return now->AB;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	long long A1 = Cal(now->ch[0], L, min(mid, R));
	long long A2 = Cal(now->ch[1], max(mid + 1, L), R);
	return (A1 + A2) % mod;
}

int n, m;

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	root = Build(1, n);
	for (int i = 1; i <= m; i++) {
		char ch[3]; scanf("%s", ch);
		if (ch[0] == '*') {
			int l, r, x; scanf("%d%d%d", &l, &r, &x);
			Add(root, l, r, 0, x);
		} else
		if (ch[0] == '.') {
			int l, r, x; scanf("%d%d%d", &l, &r, &x);
			Add(root, l, r, 1, x);
		} else {
			int l, r; scanf("%d%d", &l, &r);
			printf("%lld\n", Cal(root, l, r));
		}
	}
	return 0;
}

