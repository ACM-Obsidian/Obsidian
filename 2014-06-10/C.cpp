#include <cstdio>
#include <cmath>
typedef int int128 __attribute__((mode(TI)));
long long a[89];
int main() {
	a[0] = 1, a[1] = 0;
	int i = 2;
	for (; i < 89; i++) {
		a[i] = a[i-1] + a[i-2];
	}
	int T; for (scanf("%d", &T); T--; ) {
		long long x, y; scanf("%lld%lld", &x, &y);
		long long ansk1 = ~0ULL>>1, ansk2 = ~0ULL>>1;
		int128 tx[89], ty[89];
		for (int i = 0; i < 89; i++)
			tx[i] = (int128)a[i]*x, ty[i] = (int128)a[i]*y;
		long long ratio = y/x;
		int p = 2; for (; p < 89; p++) if (a[p] > ratio) break;
		p -= 3; if (p < 1) p = 1;
		for (int i = 0; i < 88; i++)
			for (int j = (i == 0 ? 1 : i+p); j < i+p+2 && j < 88; j++) {
				long long a1 = a[i], a2 = a[i+1], b1 = a[j], b2 = a[j+1];
				if (a1 + a2 > x || b1 + b2 > y) continue;
				long long d = a[j-i+1];
				if (i & 1) d = -d;
				int128 k1 = tx[j+1]-ty[i+1];
				int128 k2 = ty[i]-tx[j];
				if (k1 % d == 0 && k2 % d == 0) {
					k1 /= d, k2 /= d;
					if (k1 > 0 && k2 > 0 && k1 <= k2)
						if (k1 < ansk1 || k1 == ansk1 && k2 < ansk2)
							ansk1 = k1, ansk2 = k2;
				}
			}
		printf("%lld %lld\n", ansk1, ansk2);
	}
	return 0;
}
