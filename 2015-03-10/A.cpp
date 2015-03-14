#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int absurdity (int x) {
	while (x % 10 == 0) x /= 10;
	int a = 0, t = x % 10;
	while (x) ++a, x /= 10;
	if (t == 5) return 2 * a - 1;
	else return 2 * a;
}

int ll[20], rr[20];

int minimum_absurdity (int x) {
	int l = (int)ceil(x * 0.95);
	int r = (int)floor(x * 1.05);
	--l;
	int tt = 0;
	while (l || r) {
		ll[tt] = l % 10, rr[tt] = r % 10;
		l /= 10, r /= 10, ++tt;
	}
	int ans = 0, tans = 0;
	for (int i = tt - 1; i >= 0; i--) {
		if (ll[i] != rr[i]) {
			if (ll[i] < 5 && 5 <= rr[i]) ans += tans + 1;
			else ans += tans + 2;
			break;
		} else {
			if (ll[i] == 0) tans += 2;
			else if (ll[i] == 5) ans += tans + 1, tans = 1;
			else ans += tans + 2, tans = 0;
		}
	}
	return ans;
}

int main () {
	freopen("absurd.in", "r", stdin);
	 freopen("absurd.out", "w", stdout);
	int kase; for (scanf("%d", &kase); kase; --kase) {
		int x; scanf("%d", &x);
		// printf("%d %d\n", absurdity(x), minimum_absurdity(x));
		printf("%s\n", absurdity(x) > minimum_absurdity(x) ? "absurd" : "not absurd");
	}
	return 0;
}
