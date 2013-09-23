#include <cstdio>
#include <cmath>
#include <complex>
#define maxn 262144
#define maxm 80001
const double pi = 3.14159265358979324;
typedef std::complex<double> complex;
complex w[2*maxn], wx[maxn], wy[maxn], tmp[maxn], *e;
int a[maxn], p[maxn], b[maxn], c[maxn], f1[maxn], f2[maxn], f3[maxn], l;
void pre() {
	e = w+maxn;
	e[0] = complex(1, 0);
	for (int i = 1; i < maxn; i *= 2)
		e[i] = complex(cos(2*pi*i/maxn), sin(2*pi*i/maxn));
	for (int i = 1; i < maxn; i++)
		if ((i&-i) != i) e[i] = e[i-(i&-i)] * e[i&-i];
	for (int i = 1; i < maxn; i++)
		e[-i] = e[maxn-i];
}
void dft(int l, int n, complex *a, complex *b, int d) {
	if (n == 1) return;
	int m = n>>1;
	for (int i = 0; i < m; i++)
		b[l+i] = a[l+2*i], b[l+m+i] = a[l+2*i+1];
	dft(l, m, b, a, d*2), dft(l+m, m, b, a, d*2);
	for (int i = 0; i < m; i++)
		a[l+i] = b[l+i] + e[d*i]*b[l+m+i];
	for (int i = m; i < n; i++)
		a[l+i] = b[l+i-m] + e[d*i]*b[l+i];
}
void dft(int *a, complex *b) {
	for (int i = 0; i < maxn; i++) b[i] = complex(a[i], 0);
	dft(0, maxn, b, tmp, 1);
}
void idft(complex *a, int *b) {
	dft(0, maxn, a, tmp, -1);
	for (int i = 0; i < maxn; i++) b[i] = int(a[i].real()/maxn+0.5);
}
int main() {
	pre();
	for (int i = 2; i < maxm; i++) {
		if (a[i] == 0) p[l++] = i, a[i] = i, b[i] = 1, f1[i] = 1;
		for (int j = 0; j < l && i*p[j] < maxm; j++) {
			a[i*p[j]] = p[j];
			if (p[j] == a[i]) break;
		}
	}
	dft(b, wx);
	for (int i = 0; i < maxn; i++) wy[i] = wx[i]*wx[i];
	idft(wy, f2);
	for (int i = 0; i < maxm; i++) {
		if (i%2 == 0 && a[i/2] == i/2) f2[i]++;
		f1[i] += f2[i]/2;
	}
	for (int i = maxm; i < maxn; i++) f2[i] = 0;
	dft(f2, wy);
	for (int i = 0; i < maxn; i++) wy[i] *= wx[i];
	idft(wy, f2);
	for (int i = 0; i < l; i++)
		if (2*p[i] < maxm) c[2*p[i]] = 1;
	dft(c, wy);
	for (int i = 0; i < maxn; i++) wy[i] *= wx[i];
	idft(wy, f3);
	for (int i = 0; i < maxm; i++) {
		f2[i] += 2*f3[i];
		if (i%3 == 0 && a[i/3] == i/3) f2[i] += 3;
		f1[i] += f2[i]/6;
	}
	for (int i = 0; i < maxn; i++) c[i] = 0;
	for (int i = 0; i < l; i++)
		for (int j = i; p[j] <= (maxm-1)/p[i]; j++)
			c[p[i]*p[j]] = 1, f1[p[i]*p[j]]++;
	dft(c, wy);
	for (int i = 0; i < maxn; i++) wy[i] *= wx[i];
	idft(wy, f2);
	for (int i = 0; i < maxm; i++) f1[i] += f2[i];
	for (int i = 0; i < l; i++)
		for (int j = i; p[j] <= (maxm-1)/p[i]; j++)
			for (int k = j; p[k] <= (maxm-1)/p[i]/p[j]; k++)
				f1[p[i]*p[j]*p[k]]++;
	for (int x; scanf("%d", &x) != EOF; printf("%d\n", f1[x]));
	return 0;
}
