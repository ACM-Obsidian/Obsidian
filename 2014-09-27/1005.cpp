#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 62;

int x[N], y[N];
inline long long dis (int a, int b) {
    return (long long)abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

int n, k;
long long serial[N];

bool comp (long long a, long long b) {
    return __builtin_popcount(a) < __builtin_popcount(b);
}

inline void generate_serial (long long max_dis) {
    for (int i = 0; i < n; i++) {
        serial[i] = 0;
        for (int j = 0; j < n; j++) if (dis(i, j) <= max_dis) {
            serial[i] |= (1LL << j);
        }
        // printf("%X\n", serial[i]);
    }
    sort(serial, serial + n, comp);
}
bool ida (int max_depth, long long built) {
    int h = 0;
    long long t = built, c = 0;
    for (int i = 0; i < n; i++) {
        if ((t & serial[i]) == 0) {
            ++h; t |= serial[i];
            if (!c) c = serial[i];
        }
    }
    // printf("IDA %d %I64X %d\n", max_depth, built, h);
    if (h == 0) return true;
    else if (max_depth < h) return false;
    for (int i = 0; i < n; i++) if (!(built & (1LL << i)) && (c & (1LL << i))) {
        if (ida(max_depth - 1, built | (1LL << i)))
            return true;
    }
    return false;
}
bool ok (long long max_dis) {
    // printf("JUDGE %I64d\n", max_dis);
    generate_serial(max_dis);
    return ida(k, 0);
} 

int main () {
    int kase, T = 0; for (scanf("%d", &kase); kase; --kase) {
        ++T;
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);
        long long l = -1, r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                r = max(r, dis(i, j));
            }
        }
        // printf("%I64d %I64d\n", l, r);
        while (r - l > 1) {
            long long m = (l + r) / 2;
            if (ok(m)) r = m;
            else l = m;
        }
        printf("Case #%d: %I64d\n", T, r); 
    }
    return 0;
}

