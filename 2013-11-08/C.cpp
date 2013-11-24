#include <cstdio>
#define P 1000000007
int p[15], a[15], sum[15], sum2[15], pow[15];
void solve() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i], &a[i]);
		pow[i] = 1, sum[i] = 0;
		for (int j = 0; j < a[i]; j++)
			sum[i] = (sum[i]+pow[i])%P, pow[i] = 1LL*pow[i]*p[i]%P;
		sum2[i] = (sum[i]+pow[i])%P;
	}
	int ans = 0;
	for (int i = 0; i < 1<<n; i++) {
		int cur = 1, cnt = 0, num = 1;
		for (int j = 0; j < n; j++)
			if (i & 1<<j) cur = 1LL*cur*sum[j]%P, cnt++, num = 1LL*num*a[j]%P;
			else cur = 1LL*cur*sum2[j]%P, num = 1LL*num*(a[j]+1)%P;
		cur = 1LL*cur*num%P*2%P;
		if (cnt&1) ans = (ans-cur+P)%P;
		else ans = (ans+cur)%P;
	}
	int x = 1;
	for (int i = 0; i < n; i++) x = 1LL*x*pow[i]%P;
	x = 1LL*x*2%P;
	ans = (ans-x+P)%P;
	if (ans&1) ans += P;
	ans >>= 1;
	ans = (ans+x)%P;
	printf("%d\n", ans);
}
int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= T; printf("Case %d: ", i), solve(), i++);
	return 0;
}
