#include <cstdio>
int main() {
	int n, l;
	scanf("%d%d", &n, &l);
	if (l%2 == 1 || l > n*n)
		puts("Unsuitable device");
	else {
		puts("Overwhelming power of magic");
		if (l <= 2*n) {
			for (int i = 1; i <= l/2; i++)
				printf("%d 1\n", i);
			for (int i = l/2; i >= 1; i--)
				printf("%d 2\n", i);
		} else if (n%2 == 1 && l >= n*(n-1)) {
			for (int i = 2; i <= n; i++)
				printf("%d 1\n", i);
			for (int i = n-1; i >= 4; i -= 2) {
				for (int j = 2; j <= n; j++)
					printf("%d %d\n", i+1, j);
				for (int j = n; j >= 2; j--)
					printf("%d %d\n", i, j);
			}
			for (int j = 2; j <= n; j++)
				printf("3 %d\n", j);
			for (int j = 0; j < l-n*(n-1); j += 2)
				printf("2 %d\n1 %d\n1 %d\n2 %d\n", n-j, n-j, n-j-1, n-j-1);
			for (int j = n*n-l; j >= 2; j--)
				printf("2 %d\n", j);
		} else {
			int k = n&-2, cnt = (l-2*k)/(2*(n-2)), rem = (l-2*k)%(2*(n-2));
			for (int i = 1; i <= k; i++)
				printf("%d 1\n", i);
			for (int i = 0; i < cnt; i++) {
				for (int j = 2; j <= n; j++)
					printf("%d %d\n", k-2*i, j);
				for (int j = n; j >= 2; j--)
					printf("%d %d\n", k-2*i-1, j);
			}
			if (rem) {
				for (int i = 0; i <= rem/2; i++)
					printf("%d %d\n", k-2*cnt, 2+i);
				for (int i = rem/2; i >= 0; i--)
					printf("%d %d\n", k-2*cnt-1, 2+i);
				cnt++;
			}
			for (int i = k-2*cnt; i >= 1; i--)
				printf("%d 2\n", i);
		}
	}
	return 0;
}
