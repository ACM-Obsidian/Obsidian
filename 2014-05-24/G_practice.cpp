#include <cstdio>
int a[1000000][64], n, sum[64];
int main() {
	int T; for (scanf("%d", &T); T--; ) {
		scanf("%d", &n);
		for (int i = 0; i < 64; i++) sum[i] = 0;
		for (int i = 0; i < n; i++) {
			long long x; scanf("%lld", &x);
			for (int j = 0; j < 64; j++)
				a[i][j] = x>>j & 1, sum[j] += a[i][j];
		}
		for (int i = 0; i < 64; i++) sum[i] %= 3;
		int i = 63;
		for (; i >= 0; i--)
			if (sum[i] != 0) break;
		if (i < 0) puts("C");
		else if (sum[i] == 2) puts("B");
		else {
			int flag = 0;
			for (int i = 0; !flag && i < n; i++) {
				int flag2 = 1;
				for (int j = 0; j < 64; j++)
					if (a[i][j] == sum[j] - 1) flag2 = 0;
				if (flag2) flag = 1;
			}
			if (flag) puts("A");
			else puts("B");
		}
	}
	return 0;
}
