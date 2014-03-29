#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 5010, mod = 1000000007;

struct Point {
	int x, y;
	Point operator -(const Point& oth) const {
		Point ret = *this;
		ret.x -= oth.x, ret.y -= oth.y;
		return ret;
	}
	Point operator +(const Point& oth) const {
		Point ret = *this;
		ret.x += oth.x, ret.y += oth.y;
		return ret;
	}
	long long operator %(const Point& oth) const {
		return (long long)x * oth.y - (long long)y * oth.x;
	}
}a[MAXN], b[MAXN];

int n, m;

long long f[MAXN], g[MAXN];int last[MAXN];

inline int check(int l, int r) {
	for (int i = 1; i <= m; i++) if (((b[i] - a[l]) % (a[r] - a[l])) < 0) return false;
	return true;
}

inline int Dfs(int u) {
	if (!check(n, u)) return 0;
	g[u - 1] = 0; g[u] = f[u] = 1;
	for (int i = u + 1; i <= n; i++) {
		int left = max(u, last[i] > i ? 1 : last[i]);
		f[i] = (g[i - 1] - g[left - 1]) % mod;
		g[i] = (g[i - 1] + f[i]) % mod;
	}
	long long t = max(u, last[u]);
	long long res = g[n] - g[t - 1];
	long long tmp = Dfs(u + 1);
	return (res + tmp) % mod;
}

int main(void) {
	freopen("drawing.in", "r", stdin);
	freopen("drawing.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if (m == 0) {
		int Ans = 1;
		for (int i = 1; i <= n; i++) Ans = 2ll * Ans  % mod;
		Ans = (Ans - n) % mod;
		long long C = 1ll * n * (n - 1) / 2;
		C %= mod;
		Ans = (Ans - C - 1) % mod;
		if (Ans < 0) Ans += mod;
		printf("%d\n", Ans);
		return 0;
	}
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	for (int i = 1; i <= m; i++) scanf("%d%d", &b[i].x, &b[i].y);
	if (((a[2] - a[1]) % (a[3] - a[1])) > 0) {
		reverse(a + 1, a + n + 1);
	}
	for (int i = 1; i <= n; i++) {
		int l = 1, r = i - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid, i)) r = mid - 1; else l = mid + 1;
		}
		last[i] = l;
		if (last[i] == 1) {
			l = i + 1, r = n;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (check(mid, i)) r = mid - 1; else l = mid + 1;
			}
			last[i] = l;
			if (last[i] == n + 1) last[i] = 1;
		}
	}
	int Ans = Dfs(1);
	if (Ans < 0) Ans += mod;
	printf("%d\n", Ans);
	return 0;
}

