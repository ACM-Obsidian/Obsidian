#include <cstdio>
#include <algorithm>
#define P 1000000007
int pwrmod(int a, int n, int p) {
	int t = a, s = 1;
	for (; n; n >>= 1, t = 1LL*t*t%p)
		if (n & 1) s = 1LL*s*t%p;
	return s;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		long long n, l, r, k;
		scanf("%lld%lld%lld%lld", &n, &l, &r, &k);
		if (k < n-l-r+2) printf("%d\n", (int)((k+1)%P));
		else {
		   if (k > n-l+1) k = n-l+1;
		   if (k > n-r+1) k = n-r+1;
		   printf("%d\n", pwrmod(2, (k - std::max(n-l-r+2, (long long)0)) % (P-1), P));
		}
	}
	return 0;
}
