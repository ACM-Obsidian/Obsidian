#include <cstdio>
#define P 1000000007
int fac[100001], phi[100001], a[100001], p[100001], l;
int rev(int x) {
	int n = P-2, s = 1, t = x;
	for (; n; n >>= 1, t = 1LL*t*t%P)
		if (n & 1) s = 1LL*s*t%P;
	return s;
}
int calc(int n, int m, int k) {
	int ans = 0, totn = n;
	for (int flag = 1, i = 0; n >= 0 && m >= 0 && n >= m; n -= k+1, m -= k, i++) {
		ans += 1LL*flag*totn*fac[n+i-1]%P*rev(fac[i])%P*rev(fac[m])%P*rev(fac[n-m])%P;
		if (ans < 0) ans += P;
		if (ans >= P) ans -= P;
		flag = -flag;
	}
	return ans;
}
void solve() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	if (m == 0 || m == n) {
		printf("%d\n", k>m);
		return;
	}
	int ans = 0;
	for (int i = 1; i*i <= n; i++) {
		if (!(n%i) && !(m%i)) ans = (ans + 1LL*phi[i]*calc(n/i, m/i, k)) % P;
		if (!(n%i) && i*i < n && !(m%(n/i))) ans = (ans + 1LL*phi[n/i]*calc(i, m/(n/i), k)) % P;
	}
	ans = 1LL*ans*rev(n)%P;
	printf("%d\n", ans);
}
int main() {
	fac[0] = 1;
	for (int i = 1; i <= 100000; i++) fac[i] = 1LL*fac[i-1]*i%P;
	phi[1] = 1;
	for (int i = 2; i <= 100000; i++) {
		if (!a[i]) p[l++] = i, a[i] = i, phi[i] = i-1;
		for (int j = 0; i*p[j] <= 100000; j++) {
			a[i*p[j]] = p[j];
			if (p[j] == a[i]) {
				phi[i*p[j]] = phi[i]*p[j];
				break;
			} else
				phi[i*p[j]] = phi[i]*(p[j]-1);
		}
	}
	int T;
	scanf("%d", &T);
	for (int _ = 1; _ <= T; _++)
		printf("Case #%d: ", _), solve();
	return 0;
}
