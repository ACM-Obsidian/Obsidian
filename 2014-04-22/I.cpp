#include <cstdio>

const int MAXN = 100010, inf = 100000000;

struct Point {int x,y;} c[MAXN];
struct Rect {int x1, y1, x2, y2;} a[MAXN];

int n;

inline int f(int id, int x1, int x2, int y1, int y2) {
	if (id > n) return 1;
	if (x1 > a[id].x2 || x2 < a[id].x1 || y1 > a[id].y2 || y2 < a[id].y1) return f(id + 1, x1, x2, y1, y2);
	int ret = 0;
	if (!ret && a[id].x1 > x1 && a[id].x1 <= x2) ret |= f(id + 1, x1, a[id].x1 - 1, y1, y2), x1 = a[id].x1;
	if (!ret && a[id].x2 < x2 && a[id].x2 >= x1) ret |= f(id + 1, a[id].x2 + 1, x2, y1, y2), x2 = a[id].x2;
	if (!ret && a[id].y1 > y1 && a[id].y1 <= y2) ret |= f(id + 1, x1, x2, y1, a[id].y1 - 1), y1 = a[id].y1;
	if (!ret && a[id].y2 < y2 && a[id].y2 >= y1) ret |= f(id + 1, x1, x2, a[id].y2 + 1, y2), y2 = a[id].y2;
	return ret;
}

int main(void) {
	int kase = 0;
	while (scanf("%d", &n), n != -1) {
		printf("Case %d: ", ++kase);
		for (int i = 1; i <= n; i++) scanf("%d%d", &c[i].x, &c[i].y);
		int l = 1, r = inf;
		while (l <= r) {
			int mid = (l + r) >> 1;
			for (int i = 0; i <= n; i++) {
				a[i].x1 = c[i].x - mid;
				a[i].y1 = c[i].y - mid;
				a[i].x2 = c[i].x + mid;
				a[i].y2 = c[i].y + mid;
			}
			if (f(1, a[0].x1, a[0].x2, a[0].y1, a[0].y2)) l = mid + 1; else r = mid - 1;
		}
		if (l > inf) puts("never"); else printf("%d\n", l);
	}
	return 0;
}

