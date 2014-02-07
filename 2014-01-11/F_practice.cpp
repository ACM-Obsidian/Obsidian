#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <set>

using namespace std;

#pragma GCC optimize("O3")

const int MAXN = 100010;

struct Node {
	int l, r; Node *ch[2]; int m;
	void Insert(int h, int x) {
		if (l == r) {
			m = max(m, x); 
			return;
		}
		int mid = (l + r) >> 1;
		ch[h > mid]->Insert(h, x);
		m = max(ch[0]->m, ch[1]->m);
	}
	int Cal(int L, int R) {
		if (L > R) return 0;
		if (L <= l && r <= R) return m;
		int mid = (l + r) >> 1;
		return max(ch[0]->Cal(L, min(R, mid)), ch[1]->Cal(max(mid + 1, L), R));
	}
}*root, POOL[200010], *data = POOL;

Node *Build(int l, int r) {
	Node *ret = data++;
	ret->l = l, ret->r = r, ret->m = 0;
	if (l == r) return ret;
	int mid = (l + r) >> 1;
	ret->ch[0] = Build(l, mid);
	ret->ch[1] = Build(mid + 1, r);
	return ret;
}

const double eps = 1e-9; long long _ = ((1ll << 11) - 1) << 52;
const double inf = *(double*)&_;

inline int sgn(double x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}

struct Line {
	double a, b, c;
	int w, top;
	inline void Set(long long t, long long x, long long y) {
		w = x; top = y;
		long long A = (x * x - t * t) - 2 * x * (x - t);
		a = 1.0 * y / A;
		b = -2.0 * x * y / A;
		c = -(t * t * a + t * b);
	}
	inline double getVal(double x) const {return a * x * x + b * x + c;}
}a[MAXN];

struct Query {
	int l, r, tl, tr;
}c[MAXN];

struct Sweep {
	int type; // 0 for intersection, 1 for queries.
	double w;int x, y;
	int id;
	inline bool operator <(const Sweep& oth) const {
		int t = sgn(w - oth.w);
		if (t != 0) return t == -1; else return type < oth.type;
	}
}stack[MAXN]; int top;

double Ans[MAXN];

int n, m, Q, L;

inline void Insert(double w, int i, int j) {
	stack[++top].type = 0;
	stack[top].w = w;
	stack[top].x = i;
	stack[top].y = j;
}

inline void Intersect(const Line &x, const Line &y, int i, int j) {
	double A = x.a - y.a, B = x.b - y.b, C = x.c - y.c;
	if (sgn(A) == 0) {
		if (sgn(B) != 0) Insert(-C / B, i, j);
		return;
	}
	double delta = B * B - 4 * A * C;
	if (sgn(delta) < 0) return;
	if (i == 8981 && j == 9020) {
		puts("OK!");
	}
	if (sgn(delta) == 0) {
		Insert(-B / (2 * A), i, j);
		return;
	}
	Insert((-B + sqrt(delta)) / (2 * A), i, j);
	Insert((-B - sqrt(delta)) / (2 * A), i, j);
}

double NOW;

struct Para {
	double a, b, c; int id;
	Para(double a, double b, double c, int id):a(a), b(b), c(c), id(id){}
	inline double getVal(const double x) const {return a * x * x + b * x + c;}
	inline bool operator <(const Para& oth) const {
		if (NOW == inf || NOW == -inf) return a < oth.a;
		return getVal(NOW) < oth.getVal(NOW);
	}
};

multiset<Para> S; multiset<Para>::iterator fim[MAXN];
set<int> T;

inline void Process(int l, int r) {
	top = 0;
	for (int i = l; i <= r; i++) {
		for (int j = i + 1; j <= r; j++) {
			Intersect(a[i], a[j], i, j);
		}
	}
	for (int i = 1; i <= m; i++) {
		if (c[i].tl <= l && c[i].tr >= r) {
			stack[++top].type = 1, stack[top].id = i, stack[top].w = c[i].l;
			stack[++top].type = 1, stack[top].id = i, stack[top].w = c[i].r;
		}
	}
	stack[++top].type = 0; stack[top].w = inf;
	stack[++top].type = 0; stack[top].w = -inf;
	sort(stack + 1, stack + top + 1);
	assert(stack[1].w == -inf);
	assert(stack[top].w == inf);

	// Sweep
	NOW = -inf; S.clear();
	for (int i = l; i <= r; i++) fim[i] = S.insert(Para(a[i].a, a[i].b, a[i].c, i));
	int next = 1;
	for (int i = 2; i < top;) {
		while (sgn(stack[next].w - stack[i].w) < 1) next++;
		T.clear();
		for (int j = i; j < next; j++) if (stack[j].type == 0) {
			T.insert(stack[j].x);
			T.insert(stack[j].y);
		}
		for (set<int>::iterator it = T.begin(); it != T.end(); ++it)
			S.erase(fim[*it]);
		NOW = (stack[i].w + stack[next].w) / 2.0;
		for (set<int>::iterator it = T.begin(); it != T.end(); ++it)
			fim[*it] = S.insert(Para(a[*it].a, a[*it].b, a[*it].c, *it));

		fim[0] = S.end(); fim[0]--; double tmp = fim[0]->getVal(stack[i].w);
		for (int j = i; j < next; j++) if (stack[j].type == 1) {
			Ans[stack[j].id] = max(Ans[stack[j].id], tmp);
		}
		i = next;
	}

	// Segmetn Tree
	data = POOL; root = Build(0, L);
	for (int i = l; i <= r; i++) root->Insert(a[i].w, a[i].top);
	for (int i = 1; i <= m; i++) if (c[i].tl <= l && c[i]. tr >= r) {
		double tmp = root->Cal(c[i].l, c[i].r);
		Ans[i] = max(Ans[i], tmp);
	}
}

inline double getInter(const Line& now, int l, int r) {
	if (now.w >= l && now.w <= r) return now.top;
	return max(now.getVal(l), now.getVal(r));
}

inline int ScanInt(void) {
	int c, r = 0; 
	while (!isdigit(c = getchar())); 
	r = c - 48;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return r;
}

int belong[MAXN];
int main(void) {
	freopen("flights.in", "r", stdin);
	freopen("flights.out", "w", stdout);
	scanf("%d", &n); Q = 50;
	for (int i = 1; i <= n; i++) {
		int t = ScanInt(), x = ScanInt(), y = ScanInt(); L = max(L, t);
		a[i].Set(t, x, y);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) c[i].tl = ScanInt(), c[i].tr = ScanInt(), c[i].l = ScanInt(), c[i].r = ScanInt(), L = max(L, c[i].r);
	for (int i = 1; i <= n; i += Q) {
		belong[i] = -1; belong[min(n, i + Q - 1)] = 1;
		Process(i, min(n, i + Q - 1));
	}
	for (int i = 1; i <= m; i++) {
		int l = c[i].tl, r = c[i].tr;
		while (belong[l] != -1 && l <= r) {
			double tmp = getInter(a[l], c[i].l, c[i].r);
			Ans[i] = max(Ans[i], tmp);
			l++;
		}
		while (belong[r] != 1 && r >= l) {
			double tmp = getInter(a[r], c[i].l, c[i].r);
			Ans[i] = max(Ans[i], tmp);
			r--;
		}
	}
	for (int i = 1; i <= m; i++) printf("%lf\n", Ans[i]);
	return 0;
}

