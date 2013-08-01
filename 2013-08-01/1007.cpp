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

    inline int ScanInt(void) {
        int r = 0, c, d;
        while (!isdigit(c = getchar()) && c != '-');
        if (c != '-') r = c - '0'; d = c;
        while ( isdigit(c = getchar())) r = r * 10 + c - '0';
        return d=='-'?-r:r;
    }

    int n, pos[MAXN], L[MAXN], a[MAXN], m, R[MAXN], top;

    int A[MAXN], Ans[MAXN];

    inline int Cal(int u) {
        int ret = 0; for (;u;u-=u&-u) ret += A[u];
        return ret;
    }
    inline void Add(int u, int d) {
        for (;u<=n;u+=u&-u) A[u] += d;
    }

    struct Query {
        int l, r, type, c;
        inline friend bool operator <(const Query& x, const Query& y) {
            if (x.r != y.r) return x.r < y.r; else return x.type < y.type;
        }
    }stack[MAXN << 2];

    inline void Add(int x, int y, int c, int id = 0) {
        if (x > y) return;
        Query &tmp = stack[++top];
        if (c != 0) {
            tmp.l = x, tmp.r = y, tmp.type = 1, tmp.c = -c;
            Add(x, c);
        } else {
            tmp.l = x, tmp.r = y, tmp.type = 0, tmp.c = id;
        }
    }

    inline void Process(void) {
        sort(stack + 1, stack + top + 1);
        for (int i = 1; i <= top; i++) {
            if (stack[i].type == 0) {
            //    printf("%d\n", stack[i].l);
                int tmp = Cal(stack[i].l);
                Ans[stack[i].c] = tmp;
                if (tmp != stack[i].r - stack[i].l + 1) Ans[stack[i].c]++;
            } else {
                //printf("Add %d for %d\n", stack[i].l, stack[i].c);
                Add(stack[i].l, stack[i].c);
            }
        }
    }

    inline void solve(void) {
        int kase; scanf("%d", &kase); while (kase--) {
            top = 0; memset(A, 0, sizeof A); memset(pos, 0, sizeof pos); memset(L, 0, sizeof L); memset(R, 0, sizeof R); memset(Ans, 0, sizeof Ans);
            n = ScanInt(), m = ScanInt();
            for (int i = 1; i <= n; i++) {
                int x = ScanInt(); pos[x] = i; a[i] = x;
            }
            for (int i = 1; i <= n; i++) L[i] = pos[a[i] - 1], R[i] = pos[a[i] + 1];
            for (int i = 1; i <= n; i++) {
                int l = L[i], r = R[i]; if (l > r) swap(l, r);
                if (l > i) {
                    Add(1, l - 1, 1);
                    Add(1, i - 1, -1);
                    Add(i + 1, l - 1, -1);
                } else
                if (r < i) {
                    Add(r + 1, n, 1);
                    Add(i + 1, n, -1);
                    Add(r + 1, i - 1, -1);
                } else {
                    Add(l + 1, r - 1, 1);
                    Add(l + 1, i - 1, -1);
                    Add(i + 1, r - 1, -1);
                }
            }
            for (int i = 1; i <= m; i++) {
                int x = ScanInt(), y = ScanInt();
                Add(x, y, 0, i);
            }
            Process();
            for (int i = 1; i <= m; i++) {
                printf("%d\n", Ans[i]);
            }
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
