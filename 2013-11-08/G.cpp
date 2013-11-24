#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

const int MAXN = 30010;

int a[MAXN], n, D, P;

inline void ex_gcd(double a0, double a1, double a2, double a3, double &x, double &y) {
	if (a0 == 0 && a1 == 0 && a2 == 0 && a3 == 0) {
		x = 1, y = 1; return;
	}
	double det = a0 * a2 - a1 * a1;
	if (det == 0) {
		x = 0, y = a1/a0;
		return;
	}
	x = (a2 * a2 - a1 * a3) / det;
	y = (-a2 * a1 + a3 * a0) / det;
	
//	printf("%lf %lf %lf %lf %lf %lf\n", a0, a1, a2, a3, x, y);
}

double b[MAXN];

string st;

int main(void) {
	// freopen("in", "r", stdin);
	while (getline(cin, st)) {
		n = 0; int tmp; istringstream fim(st); while (fim >>tmp) a[++n] = tmp;
		D = a[1], P = a[2]; D++;
		// for (int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
		int j = D + 2;
		double x, y;
		for (int i = 1; i <= n; i++) b[i] = a[i];
		ex_gcd(b[n - 3], b[n - 2], b[n - 1], b[n], x, y);
		for (int i = 3; i <= D + 2; i++) {
			if (i > n)
				b[i] = x * b[i - 2] + y * b[i - 1];
//			printf("%lf\n", b[i]);
			if (b[i] > P + 1e-8) {j = i - 1; break;}
		}
		if (j == D + 2 && b[D + 2] + 1e-8 < P) puts("The spider may fall!"); else
			if (j == 2) puts("The spider is going to fall!"); else
				printf("%d\n", D - j + 2);
	}
	return 0;
}
