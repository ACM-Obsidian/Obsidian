#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000010;
const int base = 13331;

typedef unsigned long long Int64;

char ch[MAXN]; Int64 Sum[MAXN], pow[MAXN];

inline Int64 Cal(int l, int r) {
    return Sum[r] - Sum[l - 1] * pow[r - l + 1];
}

int main(void) {
    //freopen("in", "r", stdin);
    pow[0] = 1;
    for (int i = 1; i < MAXN; i++) pow[i] = pow[i - 1] * base;
    int kase; scanf("%d", &kase); while (kase--) {
        scanf("%s", ch + 1); int n = strlen(ch + 1);
        for (int i = 1; i <= n; i++) Sum[i] = Sum[i - 1] * base + ch[i] - 'a' + 1;
        int l = 1, r = n / 3 + 2;
        while (l <= r) {
            int mid = (l + r) >> 1; Int64 mode = Cal(1, mid);
            bool ok = false;
            for (int i = mid + 1; i <= n - 2 * mid + 1; i++) {
                if (mode == Cal(i, i + mid - 1)) {
                    ok = true;
                    break;
                }
            }
            if (ok) l = mid + 1; else r = mid - 1;
        }
        int Ans = r;
        while (Ans) {
            if (Cal(1, Ans) == Cal(n - Ans + 1, n)) break;
            Ans--;
        }
        printf("%d\n", Ans);
    }
    return 0;
}
