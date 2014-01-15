#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAXN = 30010;

struct Node {
	Node *ch[2], *p; int size, value;
	bool rev;
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Rev(void) {
		swap(ch[0], ch[1]); rev ^= 1;
	}
	// null永远不会push
	inline void Push(void) { 
		if (rev) {
			ch[0]->Rev();
			ch[1]->Rev();
			rev = 0;
		}
	}
	// null永远不会update
	inline void Update(void) { 
		size = ch[0]->size + ch[1]->size + 1;
	}
	inline void initInfo(void) {
		rev = 0;
	}
}Tnull, *null = &Tnull, *data, POOL[MAXN];

Node *fim[MAXN];

class Splay {public:
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

	inline Node* Renew(int value) {
		Node *ret = data++;
		ret->ch[0] = ret->ch[1] =ret->p = null;
		ret->size = 1; ret->value = value;
		ret->initInfo();
		return ret;
	}

	inline Node* getMin(Node *x) {Node *tmp = x; while (tmp->ch[0] != null) tmp = tmp->ch[0]; return tmp;}
	inline Node* getMax(Node *x) {Node *tmp = x; while (tmp->ch[1] != null) tmp = tmp->ch[1]; return tmp;}

	// 查询第k大
	inline Node* getKth(int k) {
		Node *tmp = root; 
		assert(k > 0 && k <= root->size);
		while (true) {
			tmp->Push();
			if (tmp->ch[0]->size + 1 == k) return tmp;
			if (tmp->ch[0]->size >= k) tmp = tmp->ch[0]; 
			else k -= tmp->ch[0]->size + 1, tmp = tmp->ch[1];
		}
	}

	// 以下为splay维护序列, 初始要在原序列中放入一个-inf和inf来防止边界条件

	// 得到原数列中[l,r]区间对应的结点，如果l == r + 1则表示是一个空区间
	inline Node* getInterval(int l, int r) {
		assert(l <= r + 1);
		Node *L = getKth(l), *R = getKth(r + 2);
		splay(L, null); splay(R, L);
		return R->ch[0];
	}

	// 删除一段区间[l,r]
	inline void eraseInterval(int l, int r) {
		getInterval(l, r);
		root->ch[1]->ch[0] = null;
		root->ch[1]->Update();
		root->Update();
	}

	// 在位置l的后面插入一段区间x (0 <= l <= n)
	inline void insertInterval(int l, Node *x) {
		Node *L = getKth(l + 1), *R = getKth(l + 2);
		splay(L, null); splay(R, L);
		R->SetC(x, 0);
		R->Update(); L->Update();
	}

	// 把数列a的[l,r]构建为一个splay
	inline Node* Build(int l, int r, int a[]) {
		if (l > r) return null;
		int mid = (l + r) >> 1;
		Node *ret = Renew(a[mid]); fim[a[mid]] = ret;
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

pair<int, int> Ans[1000000]; int top;
int n, a[MAXN];

int main(void) {
	int kase; scanf("%d", &kase); while (kase--) {
		clear();
		scanf("%d", &n); top = 0;
		for (int i = 1; i <= n; i++) scanf("%d", a + i); a[n + 1] = n + 1;
		T.root = T.Build(0, n + 1, a);
		for (int i = 1; i <= n; i++) {
			T.splay(fim[i], null);
			int k = T.root->ch[0]->size;
			while (k != i) {
				int l = i + ((k - i + 1) & 1), r = k;
				Ans[++top] = make_pair(l, r);
				int mid = (l + r) >> 1;
				Node *tmp = T.getInterval(l, mid);
				T.eraseInterval(l, mid);
				T.insertInterval(mid, tmp);
				k = mid;
			}
		}
		printf("%d\n", top);
		for (int i = 1; i <= top; i++) printf("%d %d\n", Ans[i].first, Ans[i].second);
	}
	return 0;
}

