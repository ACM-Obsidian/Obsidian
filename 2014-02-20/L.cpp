#include <cstdio>
#include <algorithm>
struct func {
	double a, b, c, l, r;
} a[100000];
double x1[100000], y1[100000], x2[100000], y2[100000], sum[100001];
std::pair<double, int> t[100000];
int n1, n2;
int cmp(func a, double b) {
	return a.r < b;
}
int main() {
	//freopen("lonely.in", "r", stdin);
	//freopen("lonely.out", "w", stdout);
	scanf("%d", &n1);
	for (int i = 0; i < n1; i++)
		scanf("%lf%lf", &x1[i], &y1[i]);
	scanf("%d", &n2);
	for (int i = 0; i < n2; i++)
		scanf("%lf%lf", &x2[i], &y2[i]), t[i].first = -y2[i], t[i].second = i;
	if (*std::max_element(y1, y1+n1) != *std::max_element(y2, y2+n2)) {
		puts("Invalid plan");
		return 0;
	}
	std::sort(t, t+n2);
	int m = 0;
	double c = 0, d = 0;
	for (int i = 0, j = 0; i < n2; i = j) {
		for (; j < n2 && t[i].first == t[j].first; j++);
		for (int k = i; k < j; k++) {
			if (t[k].second > 0 && y2[t[k].second-1] > y2[t[k].second]) {
				c -= (x2[t[k].second] - x2[t[k].second-1]) / (y2[t[k].second-1] - y2[t[k].second]) * y2[t[k].second];
				d -= (x2[t[k].second] - x2[t[k].second-1]) / (y2[t[k].second-1] - y2[t[k].second]);
			}
			if (t[k].second < n2-1 && y2[t[k].second+1] > y2[t[k].second]) {
				c -= (x2[t[k].second+1] - x2[t[k].second]) / (y2[t[k].second+1] - y2[t[k].second]) * y2[t[k].second];
				d -= (x2[t[k].second+1] - x2[t[k].second]) / (y2[t[k].second+1] - y2[t[k].second]);
			}
			if (t[k].second > 0 && y2[t[k].second-1] < y2[t[k].second]) {
				d += (x2[t[k].second] - x2[t[k].second-1]) / (y2[t[k].second] - y2[t[k].second-1]);
				c += (x2[t[k].second] - x2[t[k].second-1]) / (y2[t[k].second] - y2[t[k].second-1]) * y2[t[k].second];
			}
			if (t[k].second < n2-1 && y2[t[k].second+1] < y2[t[k].second]) {
				d += (x2[t[k].second+1] - x2[t[k].second]) / (y2[t[k].second] - y2[t[k].second+1]);
				c += (x2[t[k].second+1] - x2[t[k].second]) / (y2[t[k].second] - y2[t[k].second+1]) * y2[t[k].second];
			}
			if (t[k].second < n2-1 && y2[t[k].second+1] == y2[t[k].second])
				c += x2[t[k].second+1] - x2[t[k].second];
		}
		if (y2[t[i].second] > 0) {
			a[m].a = -d, a[m].b = c;
			a[m].l = y2[t[j].second], a[m].r = y2[t[i].second];
			m++;
		}
	}
	std::reverse(a, a + m);
	c = 0;
	for (int i = 0; i < m; i++) {
		a[i].c = c - (a[i].a/2 * a[i].l + a[i].b) * a[i].l;
		a[i].a /= 2;
		c = (a[i].a * a[i].r + a[i].b) * a[i].r + a[i].c;
	}
	sum[0] = 0;
	for (int i = 0; i < m; i++)
		sum[i+1] = sum[i] + ((a[i].a/3 * a[i].r + a[i].b/2) * a[i].r + a[i].c) * a[i].r - ((a[i].a/3 * a[i].l + a[i].b/2) * a[i].l + a[i].c) * a[i].l;
	double ans = 0;
	for (int i = 0; i < n1-1; i++) {
		int l = std::lower_bound(a, a + m, y1[i], cmp) - a, r = std::lower_bound(a, a + m, y1[i+1], cmp) - a;
		if (y1[i] == y1[i+1]) ans += ((a[l].a * y1[i] + a[l].b) * y1[i] + a[l].c) * (x1[i+1] - x1[i]);
		else {
			double k = (x1[i+1] - x1[i]) / (y1[i+1] - y1[i]);
			ans += k * (sum[r] - sum[l] - ((a[l].a/3 * y1[i] + a[l].b/2) * y1[i] + a[l].c) * y1[i] + ((a[l].a/3 * a[l].l + a[l].b/2) * a[l].l + a[l].c) * a[l].l
					+ ((a[r].a/3 * y1[i+1] + a[r].b/2) * y1[i+1] + a[r].c) * y1[i+1] - ((a[r].a/3 * a[r].l + a[r].b/2) * a[r].l + a[r].c) * a[r].l);
		}
	}
	printf("%lf\n", ans);
	return 0;
}
