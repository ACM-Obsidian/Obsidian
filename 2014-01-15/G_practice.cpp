#include <cstdio>
#include <algorithm>
struct segt {
	int cnt, delta, l, r;
	std::pair<int, int> min;
} t1[400000], t2[400000];
int l[50000], r[50000], ans[50000], hans[50000], n;
std::pair<int, int> a[100000];
void init(segt *t, int l, int r, int p) {
	t[p].l = l, t[p].r = r, t[p].min.first = 0x40000000, t[p].cnt = 0, t[p].delta = 0;
	if (l < r) {
		int mid = l+r>>1;
		init(t, l, mid, p*2), init(t, mid+1, r, p*2+1);
	}
}
void update(segt *t, int p) {
	t[p].cnt = t[p*2].cnt + t[p*2+1].cnt;
	if (t[p*2].min < t[p*2+1].min)
		t[p].min = t[p*2].min;
	else
		t[p].min = t[p*2+1].min;
}
void push(segt *t, int p) {
	t[p*2].delta += t[p].delta, t[p*2+1].delta += t[p].delta;
	t[p*2].min.first += t[p].delta, t[p*2+1].min.first += t[p].delta;
	t[p].delta = 0;
}
void ins(segt *t, int k, std::pair<int, int> x) {
	int p = 1;
	while (t[p].l < t[p].r) {
		push(t, p);
		if (k - t[p].l <= t[p].r - k) p = p*2;
		else p = p*2+1;
	}
	t[p].min = x;
	t[p].cnt = 1;
	for (p /= 2; p; p /= 2)
		update(t, p);
}
void del(segt *t, int k) {
	int p = 1;
	while (t[p].l < t[p].r) {
		push(t, p);
		if (k - t[p].l <= t[p].r - k) p = p*2;
		else p = p*2+1;
	}
	t[p].min.first = 0x40000000;
	t[p].cnt = 0;
	for (p /= 2; p; p /= 2)
		update(t, p);
}
void add(segt *t, int l, int r, int delta, int p) {
	if (t[p].l == l && t[p].r == r)
		t[p].delta += delta, t[p].min.first += delta;
	else {
		push(t, p);
		int mid = t[p].l+t[p].r>>1;
		if (r <= mid) add(t, l, r, delta, p*2);
		else if (l > mid) add(t, l, r, delta, p*2+1);
		else add(t, l, mid, delta, p*2), add(t, mid+1, r, delta, p*2+1);
		update(t, p);
	}
}
int qcnt(segt *t, int l, int r, int p) {
	if (t[p].l == l && t[p].r == r)
		return t[p].cnt;
	else {
		push(t, p);
		int mid = t[p].l+t[p].r>>1;
		if (r <= mid) return qcnt(t, l, r, p*2);
		else if (l > mid) return qcnt(t, l, r, p*2+1);
		else return qcnt(t, l, mid, p*2) + qcnt(t, mid+1, r, p*2+1);
	}
}
void qmin(segt *t, int k, std::pair<int, int> &min, int p) {
	if (t[p].cnt <= k) min = t[p].min;
	else {
		push(t, p);
		if (t[p*2].cnt >= k) qmin(t, k, min, p*2);
		else {
			qmin(t, k-t[p*2].cnt, min, p*2+1);
			if (t[p*2].min < min)
				min = t[p*2].min;
		}
	}
}
int process(int k) {
	init(t1, 0, 2*n-1, 1);
	init(t2, 0, 2*n-1, 1);
	for (int i = 0; i < n; i++)
		ins(t2, l[i], std::pair<int, int>(r[i], i));
	for (int i = 0; i < n; i++) {
		int cnt;
		std::pair<int, int> min;
		qmin(t1, n, min, 1);
		if (min.first < i-k-1) return 0;
		if (min.first == i-k-1)
			cnt = min.second - min.first;
		else
			cnt = n-i;
		qmin(t2, cnt, min, 1);
		ans[i] = min.second;
		hans[ans[i]] = i;
		del(t2, l[ans[i]]);
		int num = qcnt(t2, 0, r[ans[i]], 1);
		if (k == 0 && num > 0) return 0;
		add(t1, l[ans[i]], 2*n-1, 1, 1);
		ins(t1, r[ans[i]], std::pair<int, int>(i-num, i));
		if (i >= k) del(t1, r[ans[i-k]]);
	}
	return 1;
}
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &l[i], &r[i]), a[2*i] = std::pair<int, int>(l[i], i), a[2*i+1] = std::pair<int, int>(r[i], i+n);
	std::sort(a, a+2*n);
	for (int i = 0; i < 2*n; i++)
		if (a[i].second >= n) r[a[i].second-n] = i;
		else l[a[i].second] = i;
	int ll = 0, rr = n-1;
	while (ll < rr) {
		int mid = ll+rr>>1;
		if (process(mid)) rr = mid;
		else ll = mid+1;
	}
	process(ll);
	printf("%d\n", ll);
	for (int i = 0; i < n; i++) printf("%d %d\n", a[l[ans[i]]].first, a[r[ans[i]]].first);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
