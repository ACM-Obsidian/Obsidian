#include <cstdio>
int n, t, p[1000000];
long long f(int i) {
	int l = 1, r = n;
	while (l < r) {
		int mid = l+r>>1;
		long long s = 0;
		for (int j = 1; j <= i; j++) {
			s += (mid-1)/j+1;
			if (s >= n) break;
		}
		if (s < n) l = mid+1;
		else r = mid;
	}
	long long sum = 0;
	int u = 0;
	for (int j = 1; j <= i; j++) {
		int tmp = (l-1+j-1)/j;
		sum += 1LL*(2+1LL*j*(tmp-1))*tmp/2;
		u += tmp;
	}
	sum += 1LL*(n-u)*l + 1LL*(i-1)*t;
	int v = n-u; u = 0;
	for (int j = 1; j < i; j++) {
		u += (l-1+j-1)/j;
		if (v && !((l-1)%j)) v--, u++;
		p[j-1] = u;
	}
	return sum;
}
int main() {
	scanf("%d%d", &n, &t);
	int l = 1, r = n;
	while (l+2 < r) {
		int m1 = l+r>>1, m2 = m1+1;
		if (f(m1) < f(m2)) r = m2;
		else l = m1;
	}
	long long ans = f(l); int ansi = l;
	for (int i = l+1; i <= r; i++) {
		long long tmp = f(i);
		if (tmp < ans) ans = tmp, ansi = i;
	}
	f(ansi);
	printf("%lld\n%d\n", ans, ansi-1);
	for (int i = 0; i < ansi-1; i++) printf("%d%c", p[i], " \n"[i == ansi-2]);
	return 0;
}
