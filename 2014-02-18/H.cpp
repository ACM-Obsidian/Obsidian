#include <cstdio>
#include <algorithm>
int a[1000];
int main() {
	int n, p;
	scanf("%d%d", &n, &p);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	std::sort(a, a + n);
	int cur = 0, num = 0, cnt = 0;
	for (int i = 0, j = 0; ; i = j) {
		for (; j < n && a[i] == a[j]; j++);
		if (i == n || a[i] * (cur + j-i) > p) {
			if (cur) {
				num++; cnt += cur;
			}
			if (i == n || a[i] * (j-i) > p) break;
			cur = j-i;
		} else cur += j-i;
	}
	printf("%d %d\n", cnt, num);
	return 0;
}
