#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 500010;

struct Node {
	Node *ch[2], *p; int size, value, id; Node *w;
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
		if (ch[0]->w->value > ch[1]->w->value) w = ch[0]->w; else w = ch[1]->w;
		if (value > w->value) w = this;
	}
}Tnull, *null = &Tnull, *fim[MAXN], POOL[MAXN], *data = POOL;

Node* Renew(int _value) {
	Node *ret = data++;ret->ch[0] = ret->ch[1] = ret->p = null; ret->rev = 0; ret->value = _value; ret->size = 1; ret->w = ret;return ret;
}

inline bool isRoot(Node *x) {return x->p == null || (x != x->p->ch[0] && x != x->p->ch[1]);}

inline void rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	p->Push(); x->Push();
	if (!isRoot(p)) p->p->SetC(x, p->dir()); else x->p = p->p;
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
	p->Update();
}

inline void splay(Node *x) {
	x->Push();
	while (!isRoot(x)) {
		if (isRoot(x->p)) rotate(x);
		else {
			if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
			else {rotate(x); rotate(x);}
		}
	}
	x->Update();
}

inline Node* Access(Node *x) {
	Node *t = x, *q = null;
	for (; x != null; x = x->p) {
		splay(x); x->ch[1] = q; q = x;
	}
	splay(t);
	return q;
}

inline void Evert(Node *x) {
	Access(x); x->Rev();
}

inline void link(Node *x, Node *y) {
	Evert(x); x->p = y;
}

inline Node* getRoot(Node *x) {
	Node *tmp = x;
	Access(x);
	while (tmp->Push(), tmp->ch[0] != null) tmp = tmp->ch[0];
	splay(tmp);
	return tmp;
}

inline void cut(Node *x, Node *y) {
	Access(x); splay(y);
	if (y->p != x) swap(x, y);
	Access(x); splay(y);
	y->p = null;
}

inline Node* getPath(Node *x, Node *y) {
	Evert(x); Access(y);
	return y;
}

inline void clear(void) {
	null->rev = 0; null->size = 0; null->value = -1; null->w = null;
}

int n, m;
pair<int, int> E[MAXN];

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d%d", &n, &m); clear();
	for (int i = 1; i <= n; i++) fim[i] = Renew(0);
	long long Ans = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		E[i].first = x, E[i].second = y;
		fim[i + n] = Renew(z); 
		fim[i + n]->id = i;
		Node *l1 = getRoot(fim[x]);
		Node *l2 = getRoot(fim[y]);
		if (l1 != l2) {
			link(fim[x], fim[i + n]);
			link(fim[y], fim[i + n]);
			Ans += z;
		} else {
			Node *tmp = getPath(fim[x], fim[y]);
			if (tmp->w->value > z) {
				Ans -= tmp->w->value;
				Ans += z;
				Node *backup = tmp->w;
				cut(backup, fim[E[backup->id].first]);
				cut(backup, fim[E[backup->id].second]);
				link(fim[x], fim[i + n]);
				link(fim[y], fim[i + n]);
			}
		}
		printf("%lld\n", Ans);
	}
	return 0;
}

