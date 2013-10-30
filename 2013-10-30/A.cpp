#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>
 
#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); it++)
using namespace std;
 
const int MAXN = 8;
 
int n = 6, m = 6, C;
 
int dx[2][4] = {{0, 0}, {1, -1}}, dy[2][4] = {{1, -1}, {0, 0}};
struct Pice {
    bool type; int x, y, Len;
    void Scan(void) {
        char c;
        scanf("%d %d %d %c\n", &y, &x, &Len, &c); y++, x++;
        if (c == 'H') type = 0; else type = 1;
    }
};

set<long long> S;

struct Board {
    int a[MAXN][MAXN];
    vector<Pice> T;
	inline void operator =(const Board &oth) {
		T = oth.T;
		memcpy(a, oth.a, sizeof a);
	}
    void Init(void) {
        for (int i = 1; i <= 6; i++)
            for (int j = 1; j <= 6; j++) a[i][j] = 1;
        foreach(it, T) Color(*it, 0);
    }
    inline void Color(const Pice& it, int d) {
        for (int k = 0; k < it.Len; k++) {
            a[it.x + dx[it.type][0] * k][it.y + dy[it.type][0] * k] = d;
        }
    }
	unsigned long long Hash(void) {
		unsigned long long ret = 0;
		foreach(it, T) {
			unsigned long long tmp = it->x * 13 + it->y;
			ret = ret * 13331 + tmp;
		}
		return ret;
	}
}now;
 
int TargetX;
 
inline bool check(const Board& now) {
    int x = now.T[0].x, y = now.T[0].y; y+= now.T[0].Len;
    if (x != TargetX) return false;
    for (int i = 6; i >= y; i--) if (!now.a[x][i]) {
        return false;
    }
    return true;
}
 
inline bool Move(Pice& it, Board& now, int dir, int k) {
    int &x = it.x, &y = it.y, nx = x, ny = y;
    if (dir == 0) {
        if (it.type == 0) ny += it.Len - 1;
        else nx += it.Len - 1;
    }
    for (int i = 1; i <= k; i++) {
        nx += dx[it.type][dir];
        ny += dy[it.type][dir];
        if (!now.a[nx][ny]) return false;
    }
    now.Color(it, 1);
    x += k * dx[it.type][dir], y += k * dy[it.type][dir];
    now.Color(it, 0);
    return true;
}
 
typedef vector<pair<int, int> > VPP;

queue<pair<Board, VPP> > Q;

inline void Bfs(void) {
	Q.push(make_pair(now, VPP())); 
	int h = now.Hash(); S.insert(h);
	while (!Q.empty()) {
		Board cur = Q.front().first; VPP path = Q.front().second; Q.pop();
		if (check(cur)) {
			printf("%d\n", path.size() + 1);
			for (int i = 0; i < path.size(); i++) printf("%d %d\n", path[i].first, path[i].second);
			puts("0");
			break;
		}
		foreach(it, cur.T) {
			for (int i = 0; i < 2; i++) {
				int d = 1;
				while (Move(*it, cur, i, d)) {
					path.push_back(make_pair(it - cur.T.begin() + 1, d * (1 - i * 2)));
					int H = cur.Hash();
					if (S.find(H) == S.end()) {
						Q.push(make_pair(cur, path));
						S.insert(H);
					}
					Move(*it, cur, i ^ 1, d);
					d++;
					path.pop_back();
				}
			}
		}
	}
}

int main(void) {
    freopen("afridge.in", "r", stdin);
    freopen("afridge.out", "w", stdout);
    scanf("%d\n", &C);
    now.T.resize(C);
    foreach(it, now.T) it->Scan();
    now.Init();
    TargetX = now.T[0].x;
	Bfs();
    return 0;
}

