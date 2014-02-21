#include <cstdio>
#define P 1000000007
int f[5000];
int main() {
	int n; scanf("%d", &n);
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		int t = 1;
		for (int j = i-1; j; j--) {
			t = 1LL * t * i % P;
			f[i] -= 1LL * t * f[j] % P;
			if (f[i] < 0) f[i] += P;
		}
		t = 1LL * t * i % P;
		f[i] += t;
		if (f[i] >= P) f[i] -= P;
	}
	printf("%d\n", f[n]);
	return 0;
}
