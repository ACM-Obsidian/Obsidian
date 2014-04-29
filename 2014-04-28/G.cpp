#include <cstdio>
int n;
long long a[2000];
int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	scanf("%d", &n);
	long long x = 0;
	for (int i = 0; i < n; i++) scanf("%lld", &a[i]), x ^= a[i];
	if (x == 0) puts("Draw");
	else {
		int highest = 63 - __builtin_clzll(x);
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if (a[i]&1LL<<highest) cnt++;
		if (cnt%4 == 1 || !(n&1)) puts("First");
		else puts("Second");
	}
	return 0;
}
