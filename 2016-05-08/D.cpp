#include <cstdio>
#include <cstring>
int a[1000], b[1000], f, g;
void mul(int *a, int &f, int c) {
	a[f+1] = 0;
	for (int j = 0, g = 0, s; j <= f+1; j++)
		s = a[j] * c + g, a[j] = s % 10, g = s / 10;
	if (a[f+1]) f++;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		if (n == 1) puts("1");
		else if (n == 2) puts("-1");
		else if (n == 3) puts("1\n2\n3");
		else {
			puts("1\n2");
			a[0] = 3, f = 0;
			for (int i = 0; i < n-4; i++) {
				for (int j = f; j >= 0; j--) printf("%d", a[j]);
				puts("");
				mul(a, f, 2);
			}
			g = f, memcpy(b, a, sizeof(a));
			mul(a, f, 2);
			mul(b, g, 3);
			for (int j = f; j >= 0; j--) printf("%d", a[j]);
			puts("");
			for (int j = g; j >= 0; j--) printf("%d", b[j]);
			puts("");
		}
	}
	return 0;
}
