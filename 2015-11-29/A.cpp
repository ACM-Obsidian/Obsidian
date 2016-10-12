#include <cstdio>
int a[1000000], b[1000];
int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = i; j < n; j++) {
			k = k * 10 + b[j];
			if (k >= 1000000)
				break;
			a[k] = 1;
		}
	}
	int k = 0;
	for (; a[k]; k++);
	printf("%d\n", k);
	return 0;
}
