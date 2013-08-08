#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
#define pi 3.14159265358979324
struct point {
	double x, y;
} a[1000];
struct rec {
	double arc;
	int id;
} b[1000];
int n, m, id[1000][1000], succ[1000000], u[1000000];
int cmp(rec a, rec b) {
	return a.arc < b.arc;
}
double dist(double a, double b) {
	if (a < b) return b-a;
	else return b-a+2*pi;
}
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
	m = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j) id[i][j] = m++;
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = 0; j < n; j++)
			if (j != i) {
				b[k].arc = atan2(a[j].y-a[i].y, a[j].x-a[i].x);
				b[k++].id = j;
			}
		std::sort(b, b+k, cmp);
		int t = 0;
		for (int j = k-1; j >= 0; j--) {
			double arc_ = (b[j].arc < 0 ? b[j].arc+pi : b[j].arc-pi);
			t = (t+1)%k;
			for (; dist(b[t].arc, arc_) < dist(b[(t+k-1)%k].arc, arc_); t = (t+k-1)%k);
			t = (t+k-1)%k;
			succ[id[i][b[j].id]] = (dist(b[(j+k-1)%k].arc, b[j].arc) < dist(b[t].arc, arc_) ? id[b[(j+k-1)%k].id][i] : id[b[t].id][i]);
		}
	}
	long long ans = 0;
	for (int i = 0; i < n*(n-1); i++) u[i] = 0;
	for (int i = 0; i < n*(n-1); i++)
		if (!u[i]) {
			int cnt = 1;
			u[i] = 1;
			for (int j = succ[i]; j != i; j = succ[j]) cnt++, u[j] = 1;
			ans += 1LL * cnt * cnt;
		}
	long long ansd = n*(n-1), t = std::__gcd(ans, ansd);
	ans /= t, ansd /= t;
	if (ansd > 1) printf("%I64d/%I64d\n", ans, ansd);
	else printf("%I64d\n", ans);
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}

