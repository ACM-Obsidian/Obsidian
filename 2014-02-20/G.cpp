#include <cstdio>

inline int f(int S, int x) {
	int t = S / x;
	return (t + 1) >> 1;
}

int main(void) {
	freopen("garage.in", "r", stdin);
	freopen("garage.out", "w", stdout);
	int a, b, x, y;
	scanf("%d%d%d%d", &a, &b, &x, &y);
	printf("%d\n", f(a, x) * f(b, y));
	return 0;
}

