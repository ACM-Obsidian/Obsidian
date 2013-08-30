#include <cstdio>
#define maxn 524288
#define P1 ((3U<<30)+1)
#define G1 5U
#define X1 12U
#define P2 ((13U<<28)+1)
#define G2 3U
#define X2 13U
#define Q 1000003U
#define uint unsigned int
uint te1[2*maxn], te2[2*maxn], tmp[maxn], a[maxn], b[maxn], a1[maxn], b1[maxn], c[maxn], t[maxn], *e;
uint power(uint n, unsigned long long k, uint r) {
	uint t = n, s = 1;
	for (; k; k >>= 1, t = 1ULL*t*t%r)
		if (k & 1) s = 1ULL*s*t%r;
	return s;
}
void prepare() {
	e = te1+maxn;
	e[0] = 1, e[1] = power(G1, (P1-1)/maxn, P1);
	for (int i = 2; i < maxn; i++) e[i] = 1ULL*e[i-1]*e[1]%P1;
	for (int i = -1; i > -maxn; i--) e[i] = e[i+maxn];
	e = te2+maxn;
	e[0] = 1, e[1] = power(G2, (P2-1)/maxn, P2);
	for (int i = 2; i < maxn; i++) e[i] = 1ULL*e[i-1]*e[1]%P2;
	for (int i = -1; i > -maxn; i--) e[i] = e[i+maxn];
}
void dft(uint *a, int N, int d, uint p) {
	for (int n = N, m; m = n/2, m >= 1; n = m, d *= 2)
		for (int i = 0; i < m; i++)
			for (int j = i; j < N; j += n) {
				uint x;
				if (a[j] > a[j+m]) x = a[j]-a[j+m];
				else x = a[j]+(p-a[j+m]);
				if (a[j] < p-a[j+m]) a[j] += a[j+m];
				else a[j] -= p-a[j+m];
				a[j+m] = 1ULL*x*e[d*i]%p;
			}
	for (int i = 0, j = 1; j < N-1; j++) {
		for (int k = N/2; k > (i ^= k); k /= 2);
		if (j < i) a[i] ^= a[j], a[j] ^= a[i], a[i] ^= a[j];
	}
}
void fft(uint *a, uint *b, uint *c, int n) {
	int k = 1; for (; k < n; k <<= 1);
	n = k;
	e = te1+maxn;
	for (int i = 0; i < n; i++) a1[i] = a[i], b1[i] = b[i];
	dft(a1, n, maxn/n, P1);
	dft(b1, n, maxn/n, P1);
	for (int i = 0; i < n; i++) t[i] = 1ULL*a1[i]*b1[i]%P1;
	dft(t, n, -maxn/n, P1);
	uint rev = P1-(P1-1)/n;
	for (int i = 0; i < n; i++) t[i] = 1ULL*t[i]*rev%P1;
	e = te2+maxn;
	for (int i = 0; i < n; i++) a1[i] = a[i], b1[i] = b[i];
	dft(a1, n, maxn/n, P2);
	dft(b1, n, maxn/n, P2);
	for (int i = 0; i < n; i++) c[i] = 1ULL*a1[i]*b1[i]%P2;
	dft(c, n, -maxn/n, P2);
	rev = P2-(P2-1)/n;
	for (int i = 0; i < n; i++) {
		c[i] = 1ULL*c[i]*rev%P2;
		uint t1 = 1ULL*t[i]*X1/P1, t2 = 1ULL*c[i]*X2/P2;
		unsigned long long x1 = 1ULL*t[i]*X1*P2-1ULL*t1*P1*P2, x2 = 1ULL*c[i]*X2*P1-1ULL*t2*P1*P2, p = 1ULL*P1*P2;
		if (x2 < x1) x2 = x2+(p-x1);
		else x2 -= x1;
		c[i] = x2%Q;
	}
}
uint A[maxn], fac[maxn], sqpow[maxn], rev[Q];
int main() {
	prepare();
	int n, B, C, D;
	scanf("%d%d%d%d", &n, &B, &C, &D);
	for (int i = 0; i < n; i++) scanf("%u", &A[i]);
	fac[0] = fac[1] = 1;
	for (int i = 2; i < n; i++) fac[i] = 1ULL*fac[i-1]*i%Q;
	rev[1] = 1;
	for (int i = 2; i < Q; i++) rev[i] = 1ULL*rev[Q%i]*(Q-Q/i)%Q;
	for (int i = 0; i < n; i++) sqpow[i] = power(C, 1ULL*i*i, Q);
	for (int i = 0; i < n; i++) a[i] = 1ULL*A[n-1-i]*fac[n-1-i]%Q;
	for (int i = 0, t = 1; i < n; i++, t = 1ULL*t*D%Q) b[i] = 1ULL*rev[fac[i]]*t%Q;
	fft(a, b, c, 2*n);
	for (int i = 0, t = 1; i < n; i++, t = 1ULL*t*B%Q) a[i] = 1ULL*rev[fac[i]]*t%Q*sqpow[i]%Q*c[n-1-i]%Q;
	for (int i = 1; i < 2*n; i++) b[i] = rev[sqpow[i<n?n-i:i-n]];
	fft(a, b, c, 3*n);
	for (int i = 0; i < n; i++) printf("%d\n", 1ULL*c[i+n]*sqpow[i]%Q);
	return 0;
}
