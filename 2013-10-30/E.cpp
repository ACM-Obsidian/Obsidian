#include <cstdio>
#include <cassert>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>

#pragma GCC optimize("O2")
using namespace std;

const int MAXN = 2012;

vector<pair<int, int> > Ans;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Processer {
	int n, m, x[MAXN], y[MAXN << 1], lower[MAXN][MAXN << 1], upper[MAXN][MAXN << 1], f[MAXN][MAXN << 1];short path[MAXN][MAXN << 1];

	inline void Init(int a[], int b[], int _n, int _m) {
		n = _n; m = _m;
		memcpy(x, a, sizeof (int) * n);
		memcpy(y, b, sizeof (int) * m); 
		memcpy(y + m, b, sizeof(int) * m);
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= m * 2; j++) {
				lower[i][j] = 0;
				upper[i][j] = n;
			}
	}
	
	inline bool ok(int now, int left, int right, int i, int j) {
		return ((j >= now && j <= now + m) && (i >= lower[right][j] && i <= upper[left][j]));
	}

	inline int dp(int now, int left, int right) {
		//assert(lower[right][now] == 0);
		//assert(upper[left][now + m] == n);
		for (int j = now; j <= now + m; j++) {
			for (int i = lower[right][j]; i <= upper[left][j]; i++) {
				f[i][j] = 1000000;
				path[i][j] = -1;
				if (ok(now, left, right, i - 1, j) && f[i - 1][j] + 1 <= f[i][j]) {
					f[i][j] = f[i - 1][j] + 1;
					path[i][j] = 0;
				}
				if (ok(now, left, right, i, j - 1) && f[i][j - 1] + 1 <= f[i][j]) {
					f[i][j] = f[i][j - 1] + 1;
					path[i][j] = 1;
				}
				if (ok(now, left, right, i - 1, j - 1) && f[i - 1][j - 1] + (x[i - 1] != y[j - 1]) <= f[i][j]) {
					f[i][j] = f[i - 1][j - 1] + (x[i - 1] != y[j - 1]);
					path[i][j] = 2;
				}
				if (f[i][j] == 1000000) {
					if (i == 0 && j == now) f[i][j] = 0;
					else if (i > 0) f[i][j] = i;
					else f[i][j] = j - now;
				}
			}
		}
		for (int i = now; i <= now + m; i++) lower[now][i] = n, upper[now][i] = 0;
		int i = n;
		int j = now + m;
		lower[now][j] = upper[now][j] = i;
		while (path[i][j] != -1) {
			if (path[i][j] == 0) i--; else
			if (path[i][j] == 1) j--; else
			if (path[i][j] == 2) i--, j--;
			lower[now][j] = min(lower[now][j], i);
			upper[now][j] = max(upper[now][j], i);
		}
		return f[n][now + m];
	}

	inline void solve(int l, int r) {
		if (l + 1 >= r) return;
		int mid = (l + r) >> 1;
		int A = dp(mid, l, r);
		Ans.push_back(make_pair(mid, A));
		solve(l, mid);
		solve(mid, r);
	}

	inline void solve(void) {
		int A1 = dp(0, 0, 0);
		int A2 = dp(m, m, m);
		Ans.push_back(make_pair(0, A1));
		//assert(A1 == A2);
		solve(0, m);
	}
}worker;

char s1[MAXN], s2[MAXN];

int n, a[MAXN], b[MAXN], m;

int main(void) {
	freopen("edit.in", "r", stdin);
	freopen("edit.out", "w", stdout);
	scanf("%s%s", s1, s2);
	n = strlen(s1), m = strlen(s2);
	for (int i = 0; i < n; i++) a[i] = s1[i] - 33 + 1;
	for (int i = 0; i < m; i++) b[i] = s2[i] - 33 + 1;
///	if (n >= m) {
		worker.Init(a, b, n, m);
//	} else {
//		worker.Init(b, a, m, n);
//	}
	worker.solve();
	sort(Ans.begin(), Ans.end());
//	printf("%d\n", Ans[Ans.size() - 1].second);
	for (int i = 0; i < (int)Ans.size(); i++) printf("%d\n", Ans[i].second);
	return 0;
}

