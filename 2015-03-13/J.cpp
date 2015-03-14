#include <cstdio>
#include <complex>
#include <cmath>
const double pi = 3.14159265358979324;
typedef std::complex<double> complex;
complex a[2048][2048], b[2048][2048], tmp[2048][2048], ebuf[4096], *e = ebuf + 2048;
int n, h, w;
void trans(int n, int d, int x, int y, complex a[2048][2048], complex tmp[2048][2048]) {
	if (n == 1) return;
	int m = n/2;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			tmp[x+i][y+j] = a[x+i*2][y+j*2], tmp[x+i+m][y+j] = a[x+i*2+1][y+j*2], tmp[x+i][y+j+m] = a[x+i*2][y+j*2+1], tmp[x+i+m][y+j+m] = a[x+i*2+1][y+j*2+1];
	trans(m, d*2, x, y, tmp, a), trans(m, d*2, x+m, y, tmp, a), trans(m, d*2, x, y+m, tmp, a), trans(m, d*2, x+m, y+m, tmp, a);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int k = (i < m ? i : i-m), l = (j < m ? j : j-m);
			a[x+i][y+j] = tmp[x+k][y+l] + e[d*i]*tmp[x+k+m][y+l] + e[d*j]*tmp[x+k][y+l+m] + e[d*i]*e[d*j]*tmp[x+k+m][y+l+m];
		}
}
int main() {
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	scanf("%d%d\n", &h, &w);
	n = 2;
	for (; n < 2*h || n < 2*w; n *= 2);
	e[0] = complex(1, 0);
	for (int i = 1; i < n; i++) {
		if ((i & -i) == i) e[i] = complex(cos(2 * pi * i / n), sin(2 * pi * i / n));
		else e[i] = e[i - (i & -i)] * e[i & -i];
		e[i-n] = e[i];
	}
	int cnt = 0;
	for (int i = 0; i < h; scanf("\n"), i++)
		for (int j = 0; j < w; j++) {
			char ch = getchar();
			if (ch == '1') cnt++;
			b[i][j] = (ch == '1' ? complex(1, 0) : complex(0, 0));
		}
	trans(n, 1, 0, 0, b, tmp);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = b[i][j] * b[(n-i)%n][(n-j)%n];
	trans(n, -1, 0, 0, a, tmp);
	double p = 0;
	for (int i = -h+1; i < h; i++)
		for (int j = -w+1; j < w; j++)
			if (i || j)
				p += sqrt(1.0 * i * i + 1.0 * j * j) * a[(n-i)%n][(n-j)%n].real() / (n * n);
	p *= 3.0 / cnt / (cnt - 1);
	printf("%.8lf\n", p);
	return 0;
}
