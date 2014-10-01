#include <cstdio>
#include <algorithm>

using namespace std;

int n;

int main(void) {
    while (scanf("%d", &n) == 1) {
        int g = 0, x;
        for (int i = 1; i <= n; i++) scanf("%d", &x), g ^= x;
        puts(g ? "Win" : "Lose");
    }
    return 0;
}
