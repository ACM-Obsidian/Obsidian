#include <cstdio>
#include <algorithm>
#include <vector>
int main() {
	freopen("hypercube.in", "r", stdin);
	freopen("hypercube.out", "w", stdout);
	long long x, y;
	for (int _ = 1; scanf("%I64d%I64d", &x, &y) == 2; _++) {
		std::vector<long long> ans;
		ans.push_back(x);
		while (1) {
			if (y % x) break;
			long long t = std::__gcd(y / x, x);
			if (t == 1) break;
			x *= t;
			ans.push_back(x);
			if (x == y) break;
		}
		if (x != y) 
			printf("Case #%d: No way\n", _);
		else {
			printf("Case #%d: The shortest sequence is: %I64d", _, ans[0]);
			for (int i = 1; i < ans.size(); i++)
				printf(" -> %I64d", ans[i]);
			printf("\n");
		}
	}
	return 0;
}
