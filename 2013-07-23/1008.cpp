#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100010;

vector<int> a[MAXN];

int n, q, d[MAXN]; int dis[MAXN];

inline int Bfs(int u) {
    int head = 1, tail = 1;  memset(dis, -1, sizeof dis);
    d[1] = u; dis[u] = 0;
    while (head <= tail) {
        int now = d[head++];
        for (vector<int>::iterator it = a[now].begin(); it != a[now].end(); ++it) if (dis[*it] == -1) {
            d[++tail] = *it;
            dis[*it] = dis[now] + 1;
        }
    }
    int MaxL = 0, c = 0;
    for (int i = 1; i <= n; i++) if (dis[i] > MaxL) MaxL = dis[i], c = i;
    return c;
}

int main(void) {
//    freopen("in" , "r", stdin);
    int kase; scanf("%d", &kase); while (kase--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) a[i].clear();
        for (int i = 1; i < n; i++) {
            int x, y; scanf("%d%d", &x, &y);
            a[x].push_back(y); a[y].push_back(x);
        }
        int u = Bfs(1);
        Bfs(u);
        int MaxL = 0;
        for (int i = 1; i <= n; i++) MaxL = max(MaxL, dis[i]); MaxL++;
        for (int i = 1; i <= q; i++) {
            int k; scanf("%d", &k);
            if (k <= MaxL) {
                printf("%d\n", k - 1);
            } else printf("%d\n", k * 2 - MaxL - 1);
        }
    }
    return 0;
}