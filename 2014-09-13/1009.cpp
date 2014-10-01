#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210, M = 100010;

int n, hd[N], nxt[M], to[M], mr;
int ope[N], amb[N], xq[N];
int indeg[N], pindeg[N];

int que[N], ll, rr;

void link (int a, int b) {
     nxt[mr] = hd[a], to[mr] = b; hd[a] = mr++;
}

int ans1 (void) {
    ll = rr = 0;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) que[rr++] = i;
        else amb[i] = xq[i] = -1;
        pindeg[i] = indeg[i];
    }
    while (ll < rr) {
        int c = que[ll++];
        for (int p = hd[c]; p != -1; p = nxt[p]) {
            if (ope[to[p]] == 0 && amb[c] > amb[to[p]])
                amb[to[p]] = amb[c], xq[to[p]] = xq[c];
            else if (ope[to[p]] == 1 && xq[c] > xq[to[p]])
                amb[to[p]] = amb[c], xq[to[p]] = xq[c];
            --pindeg[to[p]];
            if (pindeg[to[p]] == 0) que[rr++] = to[p];
        }
    }
    return xq[0];
}

bool valid (int expect_xq) {
    ll = rr = 0;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) que[rr++] = i;
        else amb[i] = xq[i] = -1;
        pindeg[i] = indeg[i];
    }
    while (ll < rr) {
        int c = que[ll++];
        for (int p = hd[c]; p != -1; p = nxt[p]) {
            if (ope[to[p]] == 0 && amb[c] > amb[to[p]])
                amb[to[p]] = amb[c], xq[to[p]] = xq[c];
            else if (ope[to[p]] == 1) {
                if (xq[c] >= expect_xq) {
                    if (amb[c] > amb[to[p]]) {
                        amb[to[p]] = amb[c], xq[to[p]] = xq[c];
                    }
                } else {
                    if (xq[to[p]] < expect_xq && amb[c] < amb[to[p]]) {
                        amb[to[p]] = amb[c], xq[to[p]] = xq[c];
                    }
                }
            }
            --pindeg[to[p]];
            if (pindeg[to[p]] == 0) que[rr++] = to[p];
        }
    }
    return xq[0] >= expect_xq;
}

int main () {
    int kase; for (scanf("%d", &kase); kase; --kase) {
        scanf("%d", &n);
        memset(hd, -1, sizeof hd);
        memset(indeg, 0, sizeof indeg);
        mr = 0;
        int maxxq = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &indeg[i]);
            if (indeg[i] == 0) {
                ope[i] = -1;
                scanf("%d %d", &amb[i], &xq[i]);
                maxxq = max(maxxq, xq[i]);
            } else {
                for (int j = 0; j < indeg[i]; j++) {
                    int x; scanf("%d", &x); --x;
                    link(x, i);
                }
                char tt[5]; scanf("%s", tt);
                if (tt[0] == 'A') ope[i] = 0;
                else ope[i] = 1;
            }
        }
        printf("%d ", ans1());
        int l = 0, r = maxxq + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (valid(m)) l = m;
            else r = m;
        }
        printf("%d\n", l);
    }
    return 0;
}
