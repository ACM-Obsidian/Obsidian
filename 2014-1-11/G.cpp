#include <cstdio>
#include <algorithm>

int a[10010], N;

int main(void) {
	int n; while (scanf("%d", &n) == 1) {
		N = 0;
		int Ans = 0;
		for (int i = 2; i <= n; i++) {
			bool prime = true;
			for (int j = 2; j * j <= i; j++) if (i % j == 0) {
				prime = false;
				break;
			}
			if (prime) a[++N] = i;
		}
		int l = N;
		for (int i = 1; i <= l; i++, l--) {
			// printf("%d\n", i);
			while (l > i && a[i] * a[l] > n) l--, Ans++;
			Ans++;
		}
		printf("%d\n", Ans);
	}
	return 0;
}

