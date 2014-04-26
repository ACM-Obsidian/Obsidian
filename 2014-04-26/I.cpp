#include <cstdio>

int main(void) {
	int n, k; scanf("%d%d", &n, &k);
	for (int i = 0; i < (1 << n); i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) if (i & (1 << j)) cnt++;
		putchar(cnt%2?'A':'B');
	}
	puts("");
	return 0;
}

