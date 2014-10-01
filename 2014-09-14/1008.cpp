#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 131072;

int per[N];
int arr[N];

void solve (int n) {
    if (n == 1) {
        arr[0] = 0;
        return;
    }
    int p = 1;
    while ((p << 1) <= n) p <<= 1;
    int mask = (p << 1) - 1;
    if (p == n) {
        mask >>= 1;
        for (int i = 0; i < n; i++) arr[i] = i ^ mask;
    } else {
        for (int i = p; i < n; i++) arr[i] = i ^ mask, arr[i ^ mask] = i;
        solve((n ^ mask) + 1);
    }
}

int main () {
    int n; while (scanf("%d", &n) == 1) {
        ++n;
        for (int i = 0; i < n; i++) scanf("%d", &per[i]);
        solve(n);
        long long ans = 0;
        for (int i = 0; i < n; i++) ans += i ^ arr[i];
        printf("%I64d\n", ans);
        for (int i = 0; i < n; i++) printf("%d%c", arr[per[i]], " \n"[i == n - 1]);
    }
    return 0;
}
