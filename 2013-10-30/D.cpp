#include <cstdio>
int main() {
	freopen("divide.in","r",stdin);
	freopen("divide.out","w",stdout);
	int n;
	scanf("%d", &n);
	int x = 65536/n;
	if (65536%n) x++;
	printf("y = x * %d\n", x);
	puts("y = y >> 16");
	printf("z = y * %d\n", n);
	puts("z = x - z");
	puts("z = z >> 31");
	puts("y = y - z");
	puts("return y");
	return 0;
}
