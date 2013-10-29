#include <cstdio>

using namespace std;

int w, b;

int main(void) {
	freopen("ichess.in", "r", stdin);
	freopen("ichess.out", "w", stdout);
	while (scanf("%d%d", &w, &b) == 2) {
		int i;
		for (i = 0; ; i++) {
			int tw = i * i / 2;
			int tb = i * i / 2;
			if (i * i % 2 == 1) tw++;
			if ( !(tw <= w && tb <= b || tw <= b && tb <= w)) {
				break;
			}
		}
		if (i == 1) puts("Impossible"); else printf("%d\n", i - 1);
	}
	return 0;
}

