#include <cstdio>
#include <algorithm>
const int dx[4] = {1, 1, -1, -1};
const int dy[4] = {-1, 1, 1, -1};
struct itv {
	int l, r, len;
} a[1000], b[1000];
int n, w, h, dirmap[256];
int cmp(itv a, itv b) {
	return a.l < b.l || a.l == b.l && a.len < b.len;
}
int intersect(int x, int y, int dx, int dy) {
	if (dy < 0 && x + dx * y >= 0 && x + dx * y <= w)
		return x + dx * y;
	if (dx > 0 && y + dy * (w - x) >= 0 && y + dy * (w - x) <= h)
		return y + dy * (w - x) + w;
	if (dy > 0 && x + dx * (h - y) >= 0 && x + dx * (h - y) <= w)
		return 2 * w + h - (x + dx * (h - y));
	if (dx < 0 && y + dy * x >= 0 && y + dy * x <= h)
		return 2 * (w + h) - (y + dy * x);
	puts("error");
	return -1;
}
int main() {
	dirmap['E'] = 0;
	dirmap['N'] = 1;
	dirmap['W'] = 2;
	dirmap['S'] = 3;
	scanf("%d%d%d", &n, &w, &h);
	for (int i = 0; i < n; i++) {
		int x, y; char dir;
		scanf("%d %d %c", &x, &y, &dir);
		int d = dirmap[dir];
		a[i].l = intersect(x, y, dx[d], dy[d]);
		a[i].r = intersect(x, y, dx[(d+1)%4], dy[(d+1)%4]);
		a[i].len = (a[i].r < a[i].l ? 2*(w+h) : 0) + (a[i].r - a[i].l);
	}
	std::sort(a, a + n, cmp);
	int ans = n;
	for (int i = 0; i < 2*n; i++) {
		int x = (i & 1 ? a[i >> 1].r : a[i >> 1].l);
		int k = 0;
		for (; k < n && a[k].l < x; k++);
		int l = 0;
		for (int j = 0; j < n; j++) {
			int id = (k+j)%n;
			if (a[id].l <= x && x <= a[id].l + a[id].len
					|| a[id].l <= x + 2*(w+h) && x + 2*(w+h) <= a[id].l + a[id].len)
				continue;
			b[l] = a[id];
			if (b[l].l < x)
				b[l].l += 2*(w+h);
			if (b[l].r < b[l].l)
				b[l].r += 2*(w+h);
			l++;
		}
		int cnt = 1;
		if (l > 0) {
			int r = 4*(w+h);
			for (int j = 0; j < l; j++)
				if (b[j].r < r)
					r = b[j].r;
				else if (b[j].l > r) {
					cnt++;
					r = b[j].r;
				}
			cnt++;
		}
		if (cnt < ans)
			ans = cnt;
	}
	printf("%d\n", ans);
}
