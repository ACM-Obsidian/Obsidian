#include <cstdio>
#include <cmath>
#include <algorithm>
const long double pi = 3.14159265358979324;
long double ct[300];
int cmp(long double a, long double b) {
	return a > b;
}
int main() {
	for (int k = 143; k <= 150; k++) {
		for (int i = 1; i < 2*k; i++)
			ct[i] = cos(0.5 * pi * i / k) / sin(0.5 * pi * i / k);
		int cnt = 0;
		for (int a = 1; a < 2*k; a++)
			for (int b = 1; a+b < 2*k; b++)
				for (int c = 1; b+c < 2*k; c++)
					for (int d = 1; c+d < 2*k && a+d < 2*k; d++) {
						long double th = (ct[a] * ct[c] - ct[b] * ct[d]) / (ct[a] + ct[b] + ct[c] + ct[d]);
						int p = std::lower_bound(ct+1, ct+2*k, th, cmp) - ct;
						if (p < 2*k && fabs(ct[p] - th) < 1e-12) cnt++;
						else if (p > 1 && fabs(ct[p-1] - th) < 1e-12) cnt++;
					}
		printf("%d %d\n", k, cnt);
	}
	return 0;
}
