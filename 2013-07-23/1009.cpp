#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int a[100010], n; char ch[100010];

bool Add(void) {
    a[1]++; int ret = 0;
    for (int i = 1; i <= n; i++) a[i + 1] += a[i] / 10, a[i] %= 10, ret += a[i];
    if (a[n + 1] > 0) n++, ret += a[n];
    return ret % 10 == 0;
}

int main(void) {
    int kase; scanf("%d", &kase); while (kase--) {
        scanf("%s", ch); n = strlen(ch); memset(a, 0, sizeof a); reverse(ch, ch + n);
        for (int i = 1; i <= n; i++) a[i] = ch[i - 1] - '0';
        while (true) {
            if (Add()) {
                for (int i = n; i >= 1; i--) printf("%d", a[i]);
                puts("");
                break;
            }
        }
    }
    return 0;
}