#include <cstdio>

int main(void) {
	int kase; scanf("%d", &kase); while (kase--) {
		int k; scanf("%d", &k); int t = 0;
		while (k--) {
			t = 2ll * t + 1;
		}
		printf("%d\n", t);
	}
	return 0;
}

