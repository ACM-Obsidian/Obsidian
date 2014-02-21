#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000100;

int a[MAXN << 1], n, top, full;

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		if (x > 0) {
			a[++top] = x;
			if (top >= n) full = 1;
		} else if (x < 0) printf("%d\n", a[top--]);
		else {
			if (top * 2 <= n && !full) {
				for (int j = 1; j <= top; j++) a[top + j] = a[j];
				top *= 2;
			} else if (top < n && !full) {
				full = 1;
				int d = n - top;
				for (int j = top; j >= 1; j--) a[j + d] = a[j];
				for (int j = 1; j <= d; j++) a[j] = a[n - d + j];
				top = n;
			}
		}
	}
	return 0;
}

