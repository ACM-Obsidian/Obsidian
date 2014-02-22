#include <cstdio>
int a[60];
int main() {
	freopen("great.in", "r", stdin);
	freopen("great.out", "w", stdout);
	long long n; int k;
	scanf("%I64d%d", &n, &k);
	int l = 0;
	for (; n; n /= k, l++)
		a[l] = n % k;
	if (l&1) l++;
	int i = l;
	for (; i >= 0 && !a[i-1]; i -= 2);
	if (i > 0)
		for (i -= 2; i >= 0; i -= 2)
			a[i] = k-1;
	long long ans = 0;
	for (i = l; i >= 0; i -= 2)
		ans = ans * k + a[i];
	printf("%I64d\n", ans+1);
	return 0;
}
