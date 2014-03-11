#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>
#define MAX_VAL 10000000000LL
struct func {
	long long a, b, c;
	func(): a(1), b(0), c(0) {}
};
func operator + (func a, func b) {
	func c;
	c.a = b.a * a.a, c.b = b.a * a.b + b.b, c.c = b.a * a.c + b.c;
	return c;
}
func t[1000001];
struct rec {
	int start;
	long long init, l, r;
};
bool operator < (rec a, rec b) {
	return a.r < b.r;
}
std::deque<rec> q;
std::vector<rec> res;
int n;
char tmp[5];
void insert(int idx, func f) {
	for (; idx <= n; idx += idx & -idx)
		t[idx] = t[idx] + f;
}
func query(int idx) {
	func f;
	for (; idx; idx -= idx & -idx)
		f = f + t[idx];
	return f;
}
void solve() {
	long long min, max;
	scanf("%d%lld%lld", &n, &min, &max);
	q.clear();
	for (int i = 1; i <= n; i++) t[i].a = 1, t[i].b = t[i].c = 0;
	rec tmp_rec; tmp_rec.start = 0, tmp_rec.init = 0, tmp_rec.l = 1, tmp_rec.r = MAX_VAL;
	q.push_back(tmp_rec);
	func tmp_func;
	for (int i = 0; i < n; i++) {
		char op; long long val;
		scanf(" %c%lld", &op, &val);
		switch (op) {
			case '+': tmp_func.a = 1, tmp_func.b = 0, tmp_func.c = val; break;
			case '-': tmp_func.a = 1, tmp_func.b = 0, tmp_func.c = -val; break;
			case '*': tmp_func.a = val, tmp_func.b = 0, tmp_func.c = 0; break;
			case '@': tmp_func.a = 1, tmp_func.b = val, tmp_func.c = 0; break;
		}
		insert(n-i, tmp_func);
		while (1) {
			if (q.size() == 0) {
				tmp_rec.l = 1, tmp_rec.r = MAX_VAL;
				tmp_rec.start = i+1, tmp_rec.init = min;
				q.push_front(tmp_rec);
				break;
			}
			tmp_rec = q.front();
			tmp_func = query(n-tmp_rec.start);
			if (tmp_rec.init == 0) tmp_func.b += tmp_func.a;
			if (tmp_func.b * tmp_rec.r + tmp_func.a * tmp_rec.init + tmp_func.c <= min)
				q.pop_front();
			else if (tmp_func.b * tmp_rec.l + tmp_func.a * tmp_rec.init + tmp_func.c <= min) {
				long long midp = (min - tmp_func.a * tmp_rec.init - tmp_func.c) / tmp_func.b;
				tmp_rec.l = midp + 1;
				q.pop_front(); q.push_front(tmp_rec);
				tmp_rec.l = 1, tmp_rec.r = midp;
				tmp_rec.start = i+1, tmp_rec.init = min;
				q.push_front(tmp_rec);
				break;
			} else {
				if (tmp_rec.l > 1) {
					tmp_rec.r = tmp_rec.l - 1, tmp_rec.l = 1;
					tmp_rec.start = i+1, tmp_rec.init = min;
					q.push_front(tmp_rec);
				}
				break;
			}
		}
		while (1) {
			if (q.size() == 0) {
				tmp_rec.l = 1, tmp_rec.r = MAX_VAL;
				tmp_rec.start = i+1, tmp_rec.init = max;
				q.push_back(tmp_rec);
				break;
			}
			tmp_rec = q.back();
			tmp_func = query(n-tmp_rec.start);
			if (tmp_rec.init == 0) tmp_func.b += tmp_func.a;
			if (tmp_func.b * tmp_rec.l + tmp_func.a * tmp_rec.init + tmp_func.c >= max)
				q.pop_back();
			else if (tmp_func.b * tmp_rec.r + tmp_func.a * tmp_rec.init + tmp_func.c >= max) {
				long long midp = (max - tmp_func.a * tmp_rec.init - tmp_func.c + tmp_func.b-1) / tmp_func.b;
				tmp_rec.r = midp - 1;
				q.pop_back(); q.push_back(tmp_rec);
				tmp_rec.l = midp, tmp_rec.r = MAX_VAL;
				tmp_rec.start = i+1, tmp_rec.init = max;
				q.push_back(tmp_rec);
				break;
			} else {
				if (tmp_rec.r < MAX_VAL) {
					tmp_rec.l = tmp_rec.r + 1, tmp_rec.r = MAX_VAL;
					tmp_rec.start = i+1, tmp_rec.init = max;
					q.push_back(tmp_rec);
				}
				break;
			}
		}
	}
	res.clear();
	while (q.size() > 0)
		res.push_back(q.front()), q.pop_front();
	int m; scanf("%d", &m);
	long long ans = 0;
	while (m--) {
		long long t; scanf("%lld", &t);
		tmp_rec.r = t;
		int idx = std::lower_bound(res.begin(), res.end(), tmp_rec) - res.begin();
		tmp_rec = res[idx];
		tmp_func = query(n-tmp_rec.start);
		if (tmp_rec.init == 0) tmp_func.b += tmp_func.a;
		ans += tmp_func.b * t + tmp_func.a * tmp_rec.init + tmp_func.c;
	}
	printf("%lld\n", ans);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
