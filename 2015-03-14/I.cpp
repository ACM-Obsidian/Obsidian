#include <cstdio>
#include <cstring>
#include <algorithm>
struct segt {
	int l, r, min, max;
} t[400004];
char s[100001];
int a[100001], b[100001], c[100000], n, m;
void build(int l, int r, int p) {
	t[p].l = l, t[p]. r = r;
	if (l < r) {
		int mid = l + r >> 1;
		build(l, mid, p * 2), build(mid + 1, r, p * 2 + 1);
	}
}
void putmin(int k, int x) {
	int p = 1;
	while (t[p].l < t[p].r)
		if (k - t[p].l <= t[p].r - k) p *= 2;
		else p = p * 2 + 1;
	t[p].min = x;
	for (p >>= 1; p; p >>= 1)
		t[p].min = std::max(t[p * 2].min, t[p * 2 + 1].min);
}
void putmax(int k, int x) {
	int p = 1;
	while (t[p].l < t[p].r)
		if (k - t[p].l <= t[p].r - k) p *= 2;
		else p = p * 2 + 1;
	t[p].max = x;
	for (p >>= 1; p; p >>= 1)
		t[p].max = std::min(t[p * 2].max, t[p * 2 + 1].max);
}
bool can() {
	return t[1].min <= t[1].max;
}
bool solve() {
	for (int i = 0; i < n; i++)
		c[i] = 0;
	for (int i = 0; i < m; i++)
		c[i % n] += a[i];
	for (int i = 0; i < n; i++)
		putmin(i, c[i]), putmax(i, c[i]);
	for (int i = 0; i < m; i++) {
		c[i % n] -= a[i];
		putmin(i % n, a[i] + 1 + c[i % n]), putmax(i % n, 9 + c[i % n] + i / n * 9);
		if (a[i] < 9 && can()) {
			for (int j = i; j >= 0; j--) {
				int k = (j == i ? a[i] + 1 : 0);
				for (; k <= 9; k++) {
					putmin(j % n, k + c[j % n]), putmax(j % n, k + c[j % n] + j / n * 9);
					if (can()) break;
				}
				a[j] = k;
				c[j % n] += k;
			}
			return true;
		}
		putmin(i % n, c[i % n]);
	}
	return false;
}
int main() {
	freopen("ticket.in", "r", stdin);
	freopen("ticket.out", "w", stdout);
	int N;
	scanf("%d%s", &N, s);
	m = strlen(s);
	n = std::min(N, m);
	build(0, n-1, 1);
	for (int i = 0; i < m; i++)
		a[i] = s[m-i-1] - 48;
	if (!solve()) {
		for (int i = 0; i < m; i++)
			a[i] = 9;
		a[m] = 0;
		m++;
		n = std::min(N, m);
		build(0, n-1, 1);
		solve();
	}
	for (int i = m-1; i >= 0; i--)
		printf("%d", a[i]);
	puts("");
	return 0;
}
