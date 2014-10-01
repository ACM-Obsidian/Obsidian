#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2010;
const int mod = 1000000007;
int arr[2][N * 2];
int sum[2][N * 2];
int T[N];

int main () {
    int kase; for (scanf("%d", &kase); kase; --kase) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", &T[i]);
        int m = T[0];
        int now = 0, last = 1;
        memset(arr, 0, sizeof arr);
        memset(sum, 0, sizeof sum);
        for (int i = 0; i <= m; i++) arr[now][i] = 1, sum[now][i] = i;
        for (int k = 1; k < n; k++) {
            swap(now, last);
            memset(arr[now], 0, sizeof arr[0]);
            memset(sum[now], 0, sizeof sum[0]);
            for (int i = 0; i <= m + T[k]; i++) {
                int ll = max(0, i - T[k]), rr = min(m, i);
                if (rr >= ll) {
                   long long tt = (long long)sum[last][rr] - sum[last][ll] + arr[last][ll];
                   tt %= mod;
                   if (tt < 0) tt += mod;
                   arr[now][i] = tt;
                }
                // printf("%d ", arr[now][i]);
                if (i == 0) sum[now][i] = arr[now][i];
                else sum[now][i] = (arr[now][i] + sum[now][i - 1]) % mod;
            }
            // printf("\n");
            m += T[k];
        }
        printf("%d\n", arr[now][m / 2]);
    }
    return 0;
}
