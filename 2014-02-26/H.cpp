#include <map>
#include <vector>
#include <set>
#include <cstdio>
#include <algorithm>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

const int MAXN = 500010;
const int inf = 1000000000;

pair<int, int> a[MAXN];
int n; set<int> SX, SY; map<int, int> MX, MY; int Lx, Ly, N;

vector<int> Y[MAXN]; pair<int, int> X[MAXN];

struct Node {
	int x, type, pos;
}c[MAXN]; int top = 0;

inline bool cmp(const Node& x, const Node& y) {
	if (x.x != y.x) return x.x < y.x; else return x.type < y.type;
}

int C[MAXN];
inline void Insert(int x, int d) {
	for (;x <= N; x += x & -x) C[x] += d;
}
inline int Cal(int x) {
	int ret = 0; for (;x; x -= x & -x) ret += C[x]; return ret;
}
inline int Sum(int l, int r) {
	if (l > r) return 0;
	return Cal(r) - Cal(l - 1);
}

int main(void) {
	freopen("inner.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].first, &a[i].second), SX.insert(a[i].first), SY.insert(a[i].second);
	foreach(it, SX) MX[*it] = ++Lx; 
	foreach(it, SY) MY[*it] = ++Ly; N = max(Lx, Ly);
	for (int i = 1; i <= n; i++) X[i].first = inf;
	for (int i = 1; i <= n; i++) {
		int x = MX[a[i].first], y = MY[a[i].second];
		X[x].first = min(X[x].first, y);
		X[x].second = max(X[x].second, y);
		Y[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) {
		if (Y[i].size() >= 2u) {
			sort(Y[i].begin(), Y[i].end());
			c[++top].type = 0;
			c[top].x = i;
		}
		if (X[i].first < X[i].second) {
			c[++top].type = -1;
			c[top].x = X[i].first;
			c[top].pos = i;
			c[++top].type = 1;
			c[top].x = X[i].second;
			c[top].pos = i;
		}
	}
	long long Ans = 0;
	sort(c + 1, c + top + 1, cmp);
	for (int i = 1; i <= top; i++) {
		if (c[i].type) Insert(c[i].pos, -c[i].type);
		else {
			for (int j = 0; j < (int)Y[c[i].x].size() - 1; j++) {
				Ans += (long long)Sum(Y[c[i].x][j] + 1, Y[c[i].x][j + 1] - 1);
			}
		}
	}
	printf("%I64d\n", Ans + n);
	return 0;
}

