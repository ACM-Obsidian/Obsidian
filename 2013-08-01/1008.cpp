//#define FILEIO

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

    const int MAXN = 100010;

    char ch[MAXN]; int f[MAXN];

    inline void solve(void) {
        int t = 0;
        int kase; scanf("%d", &kase); while (kase--) {
            t++;
            scanf("%s", ch + 1); int n = strlen(ch + 1);
            f[0] = 1;
            for (int i = 1; i <= n; i++) {
                f[i] = 0;
                f[i] = (f[i] + f[i - 1]) % 10007;
                if (i >= 4 && ch[i] == 'e' && ch[i - 1] == 'h' && ch[i - 2] == 'e' && ch[i - 3] == 'h') {
                    f[i] = (f[i] + f[i - 4]) % 10007;
                }
            }
            printf("Case %d: %d\n", t, f[n]);
        }
    }
}

int main(void) {
    #ifdef FILEIO
        freopen(INPUT, "r", stdin);
//        freopen(OUTPUT, "w", stdout);
    #endif
    Solve::solve();
    return 0;
}
