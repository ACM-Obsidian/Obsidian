#include <cstdio>
#include <algorithm>
struct segt {
	bool left;
	int min, delta;
	int l, r;
} t[1200000];
char s[300001];
int sum[300000], n, m;
void push(int p) {
	int delta = t[p].delta;
	t[p*2].min += delta, t[p*2].delta += delta;
	t[p*2+1].min += delta, t[p*2+1].delta += delta;
	t[p].delta = 0;
}
void update(int p) {
	t[p].left = t[p*2].left && t[p*2+1].left;
	t[p].min = std::min(t[p*2].min, t[p*2+1].min);
}
void build(int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l < r) {
		int mid = l+r>>1;
		build(l, mid, p*2), build(mid+1, r, p*2+1);
		update(p);
	} else {
		t[p].left = (s[l] == '(');
		t[p].min = sum[l];
		t[p].delta = 0;
	}
}
void flip(int k) {
	int p = 1;
	while (t[p].l < t[p].r) {
		push(p);
		if (k - t[p].l <= t[p].r - k) p = p*2;
		else p = p*2+1;
	}
	t[p].left = !t[p].left;
	for (p>>=1; p; p>>=1)
		update(p);
}
void add(int l, int r, int p, int d) {
	if (t[p].l == l && t[p].r == r)
		t[p].delta += d, t[p].min += d;
	else {
		push(p);
		int mid = t[p].l+t[p].r>>1;
		if (r <= mid) add(l, r, p*2, d);
		else if (l > mid) add(l, r, p*2+1, d);
		else add(l, mid, p*2, d), add(mid+1, r, p*2+1, d);
		update(p);
	}
}
int find_first_right() {
	int p = 1;
	while (t[p].l < t[p].r)
		if (t[p*2].left) p = p*2+1;
		else p = p*2;
	return t[p].l;
}
int find_first_gte2() {
	int p = 1;
	while (t[p].l < t[p].r) {
		push(p);
		if (t[p*2+1].min < 2) p = p*2+1;
		else p = p*2;
	}
	return t[p].l+1;
}
int main() {
	scanf("%d%d%s", &n, &m, s);
	for (int i = 0; i < n; i++)
		sum[i] = (i == 0 ? 0 : sum[i-1]) + (s[i] == '(' ? 1 : -1);
	build(0, n-1, 1);
	for (int i = 0; i < m; i++) {
		int x, ans;
		scanf("%d", &x), x--;
		if (s[x] == '(') {
			s[x] = ')';
			flip(x);
			add(x, n-1, 1, -2);
			ans = find_first_right();
			s[ans] = '(';
			flip(ans);
			add(ans, n-1, 1, 2);
		} else {
			s[x] = '(';
			flip(x);
			add(x, n-1, 1, 2);
			ans = find_first_gte2();
			s[ans] = ')';
			flip(ans);
			add(ans, n-1, 1, -2);
		}
		printf("%d\n", ans+1);
	}
	return 0;
}
