#include <cstdio>
int main() {
	freopen("continued.in", "r", stdin);
	freopen("continued.out", "w", stdout);
	int n, m; scanf("%d%d", &n, &m);
	printf("%d\n", (n % m ? 3 : 1));
	if (n >= m) {
		for (int i = n-m; i >= 0; i--)
			putchar(48+!((n-i)%m));
		n = n%m;
	} else putchar(48);
	putchar(32);
	if (n > 0) {
		for (int i = m-n; i; i--) putchar(57);
		printf(" 1 ");
		for (int i = n; i; i--) putchar(57);
	} else
		for (int i = m; i; i--) putchar(57);
	puts("");
}
