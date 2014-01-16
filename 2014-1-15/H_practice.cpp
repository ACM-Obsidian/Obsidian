#include <cstdio>
#include <vector>
#include <algorithm>

#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); ++it)
using namespace std;

const int MAXN = 1000100;
const int inf = ~0U>>1;

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a < b ? a : b;}

struct Node {
	int x1, y1, x2, y2, t;
	Node(int x1, int y1, int x2, int y2):x1(x1), y1(y1), x2(x2), y2(y2){}
};

struct List {
	int l, r;
	vector<Node> a;
	inline void push(Node oth, int _t) {
		l = min(l, _t);
		r = max(r, _t);
		oth.t = _t; a.push_back(oth);
	}
	inline void clear(void) {
		l = inf, r = -inf;
		a.clear();
	}
}X, Y, Z;

struct Point {
	int l, r, type;
	Point(int l, int r, int type):l(l), r(r), type(type){}
	inline bool operator <(const Point &oth) const {
		return l < oth.l;
	}
};

int n;

vector<Point> tmp;

inline int Check(List& A, List& B) {
	if (A.a.size() == 0 || B.a.size() == 0) return 1;
	foreach(it, A.a) 
		if (it->y2 < B.l || it->y1 > B.r) return 0;
	int l = -inf, r = inf;
	tmp.clear();
	foreach(it, B.a) {
		r = min(r, it->x2);
		l = max(l, it->x1);
		tmp.push_back(Point(it->y1, it->y2, 0));
	}
	if (r <= l + 1) return 0;
	// printf("%d %d\n", l, r);
	foreach(it, A.a) {
		if (it->t <= l || it->t >= r) return 0;
		tmp.push_back(Point(it->x1, it->x2, 1));
	}
	sort(tmp.begin(), tmp.end());
	int minR[2] = {inf, inf}, maxR[2] = {-inf, -inf};
	foreach(it, tmp) {
		if (it->r < maxR[!it->type]) return 0;
		if (it->l > minR[!it->type]) return 0;
		minR[it->type] = min(minR[it->type], it->r);
		maxR[it->type] = max(maxR[it->type], it->r);
	}
	return 1;
}

inline void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x1, y1, z1, x2, y2, z2;
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		if (z1 > z2) swap(z1, z2);
		if (x1 == x2) {
			X.push(Node(y1, z1, y2, z2), x1);
		}
		if (y1 == y2) {
			Y.push(Node(z1, x1, z2, x2), y1);
		}
		if (z1 == z2) {
			Z.push(Node(x1, y1, x2, y2), z1);
		}
	}
	int t = !!X.a.empty() + !!Y.a.empty() + !!Z.a.empty();
	if (t == 2) {puts("NO"); return;}
	int cnt1 = Check(X, Z);
	int cnt2 = Check(Z, Y);
	int cnt3 = Check(Y, X);
	puts(cnt1 + cnt2 + cnt3 > t + 1 ? "YES": "NO");
}

inline void clear(void) {
	X.clear(); Y.clear(); Z.clear();
}

int main(void) {
	int kase;
	for (scanf("%d", &kase); kase--; clear(), solve());
	return 0;
}

