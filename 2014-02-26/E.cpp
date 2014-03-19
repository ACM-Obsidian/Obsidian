#include <cstdio>
#include <set>
#include <vector>
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
	Splay() {
		root = data++; root->size = 2; root->ch[0] = data++; root->ch[1] = null; root->Min = inf; root->value = inf;
		root->ch[0]->ch[0] = null; root->ch[0]->ch[1] = null; root->ch[0]->size = 1; root->ch[0]->Min = root->ch[0]->value = inf;
		root->p = null; root->ch[0]->p = root;
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

	inline void eraseInterval(int l, int r) {
		getInterval(l, r);
		root->ch[1]->ch[0] = null;
		root->ch[1]->Update();
		root->Update();
	}

	inline void merge(Splay *oth) {
		Node *tmp = oth->root; while (tmp->ch[0] != null) tmp = tmp->ch[0];
		oth->splay(tmp, null);
		tmp = tmp->ch[1]; tmp->p = null;
		oth->root = tmp;
		while (tmp->ch[1] != null) tmp = tmp->ch[1];
		oth->splay(tmp, null);
		tmp = tmp->ch[0]; tmp->p = null;
		oth->root = tmp;
		insertInterval(root->size - 2, tmp);
	}
};

void clear(void) {
	data = POOL;
}

std::set<std::pair<int, Splay*> > a;

void dfs(Node *x, std::vector<int> &res) {
	if (x == null) return;
	dfs(x->ch[0], res);
	if (x->value != inf) res.push_back(x->value);
	dfs(x->ch[1], res);
}

int main() {
	freopen("key.in", "r", stdin);
	clear(); null->value = null->Min = inf;
	Splay dummy, *t;
	int n, m; scanf("%d%d", &n, &m);
	std::set<std::pair<int, Splay*> >::iterator it, it2;
	for (int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		it = a.upper_bound(std::pair<int, Splay*>(x, &dummy));
		if (it != a.end() && it->first == x) it++;
		if (it != a.begin() && (it--, x < it->first + it->second->root->size-2))
			it->second->insertInterval(x - it->first, it->second->Renew(i+1));
		else {
			t = new Splay();
			t->insertInterval(0, t->Renew(i+1));
			it = a.insert(std::pair<int, Splay*>(x, t)).first;
		}
		if (it != a.begin() && (it2 = it, it2--, it2->first + it2->second->root->size-2 == it->first)) {
			it2->second->merge(it->second);
			a.erase(it);
			it = it2;
		}
		if (it != --a.end() && (it2 = it, it2++, it->first + it->second->root->size-2 == it2->first)) {
			it->second->merge(it2->second);
			a.erase(it2);
		}
	}
	std::vector<int> res;
	int last = 1;
	for (it = a.begin(); it != a.end(); it++) {
		for (int i = last; i < it->first; i++) res.push_back(0);
		dfs(it->second->root, res);
		last = it->first + it->second->root->size-2;
	}
	printf("%d\n", (int)res.size());
	for (int i = 0; i < res.size(); i++) printf("%d%c", res[i], " \n"[i == res.size()-1]);
	return 0;
}
