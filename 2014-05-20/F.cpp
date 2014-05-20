#include <cstdio>
#include <vector>
#include <algorithm>
struct point {
	long long x, y;
	point(long long _x, long long _y)
		: x(_x), y(_y) { }
};
point operator - (point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}
long long operator * (point a, point b) {
	return a.x * b.x + a.y * b.y;
}
long long operator % (point a, point b) {
	return a.x * b.y - a.y * b.x;
}
int parallel(point a, point b) {
	return a * a == 0 || b * b == 0 || a % b == 0;
}
std::vector<point> t;
long long f[3001][3000];
int a[3000], sum[3001], n;
std::vector<std::pair<int, int> > k;
int cmp(point a, point b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
void convex_gen(std::vector<point> &a) {
	std::vector<point> q, t(a);
	std::sort(t.begin(), t.end(), cmp);
	q.push_back(t[0]);
	if (t.size() > 1) q.push_back(t[1]);
	for (int i = 2; i < t.size(); i++) {
		while (q.size() > 1) {
			point p1 = t[i] - q[q.size()-1], p2 = q[q.size()-1] - q[q.size()-2];
			if (p1 % p2 < 0 || parallel(p1, p2)) q.pop_back();
			else break;
		}
		q.push_back(t[i]);
	}
	a = q;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sum[0] = 0;
	for (int i = 0; i < n; i++) sum[i+1] = sum[i] + a[i];
	for (int i = 1; i <= n; i++) f[i][0] = 0;
	for (int i = 1; i < n; i++) {
		t.clear();
		for (int j = 0; j < i; j++)
			t.push_back(point(sum[i] - sum[j], f[i][j]));
		convex_gen(t);
		k.clear();
		for (int j = i+1; j <= n; j++)
			k.push_back(std::make_pair(sum[j] - sum[i], j));
		std::sort(k.begin(), k.end());
		int p = 0;
		for (int j = 0; j < k.size(); j++) {
			while (p+1 < t.size() && t[p+1].y - t[p].y > (t[p+1].x - t[p].x) * -k[j].first) p++;
			f[k[j].second][i] = t[p].y + t[p].x * k[j].first;
		}
	}
	long long ans = -1;
	for (int i = 0; i < n; i++)
		if (f[n][i] > ans) ans = f[n][i];
	printf("%lld\n", ans);
	return 0;
}
