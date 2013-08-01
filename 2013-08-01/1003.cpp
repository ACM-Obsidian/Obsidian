//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <functional>
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
#include <queue>

#define mp make_pair
#define pb push_back
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

    const int MAXN = 210;
    const int MAXS = 130;
    const int inf = ~0U>>1;

    int dx[] = {1,0,-1,0}, dy[] = {0,1,0,-1};

    struct State {
        int x, y, S, step;
        State(){}
        State(int x, int y, int S, int step):x(x), y(y), S(S), step(step){}
        inline friend bool operator <(const State& x, const State& y) {return x.step > y.step;}
    };

    int step[MAXN][MAXN][MAXS], n, m, a[MAXN][MAXN], cntK;
    char ch[MAXN];

    priority_queue<State> Q;

    inline bool turn(int x) {return x <= 13 && x >= 10;}
    inline int isKey(int x, int S) {
        if (x >= 20 && !(S & (1 << (x - 20)))) {
            return x - 20;
        } else return -1;
    }

    inline void Renew(int x, int y, int S, int cnt) {
        if (step[x][y][S] == -1 || step[x][y][S] > cnt) {
            step[x][y][S] = cnt;
            Q.push(State(x, y, S, cnt));
        }
    }

    inline bool Swipe(int x, int y, int S, int dir, int step) {
        while (true) {
            int nx = x + dx[dir], ny = y + dy[dir];
            if (a[nx][ny] == -1) break;
            if (a[nx][ny] == 0) {
                Renew(x, y, S, step);
                break;
            } 
            if (turn(a[nx][ny])) {
                Renew(nx, ny, S, step);
                break;
            }
            if (a[nx][ny]==3 && S == (1 <<cntK) - 1) {
                Renew(nx, ny, S, step);
                break;
            }
            int t = 0;;
            if ((t = isKey(a[nx][ny], S)) >= 0) {
                S |= 1<<t;
            }
            x = nx, y = ny;
        }
        return false;
    }

    inline void cl(void) {
        memset(a, -1, sizeof a); memset(step, -1, sizeof step);
        cntK = 0;
    }

    inline void solve(void) {
        while (scanf("%d%d", &n, &m) == 2) {
            cl();
            State begin; begin.step = begin.S = 0;
            for (int i = 1; i <= n; i++) {
                scanf("%s", ch + 1);
                for (int j = 1; j <= m; j++) {
                    if (ch[j] == '#') a[i][j] = 0;
                    if (ch[j] == '.') a[i][j] = 1;
                    if (ch[j] == 'S') a[i][j] = 1, begin.x = i, begin.y = j;
                    if (ch[j] == 'K') a[i][j] = 20 + (cntK++);
                    if (ch[j] == 'E') a[i][j] = 3;
                    if (ch[j] == 'L') a[i][j] = 13;
                    if (ch[j] == 'U') a[i][j] = 12;
                    if (ch[j] == 'D') a[i][j] = 10;
                    if (ch[j] == 'R') a[i][j] = 11;
                }
            }
            while (!Q.empty()) Q.pop(); Q.push(begin); step[begin.x][begin.y][begin.S] = 0;
            bool ok = false;
            while (!Q.empty()) {
                State now = Q.top(); int t = step[now.x][now.y][now.S]; Q.pop();
                if (a[now.x][now.y] == 3 && now.S == (1<<cntK) - 1) {
                    printf("%d\n", now.step);
                    ok = true;
                    break;
                }
                ok = 0;
                if (turn(a[now.x][now.y])) {
                    int dir = a[now.x][now.y] - 10;
                    Swipe(now.x, now.y, now.S, dir, t);
                } else {
                    for (int i = 0; i < 4 && !ok; i++) {
                        Swipe(now.x, now.y, now.S, i, t + 1);
                    }
                }
            }
            if (!ok) puts("-1");
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
