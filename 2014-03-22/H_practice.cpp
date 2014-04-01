#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 200010;
const long long inf = 10000000000000000ll;

long long fim[MAXN];

struct Node {
	Node *ch[2]; int l, r; long long d;pair<long long, int> Min;
	void Update(void) {Min = min(ch[0]->Min, ch[1]->Min);}
	void Push(void) {
		if (d) {
			ch[0]->Set(d);
			ch[1]->Set(d);
			d = 0;
		}
	}
	void Set(long long u) {
		d += u, Min.first += u;
	}
}*root, POOL[MAXN << 2], *data = POOL;

inline Node* Build(int l, int r) {
	Node *ret = data++;
	ret->l = l, ret->r = r; ret->d = 0;
	if (l == r) { ret->Min = make_pair(fim[l], l); return ret; }
	int mid = (l + r) >> 1;
	ret->ch[0] = Build(l, mid);
	ret->ch[1] = Build(mid + 1, r);
	ret->Update();
	return ret;
}

inline void Add(Node *now, int L, int R, int t) {
	if (L > R) return;
	if (L <= now->l && now->r <= R) {
		now->Set(t);
		return;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	Add(now->ch[0], L, min(mid, R), t);
	Add(now->ch[1], max(mid + 1, L), R, t);
	now->Update();
}

inline pair<long long, int> Cal(Node *now, int L, int R) {
	if (L > R) return make_pair(inf, 0);
	if (L <= now->l && now->r <= R) {
		return now->Min;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	return min(Cal(now->ch[0], L, min(mid, R)), Cal(now->ch[1], max(L, mid + 1), R));
}

map<int, int> M; set<int> S;multiset<int> right;
vector<int> list;

struct Pair {
	int l, r, val;
}a[MAXN];

int n, L;

struct Query {
	int pos, id, type;
}c[MAXN];

inline bool cmp(const Query& x, const Query& y) {
	if (x.pos != y.pos) return x.pos < y.pos;
	else return x.type < y.type;
}

long long sum, Ans = inf;
int w1, w2;

inline void make(int k) {
	multiset<int>::iterator it = right.upper_bound(k);
	if (it == right.end()) return;
	int next = *it + 1;
	pair<long long, int> ret = Cal(root, next, L);
	if (ret.first < inf) {
		if (Ans > sum + ret.first) {
			Ans = sum + ret.first;
			w1 = k;
			w2 = ret.second;
		}
	}
}

inline bool in(int x, int l, int r) {return x >= l && x <= r;}

int main(void) {
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].val), S.insert(a[i].l), S.insert(a[i].r);
	for (set<int>::iterator it = S.begin(); it != S.end(); ++it) fim[M[*it] = ++L] = inf;
	for (int i = 1; i <= n; i++) {
		fim[ a[i].l = M[a[i].l] ] = 0, a[i].r = M[a[i].r];
		c[i * 2 - 1].pos = a[i].l, c[i * 2 - 1].id = i;
		c[i * 2].pos = a[i].r, c[i * 2].type = 1, c[i * 2].id = i;
		right.insert(a[i].r);
	}
	root = Build(1, L);
	for (int i = 1; i <= n; i++) Add(root, a[i].l + 1, a[i].r, a[i].val);
	sort(c + 1, c + n * 2 + 1, cmp);
	for (int i = 1; i <= n * 2; ) {
		if (c[i].type == 0) {
			sum += a[c[i].id].val;
			Add(root, a[c[i].id].l + 1, a[c[i].id].r, -a[c[i].id].val);
			__typeof(right.begin()) it = right.find(a[c[i].id].r);
			right.erase(it);
			i++;
		} else {
			int j = i;
			while (j <= n * 2 && c[j].pos == c[i].pos) sum -= a[c[j++].id].val;
			make(c[i].pos);
			i = j;
		}
	}
	if (Ans < inf) {
		printf(LL "\n", Ans);
		for (int i = 1; i <= n; i++) if ((in(w1, a[i].l, a[i].r) || in(w2, a[i].l, a[i].r)) && !(a[i].r == w1 || a[i].l == w2)) list.push_back(i);
		printf("%lu\n", list.size());
		for (int i = 0; i < (int)list.size(); i++) printf("%d%c", list[i], " \n"[i == (int)list.size() - 1]);
	} else {
		printf("-1\n");
	}
	return 0;
}

