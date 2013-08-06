#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define cl(a) memset(a,0,sizeof a);
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	const int MAXN = 120; int inf;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, m, a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], ok[MAXN][MAXN];double Ans[MAXN][MAXN];

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			memset(a, 50, sizeof a); inf = a[0][0]; memset(ok, 0, sizeof ok);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) Ans[i][j] = inf;
			for (int i = 1; i <= m; i++) {
				int x = ScanInt(), y = ScanInt(), z = ScanInt();
				a[x][y] = z;
				Ans[x][y] = min(Ans[x][y], (double)z);
			}
			memcpy(b, a, sizeof a);
			for (int l = 2; l <= n; l++) {
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++) {
						int tmp = inf;
						for (int k = 1; k <= n; k++) if (a[i][k] != inf && b[k][j] != inf) tmp = min(tmp, a[i][k] + b[k][j]);
						c[i][j] = tmp;
						if (tmp != inf) Ans[i][j] = min(Ans[i][j], (double) tmp / l);
					}
				memcpy(a, c, sizeof a);
			}
			rep(i,n) rep(j,n) if (Ans[i][j] != inf) ok[i][j] = true;
			rep(i,n) rep(j,n) {
				rep(k,n) if (ok[i][k] && ok[k][j] && Ans[k][k] < Ans[i][j]) Ans[i][j] = Ans[k][k];
			}
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j < n; j++) {
					if (!ok[i][j]) printf("NO "); else printf("%.3f ", Ans[i][j]);
				}
				if (!ok[i][n]) printf("NO\n"); else printf("%.3f\n", Ans[i][n]);
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
