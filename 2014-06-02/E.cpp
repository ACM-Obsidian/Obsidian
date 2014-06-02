#include <cstdio>
#include <algorithm>
int a[3];
int main() {
	scanf("%d%d%d", &a[0], &a[1], &a[2]);
	std::sort(a, a+3);
	if (a[2] >= a[0] + a[1]) {
		if (!(a[0] & 1) && !(a[1] & 1)) puts("Petya");
		else puts("Masha");
	} else if (!(a[0] & 1) && !(a[1] & 1) && !(a[2] & 1)) {
		puts("Petya");
	} else {
		if (a[0] + a[1] + a[2] & 1 && (a[2] + a[1] >> 1 & 1) == (a[0] >> 1 & 1)) puts("Petya");
		else puts("Masha");
	}
	return 0;
}
