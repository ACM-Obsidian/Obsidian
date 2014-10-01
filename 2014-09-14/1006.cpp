#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int per[4][6] = {
    {4, 3, 1, 2, 5, 6},
    {3, 4, 2, 1, 5, 6},
    {6, 5, 3, 4, 1, 2},
    {5, 6, 3, 4, 2, 1}
};

inline int p_apply (int a, int p[]) {
    int rr[7], tt[7];
    for (int i = 6; i >= 1; i--) rr[i] = a % 10, a /= 10;
    for (int i = 0; i < 6; i++) tt[i + 1] = rr[p[i]];
    int ans = 0;
    for (int i = 1; i <= 6; i++) ans = ans * 10 + tt[i];
    return ans;
}
inline bool valid (int a) {
    int rr[7], tt[7];
    for (int i = 6; i >= 1; i--) rr[i] = a % 10, a /= 10;
    for (int i = 1; i <= 6; i++) {
        if (rr[i] > 6 || rr[i] < 1) return false;
        for (int j = 1; j < i; j++) if (rr[j] == rr[i]) return false;
    }
    return true;
}

int cha[654322][4];
int vv[1010], vm;

int dist[654322];
int que[1010], l, r;

int main () {
    vm = 0;
    for (int i = 123456; i <= 654321; i++) if (valid(i)) {
        vv[vm++] = i;
    }
    for (int i = 0; i < vm; i++)
        for (int j = 0; j < 4; j++) {
            cha[vv[i]][j] = p_apply(vv[i], per[j]);
        }
    int a1, a2, a3, a4, a5, a6;
    while (scanf("%d %d %d %d %d %d", &a1, &a2, &a3, &a4, &a5, &a6) == 6) {
        int from = a1 * 100000 + a2 * 10000 + a3 * 1000 + a4 * 100 + a5 * 10 + a6;
        scanf("%d %d %d %d %d %d", &a1, &a2, &a3, &a4, &a5, &a6);
        int to = a1 * 100000 + a2 * 10000 + a3 * 1000 + a4 * 100 + a5 * 10 + a6;
        l = r = 0;
        for (int i = 0; i < vm; i++) dist[vv[i]] = -1;
        que[r++] = from;
        dist[from] = 0;
        while (l < r) {
            int c = que[l++];
            if (c == to) break;
            for (int i = 0; i < 4; i++) {
                int t = cha[c][i];
                if (dist[t] == -1) {
                    dist[t] = dist[c] + 1;
                    que[r++] = t;
                }
            }
        }
        printf("%d\n", dist[to]);
    }
    return 0;
}
