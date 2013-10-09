#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int N = 0;
const int MAXN = 400010;

struct Node {
	Node *ch[2], *p; int size, leftA, value; long long sum;
	inline bool dir(void) {return this == p->ch[1];}
	inline void SetC(Node *x, bool dir) {
		ch[dir] = x; x->p = this;
	}
	inline void Update(void);
}Tnull, *null = &Tnull, *positive[MAXN], *negitive[MAXN], *root, POOL[MAXN], *data;

void Node::Update(void) {
	if (this == null) return;
	size = ch[0]->size + ch[1]->size + 1;
	sum = ch[0]->sum + ch[1]->sum + value;
	if (ch[0]->leftA != 0) leftA = ch[0]->leftA; else
	if (value > 0) leftA = value;
	else leftA = ch[1]->leftA;
}

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
		if (x->p->p == G) rotate(x);
		else {
			if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
			else {rotate(x); rotate(x);}
		}
	}
	x->Update();
}

inline Node* getMin(Node *x) {if (x == null) return null; while (x->ch[0] != null) x = x->ch[0];return x;}
inline Node* getMax(Node *x) {if (x == null) return null; while (x->ch[1] != null) x = x->ch[1];return x;}

inline void erase(Node *x) {
	splay(x, null);
	Node *L = getMax(x->ch[0]), *R = getMin(x->ch[1]);
	if (L == null) {
		root = root->ch[1]; root->p = null; 
		return;
	}
	if (R == null) {
		root = root->ch[0]; root->p = null;
		return;
	}
	splay(L, x); splay(R, x);
	root = L; L->SetC(R, 1); L->p = null;
	L->Update();
}

inline Node* insert(Node *&now, int leftSize, Node *father, int _v) {
	if (now == null) {
		Node *tmp = data++;
		tmp->p = father; tmp->ch[0] = tmp->ch[1] = null; tmp->sum = tmp->value = _v; if (tmp->value > 0) tmp->leftA = tmp->value; else tmp->leftA = 0; tmp->size = 1;
		now = tmp;
		return tmp;
	}
	Node *tmp;
	if (leftSize <= now->ch[0]->size) {
		tmp = insert(now->ch[0], leftSize, now, _v);
	} else {
		tmp = insert(now->ch[1], leftSize - now->ch[0]->size - 1, now, _v);
	}
	now->Update();
	return tmp;
}

int n; char ch[20];

set<int> stack; int top;

inline int getCur(void) {
	if (stack.empty()) return top++;
	else {
		int ret = *stack.begin();
		stack.erase(stack.begin());
		return ret;
	}
}

inline void remove(int now) {
	if (!positive[now]) return;
	N -= 2;
	stack.insert(now);
	erase(positive[now]);
	erase(negitive[now]);
	positive[now] = negitive[now] = 0;
}

inline long long Cal(int now) {
	if (!positive[now]) return 0;
	splay(positive[now], null);
	splay(negitive[now], positive[now]);
	return root->ch[1]->ch[0]->sum;
}

inline void insert(int p) {
	int now = getCur();
	positive[now] = insert(root, p, null, now); splay(positive[now], null);
	int next;
	int t = root->ch[1]->leftA;
	if (t == 0) next = root->size - 1; else {
		splay(negitive[t], null);
		next = root->ch[0]->size;
	}
	negitive[now] = insert(root, next, null, -now); splay(negitive[now], null);
}

void clear(void) {
	memset(positive, 0, sizeof positive);
	memset(negitive, 0, sizeof negitive);
	data = POOL;
	null->value = 0; null->size = null->leftA = null->sum = 0;
	root = null; 
	insert(root, 0, null, 0);
	insert(root, 1, null, 0);
	top = 1;
	stack.clear();
}

int main(void) {
	int kase = 0;
	while (scanf("%d", &n) == 1) {
		N = 0;
		clear(); printf("Case #%d:\n", ++kase);
		for (int i = 1, x; i <= n; i++) {
			//fprintf(stderr, "%d %d\n", kase, i);
			scanf("%s %d", ch, &x);
			if (strcmp(ch, "insert") == 0) {
				insert(x + 1);
				N += 2;
			}
			if (strcmp(ch, "query") == 0) {
				long long Ans = Cal(x);
				cout <<Ans<<endl;
			}
			if (strcmp(ch, "remove") == 0) {
				remove(x);
			}
			assert(N == root->size - 2);
		}
	}
	return 0;
}
