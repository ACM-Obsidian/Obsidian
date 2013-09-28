#include <cstdio>
int main() {
    int n, k;
    for (; scanf("%d%d", &n, &k), n; )
        if (!((n-1)%(k+1))) puts("Jiang");
        else puts("Tang");
    return 0;
}
