#include <cstdio>
#include <cstring>
#define P 33554432
int a[41], b[41];
void add(int *a, int *b, int *c) {
    for (int i = 0, s, g = 0; i <= 40; i++)
        s = a[i] + b[i] + g, c[i] = s % P, g = s / P;
}
void sub(int *a, int *b, int *c) {
    for (int i = 0, s, g = 0; i <= 40; i++)
        s = a[i] - b[i] - g, s < 0 ? (c[i] = s + P, g = 1) : (c[i] = s, g = 0);
}
void div2(int *a, int *b) {
    for (int i = 40, s, g = 0; i >= 0; i--)
        s = g * P + a[i], b[i] = s / 2, g = s % 2;
}
bool less(int *a, int *b) {
    for (int i = 40; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i];
    return false;
}
bool null(int *a) {
    for (int i = 0; i <= 40; i++)
        if (a[i]) return false;
    return true;
}
void print(int x, bool full) {
    bool flag = full;
    for (int i = 24; i >= 0; i--) {
        if (x & 1<<i) flag = true;
        if (flag) putchar(x & 1<<i ? '1' : '0');
    }
}
char s[1002], t[1002];
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        scanf("%s%s", s, t);
        for (int i = 0; i <= 40; i++) a[i] = b[i] = 0;
        int cnt = 0;
        for (int i = 0, l = strlen(s); i < l; i++) {
            add(a, a, a);
            if (s[i] == '1') a[0]++;
        }
        for (int i = 0, l = strlen(t); i < l; i++) {
            add(b, b, b);
            if (t[i] == '1') b[0]++;
        }
        while (!null(a) && !null(b)) {
            if (!(a[0]&1) && !(b[0]&1)) div2(a, a), div2(b, b), cnt++;
            else if (!(a[0]&1)) div2(a, a);
            else if (!(b[0]&1)) div2(b, b);
            else if (less(a, b)) sub(b, a, b);
            else sub(a, b, a);
        }
        if (null(a)) memcpy(a, b, sizeof a);
        for (int i = 0; i < cnt; i++)
            add(a, a, a);
        int i = 40; for (; i >= 0; i--) if (a[i]) break;
        printf("Case #%d: ", _); print(a[i], false);
        for (i--; i >= 0; i--)
            print(a[i], true);
        printf("\n");
    }
    return 0;
}
