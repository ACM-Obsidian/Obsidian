#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

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

	const int MAXN = 200010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, m, a[MAXN], pos[MAXN];

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			memset(pos, -1, sizeof pos); pos[0] = 0;
			for (int i = 1; i <= n; i++) {
				a[i] = ScanInt() % m; if (a[i] < 0) a[i] += m;
				a[i] = (a[i - 1] + a[i]) % m;
			}
			int Ans = 0;
			for (int i = 1; i <= n; i++) {
				if (pos[a[i]] != -1) {
					Ans = max(Ans, i - pos[a[i]]);
				} else pos[a[i]] = i;
			}
			printf("%d\n", Ans);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
