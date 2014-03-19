#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 500020;
const int inf = 1000000001;

struct Node {
	Node *ch[2], *p; int size, value, Min;
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	void Update();
} Tnull, *null = &Tnull, *data, POOL[MAXN];

inline void Node::Update(void) {
	if (this == null) return;
	size = ch[0]->size + ch[1]->size + 1;
	Min = min(ch[0]->Min, ch[1]->Min); 
	Min = min(Min, value);
}

class Splay { public:
	Node *root;
	inline void rotate(Node *x) {
		Node *p = x->p; bool d = x->dir();
		p->p->SetC(x, p->dir());
		p->SetC(x->ch[!d], d);
		x->SetC(p, !d);
		p->Update();
	}
	inline void splay(Node *x, Node *G) {
		if (G == null) root = x;
		while (x->p != G) {
			if (x->p->p == G) rotate(x); else {
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);} else {rotate(x); rotate(x);}
			}
		}
		x->Update();
	}
	inline Node* Renew(int value) {
		Node *ret = data++;
		ret->ch[0] = ret->ch[1] = ret->p = null;
		ret->size = 1; ret->Min = ret->value =value;
		return ret;
	}

	inline Node* getKth(int k) {
		Node *tmp = root;
		while (true) {
			if (tmp->ch[0]->size + 1 == k) return tmp;
			if (tmp->ch[0]->size >= k) tmp = tmp->ch[0];
			else k -= tmp->ch[0]->size + 1, tmp = tmp->ch[1];
		}
	}

	inline Node* getInterval(int l, int r) {
		Node *L = getKth(l), *R = getKth(r + 2);
		splay(L, null); splay(R, L);
		return R->ch[0];
	}

	inline void insertInterval(int l, Node *x) {
		Node *L = getKth(l + 1), *R = getKth(l + 2);
		splay(L, null); splay(R, L);
		R->SetC(x, 0);
		R->Update(); L->Update();
	}
}T;

void clear(void) {
	data = POOL;
	T.root = null;
}

int n; char ch[3];
int main(void) {
	freopen("rmq.in", "r", stdin);
	scanf("%d", &n);
	clear(); null->value = null->Min = inf;
	T.root = data++; T.root->size = 2; T.root->ch[0] = data++; T.root->ch[1] = null; T.root->Min = inf; T.root->value = inf;
	T.root->ch[0]->ch[0] = null; T.root->ch[0]->ch[1] = null; T.root->ch[0]->size = 1; T.root->ch[0]->Min = T.root->ch[0]->value = inf;
	T.root->p = null; T.root->ch[0]->p = T.root;
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch);
		if (ch[0] == '+') {
			int pos, x; scanf("%d%d", &pos, &x);
			Node *tmp = T.Renew(x);
			T.insertInterval(pos, tmp);
		} else {
			int l, r; scanf("%d%d", &l, &r);
			printf("%d\n", T.getInterval(l, r)->Min);
		}
	}
	return 0;
}

