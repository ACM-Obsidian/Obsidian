#include <cstdio>
#include <algorithm>
int a[1000000], b[1000000], c[1000000];
int main() {
	int n;
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		for (int i = 1; i < n; i++) a[i] += a[i-1];
		b[0] = a[0];
		for (int i = 1; i < n; i++) b[i] = std::min(b[i-1], a[i]);
		c[n-1] = a[n-1];
		for (int i = n-2; i >= 0; i--) c[i] = std::min(c[i+1], a[i]);
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if ((i == 0 || c[n-i] >= a[n-i-1]) && b[n-i-1]+a[n-1]-a[n-i-1] >= 0)
				cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}
