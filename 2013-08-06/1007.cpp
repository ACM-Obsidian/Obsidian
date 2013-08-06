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

	const int MAXN = 222;

	int n, a[MAXN], b[MAXN];
	double p[MAXN], f[MAXN];

	inline double Cal(double a, double b, double p) {
		return (1 - p) * a + p * b;
	}

	inline void solve(void) {
		int kase = 0;
		while (scanf("%d", &n) == 1) {
			printf("Case %d:\n", ++kase); n++;
			for (int i = 1; i <= n; i++) scanf("%d", a + i);
			for (int j = 2; j <= n; j++) {
				char ch[3]; scanf("%s", ch);
				if (ch[0] == '&') b[j] = 1;
				if (ch[0] == '|') b[j] = 2;
				if (ch[0] == '^') b[j] = 3;
			}
			for (int j = 2; j <= n; j++) scanf("%lf", p + j);
			double Ans = 0;
			for (int k = 0; k <= 20; k++) {
				f[1] = (a[1] >> k) & 1;
				for (int i = 2; i <= n; i++) {
					int t = (a[i] >> k) & 1;
					if (b[i] == 1) {
						if (t == 0) f[i] = Cal(0, f[i - 1], p[i]);
						else f[i] = Cal(f[i - 1], f[i - 1], p[i]);
					}
					if (b[i] == 2) {
						if (t == 0) f[i] = Cal(f[i - 1], f[i - 1], p[i]);
						else f[i] = Cal(1, f[i - 1], p[i]);
					}
					if (b[i] == 3) {
						if (t == 0) f[i] = Cal(f[i - 1], f[i - 1], p[i]);
						else f[i] = Cal(1 - f[i - 1], f[i - 1], p[i]);
					}
				}
				Ans += f[n] * (1 << k);
			}
			printf("%.6f\n", Ans);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		//freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
