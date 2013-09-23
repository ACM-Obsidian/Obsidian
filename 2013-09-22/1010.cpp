#include <cstdio>
int n, a[100000], b[100000], c[100000], l, r;
void solve() {
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) scanf("%d", &b[i]);
	c[0] = 0; c[1] = b[0];
	for (int i = 2; i < n; i++)
		c[i] = b[i-1]-c[i-1]-c[i-2];
	if (n % 3 == 0) l = r = c[n-1]+c[n-2]-b[n-1];
	else if (n % 3 == 1) l = r = b[n-1]-c[n-1]-c[n-2];
	else {
		l = r = -1;
		for (int i = 0; i < n; i++)
			if (a[i] != -1 && i % 3 != 2)
				if (i % 3 == 0) l = r = a[i]-c[i];
				else if (i % 3 == 1) l = r = c[i]-a[i];
		if (l == -1) {
			l = 0, r = ~0U>>1;
			for (int i = 0; i < n; i++)
				if (i % 3 == 0 && -c[i] > l) l = -c[i];
				else if (i % 3 == 1 && c[i] < r) r = c[i];
		}
	}
	int m; scanf("%d", &m);
	for (; m; m--) {
		int x;
		scanf("%d", &x);
		if (x % 3 == 2) printf("%d\n", c[x]);
		else if (x % 3 == 0) printf("%d\n", r+c[x]);
		else printf("%d\n", c[x]-l);
	}
}
int main() {
	for (; scanf("%d", &n) != EOF; solve());
	return 0;
}
