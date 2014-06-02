#include <cstdio>
#include <algorithm>
#include <vector>
#define P 7340033
#define Q 2187
#define maxn 1048576
typedef std::vector<int> func;
int tmp[2*maxn], *e = tmp+maxn, wa[maxn], wb[maxn];
int pwr(int x, int n) {
	int s = 1, t = x;
	for (; n; n>>=1, t = 1LL*t*t%P)
		if (n & 1) s = 1LL*s*t%P;
	return s;
}
void prepare() {
	e[0] = 1, e[1] = Q;
	for (int i = 2; i < maxn; i++)
		e[i] = 1LL*e[i-1]*Q%P;
	for (int i = 1; i < maxn; i++)
		e[-i] = e[maxn-i];
}
void dft(int *a, int N, int f) {
	int d = maxn / N * f;
	for (int n = N, m; m = n / 2, m >= 1; n = m, d *= 2)
		for (int i = 0; i < m; i++)
			for (int j = i, x; j < N; j += n)
				x = (a[j] - a[j+m] + P) % P, a[j] = (a[j] + a[j+m]) % P, a[j+m] = 1LL * x * e[d*i] % P;
	for (int i = 0, j = 1; j < N-1; j++) {
		for (int k = N/2; k > (i ^= k); k /= 2);
		if (j < i) std::swap(a[i], a[j]);
	}
}
void mul(func a, func b, func &c) {
	int t = a.size()+b.size()-1, n = 1;
	while (n < t) n *= 2;
	for (int i = 0; i < n; i++)
		wa[i] = (i < a.size() ? a[i] : 0);
	for (int i = 0; i < n; i++)
		wb[i] = (i < b.size() ? b[i] : 0);
	dft(wa, n, 1);
	dft(wb, n, 1);
	for (int i = 0; i < n; i++)
		wa[i] = 1LL * wa[i] * wb[i] % P;
	dft(wa, n, -1);
	c.resize(t);
	int k = pwr(n, P-2);
	for (int i = 0; i < t; i++) c[i] = 1LL * wa[i] * k % P;
}
void rev(func a, func &b) {
	if (a.size() == 1) {
		b.resize(1); b[0] = pwr(a[0], P-2);
	} else if (a.size() == 2) {
		b.resize(2); b[1] = pwr(a[1], P-2), b[0] = (P - 1LL * b[1] * b[1] % P) * a[0] % P;
	} else {
		int n = a.size()-1, t = (n+1)/2;
		func c, d, tmp1;
		for (int i = 0; i <= t; i++) c.push_back(a[i+n-t]);
		rev(c, d);
		for (int i = 0; i < n-t; i++) tmp1.push_back(0);
		for (int i = 0; i <= t; i++) tmp1.push_back(2*d[i]);
		mul(d, d, d);
		mul(d, a, d);
		for (int i = 0; i <= n; i++) d[i] = (tmp1[i] - d[i+2*t] + P) % P;
		d.resize(n+1);
		b = d;
	}
}
void div(func a, func b, func &c) {
	func a1, b1;
	int n = a.size()-b.size(), m1 = a.size()-1, n1 = b.size()-1;
	for (int i = 0; i <= n; i++)
		b1.push_back(i+n1-n >= 0 ? b[i+n1-n] : 0);
	for (int i = 0; i <= 2*n; i++)
		a1.push_back(i+m1-2*n >= 0 ? a[i+n1-n] : 0);
	rev(b1, b1);
	mul(a1, b1, a1);
	c.resize(n+1);
	for (int i = 0; i <= n; i++) c[i] = a1[i+2*n];
}
int p[maxn];
int main() {
	prepare();
	int m, n; scanf("%d%d", &m, &n), m--;
	for (int i = 0; i <= n; i++) scanf("%d", &p[i]);
	if (p[0] == 0) {
		puts("The ears of a dead donkey");
		return 0;
	}
	func a;
	for (int i = 0; i <= m; i++) a.push_back(m-i > n ? 0 : p[m-i]);
	rev(a, a);
	for (int i = m; i >= 0; i--) printf("%d%c", a[i], " \n"[i == 0]);
	return 0;
}
