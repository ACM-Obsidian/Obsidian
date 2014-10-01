#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int a[10010];

int main () {
    int kase; for (scanf("%d", &kase); kase; --kase) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a + n);
        double base = 1, ans = 0;
        for (int i = n - 1; i >= 0; i--)
            ans += base * a[i], base *= 0.95;
        printf("%.8lf\n", ans);
    }
    return 0;
}
