#include <cstdio>
const int c[16] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3};
int main() {
	freopen("cue.in","r",stdin);
	freopen("cue.out","w",stdout);
	int n; scanf("%d", &n);
	for (int i = 0; i <= n; i++) putchar(c[i]+48);
	puts("");
	return 0;
}
