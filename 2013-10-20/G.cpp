#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long Int64;

char ch[10];

struct Node {
	Node *ch[2], *p; int size;Int64 value;
	Int64 num, total, cur_num;
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Update(void) {
		size = ch[0]->size + ch[1]->size + 1;
		num = ch[0]->num + ch[1]->num + cur_num;
		total = ch[0]->total + ch[1]->total + cur_num * value;
	}
	inline void initInfo(Int64 _num) {
		num = cur_num = _num; total = num * value;
	}
};

const int MAXN = 100010;

class Splay {public:
	Node *root, Tnull, *null, *data, POOL[MAXN];
	Splay(){clear();}
	inline void clear(void) {
		data = POOL; root = null = &Tnull;
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
			if (x->p->p == G) rotate(x); else {
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
				else {rotate(x); rotate(x);}
			}
		}
		x->Update();
	}

	inline Node* Renew(Int64 value, Int64 _num) {
		Node *ret = data++;
		ret->ch[0] = ret->ch[1] =ret->p = null;
		ret->size = 1; ret->value = value;
		ret->initInfo(_num);
		return ret;
	}

	// 插入一个值为value的节点，初始要以Insert(root, null, value)来调用
	inline Node* Insert(Node *&now, Node* father, Int64 value, Int64 _num) {
		if (now == null) {
			now = Renew(value, _num); now->p = father;
			return now;
		}
		Node *ret;
		if (value <= now->value) ret = Insert(now->ch[0], now, value, _num);
		else ret = Insert(now->ch[1], now, value, _num);
		now->Update();
		return ret;
	}

	inline Node* find(int v) {
		Node *tmp = root;
		while (tmp != null) {
			if (tmp->value == v) return tmp;
			if (v < tmp->value) tmp = tmp->ch[0]; else tmp = tmp->ch[1];
		}
		return null;
	}

	inline pair<Int64, Int64> getKth(Int64 k) {
		Node *tmp = root; Int64 ret = 0;
		if (k == 0) return make_pair(0, 0);
		while (true) {
			if (tmp->ch[0]->num < k && tmp->ch[0]->num + tmp->cur_num >= k) {
				pair<Int64, Int64> t = make_pair(ret + tmp->ch[0]->total + (k - tmp->ch[0]->num) * tmp->value, tmp->value);
				splay(tmp, null);
				return t;
			}
			if (tmp->ch[0]->num >= k) tmp = tmp->ch[0]; 
			else k -= tmp->ch[0]->num + tmp->cur_num, ret += tmp->ch[0]->total + tmp->cur_num * tmp->value, tmp = tmp->ch[1];
		}
	}

	inline Node* getMin(Node *x) {Node *tmp = x; while (tmp->ch[0] != null) tmp = tmp->ch[0]; return tmp;}
	inline Node* getMax(Node *x) {Node *tmp = x; while (tmp->ch[1] != null) tmp = tmp->ch[1]; return tmp;}

	inline void erase(Node* x) {
		splay(x, null);
		if (x->ch[0] == null || x->ch[1] == null) {
			int d = x->ch[1] != null;
			root = x->ch[d]; root->p = null;
			return;
		}
		Node *L = getMax(x->ch[0]), *R = getMax(x->ch[1]);
		splay(L, x); splay(R, x);
		L->SetC(R, 1); L->p = null; root = L;
		L->Update();
	}
}T1, T2;

inline void Add(Splay& T, Int64 num, Int64 price) {
	Node* res = T.find(price);
	if (res == T.null) {
		res = T.Insert(T.root, T.null, price, num);
		T.splay(res, T.null);
	} else {
		T.splay(res, T.null);
		T.root->initInfo(T.root->cur_num + num);
		T.root->Update();
		if (T.root->cur_num == 0) T.erase(T.root);
	}
}

inline Int64 Cal(void) {
	Int64 l = 1, r = min(T1.root->num, T2.root->num);
	while (l <= r) {
		Int64 mid = (l + r) >> 1;
		pair<Int64, Int64> neg = T1.getKth(mid);
		pair<Int64, Int64> pos = T2.getKth(mid);
		if (neg.second < -pos.second) l = mid + 1; else r = mid - 1;
	}
	pair<Int64, Int64> neg = T1.getKth(r);
	pair<Int64, Int64> pos = T2.getKth(r);
	return -(neg.first + pos.first);
}

int main(void) {
//	freopen("in", "r", stdin);
	while (scanf("%s", ch) && strcmp(ch, "end")) {
		Int64 num, price; scanf(LL LL, &num, &price);
		if (strcmp(ch, "sell") == 0) {
			Add(T1, num, price);
		}
		if (strcmp(ch, "buy") == 0) {
			Add(T2, num, -price);
		}
		Int64 Ans = Cal();
		printf(LL "\n", Ans);
		fflush(stdout);
	}
	return 0;
}

