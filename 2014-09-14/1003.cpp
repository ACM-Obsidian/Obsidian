#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
using namespace std;

const int N = 50010;
const int inf = 19931005;

map<int, int> last;
int crucial[N], l, r;
int arr[N], dp[N];

inline void del (int x) {
    for (int i = l; i < r; i++) {
        if (crucial[i] == x) {
            for (int j = i; j + 1 < r; j++)
                crucial[j] = crucial[j + 1];
            --r;
            return;
        }
    }
}

int main () {
    int n; while (scanf("%d", &n) == 1) {
        int m = (int)sqrt(n) + 2;
        l = r = 0;
        crucial[r++] = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
        last.clear();
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            // printf("- %d\n", i);
            if (last.find(arr[i]) != last.end()) {
                del(last[arr[i]]);
            }
            last[arr[i]] = i;
            crucial[r++] = i;
            int typ = 1;
            if (r - l > m) ++l;
            dp[i] = dp[i - 1] + 1;
            for (int j = r - 1; j >= l; j--) {
                int c = crucial[j];
                // printf("---- %d\n", c);
                if (c != i) {
                    dp[i] = min(dp[i], dp[c] + typ * typ);
                    ++typ;
                    if (typ * typ >= dp[i]) break;
                }
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
