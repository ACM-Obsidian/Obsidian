#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Node {
	Node *ch[2], *p; int size; long long value, sum;
	bool rev;
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Rev(void) {
		swap(ch[0], ch[1]); rev ^= 1;
	}
	inline void Push(void) {
		if (rev) {
			ch[0]->Rev();
			ch[1]->Rev();
			rev = 0;
		}
	}
	inline void Update(void) {
		size = ch[0]->size + ch[1]->size + 1;
		sum = ch[0]->sum + ch[1]->sum + value;
	}
}Tnull, *null = &Tnull, POOL[MAXN], *data = POOL;

class Spaly {public:
	Node *root;
	inline void rotate(Node *x) {
		Node *p = x->p; bool d = x->dir();
		p->Push(); x->Push();
		p->p->SetC(x, p->dir());
		p->SetC(x->ch[!d], d);
		x->SetC(p, !d);
		p->Update();
	}

	inline void splay(Node *x, Node *G) {
		if (G == null) root = x;
		while (x->p != G) {
			if (x->p->p == G) rotate(x); else {
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
				else {rotate(x); rotate(x);}
			}
		}
		x->Push();
		x->Update();
	}
	inline Node *Renew(long long value) {
		Node *ret = data++;
		ret->ch[0] = ret->ch[1] = ret->p = null;
		ret->size = 1; ret->sum = ret->value = value;
		ret->rev = 0;
		return ret;
	}

	inline Node* getKth(int k) {
		Node *tmp = root;
		while (true) {
			tmp->Push();
			if (tmp->ch[0]->size + 1 == k) return tmp;
			if (tmp->ch[0]->size >= k) tmp = tmp->ch[0]; else k -= tmp->ch[0]->size + 1, tmp = tmp->ch[1];
		}
	}

	inline Node* getInterval(int l, int r) {
		Node *L = getKth(l), *R = getKth(r + 2);
		splay(L, null); splay(R, L);
		return R->ch[0];
	}

	inline Node* Build(int l, int r, long long a[]) {
		if (l > r) return null;
		int mid = (l + r) >> 1;
		Node *ret = Renew(a[mid]);
		if (l == r) return ret;
		ret->SetC(Build(l, mid - 1, a), 0);
		ret->SetC(Build(mid + 1, r, a), 1);
		ret->Update();
		return ret;
	}
}T;

void clear(void) {
	data = POOL;
	T.root = null;
}

long long a[MAXN]; int n;

int main(void) {
	freopen("in", "r", stdin);
	clear();
	scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%lld", a+i), a[i] *= a[i];
	T.root = T.Build(0, n + 1, a);
	int q; scanf("%d", &q); while (q--) {
		int l, r; scanf("%d%d", &l, &r);
		Node *tmp = T.getInterval(l, r);
		long long A = (long long)(sqrt(tmp->sum) + 0.5);
		if (A * A < tmp->sum) A++;
		printf("%lld\n",A);
		if (l < r) {
			tmp = T.getInterval(l + 1, r);
			tmp->Rev();
		}
	}
	return 0;
}

