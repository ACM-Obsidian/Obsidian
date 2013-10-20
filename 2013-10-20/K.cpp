#include <cstdio>
#include <algorithm>
int ans[200000], q[200000];
int main() {
	int a, b, c, x, y, n, k, l = 0;
	scanf("%d%d%d%d%d%d%d", &n, &k, &x, &y, &a, &b, &c);
	int tx = x, ty = y, tz;
	for (int i = 0; i < n; i++) {
		tz = a*tx+b*ty+c&(1<<31)-1;
		tx = ty, ty = tz;
		if (!(i%20)) {
			if (l >= k && tz <= -q[0]) continue;
			if (l >= k) std::pop_heap(q, q+l), l--;
			q[l++] = -tz, std::push_heap(q, q+l);
		}
	}
	tx = x, ty = y;
	for (int i = 0; i < n; i++) {
		tz = a*tx+b*ty+c&(1<<31)-1;
		tx = ty, ty = tz;
		if (i%20) {
			if (l >= k && tz <= -q[0]) continue;
			if (l >= k) std::pop_heap(q, q+l), l--;
			q[l++] = -tz, std::push_heap(q, q+l);
		}
	}
	for (int i = 0; i < k; i++) ans[k-i-1] = -q[0], std::pop_heap(q, q+l), l--;
	printf("%d", ans[0]);
	for (int i = 1; i < k; i++) printf(" %d", ans[i]);
	puts("");
	return 0;
}
