#include <cstdio>
#include <cmath>
#include <complex>
const double pi = 3.14159265358979324;
typedef std::complex<double> complex;
complex e[1024], bf[1024], hf[1024], a[1024];
double b[1024], h[1024];
void solve() {
	int n; scanf("%d", &n); n = 1<<n;
	for (int i = 0; i < n; i++) scanf("%lf", &b[i]);
	for (int i = 0; i < n; i++) scanf("%lf", &h[i]);
	e[0] = 1;
	for (int i = 1; i < n; i++)
		if ((i & -i) == i) e[i] = complex(cos(2 * pi * i / n), sin(2 * pi * i / n));
		else e[i] = e[i - (i & -i)] * e[i & -i];
	for (int i = 0; i < n; i++) {
		bf[i] = 0;
		for (int j = 0; j < n; j++)
			bf[i] += b[j] * e[(i*j)%n];
		hf[i] = 0;
		for (int j = 0; j < n; j++)
			hf[i] += h[j] * e[(i*j)%n];
	}
	for (int i = 0; i < n; i++) bf[i] = hf[(n-i)%n] / bf[i];
	for (int i = 0; i < n; i++) {
		a[i] = 0;
		for (int j = 0; j < n; j++)
			a[i] += bf[j] * e[(i*j)%n];
		a[i] /= n;
	}
	for (int i = 0; i < n; i++) printf("%.2lf%c", a[i].real(), " \n"[i == n-1]);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
