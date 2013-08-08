#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int pent[1010], pmr;
int coef[100010];

const int P = 1000000007;
int p[100001];

int main ()
{
	pent[pmr++] = 0, coef[0] = 1;
	int ps = -1;
	for (int k = 1; k * (3 * k - 1) / 2 <= 100000; k++)
	{
		pent[pmr++] = k * (3 * k - 1) / 2;
		coef[pent[pmr - 1]] = ps;
		pent[pmr++] = k * (3 * k + 1) / 2;
		coef[pent[pmr - 1]] = ps;
		ps *= -1;
	}
	p[0] = p[1] = 1, p[2] = 2;
	for (int i = 3; i <= 100000; i++) {
		p[i] = 0;
		for (int j = 1, s = 1; j*(3*j-1)/2 <= i; j++, s = -s) {
			if (j*(3*j+1)/2 <= i) p[i] = (p[i] + s * p[i-j*(3*j+1)/2]) % P;
			p[i] = (p[i] + s * p[i-j*(3*j-1)/2]) % P;
		}
		if (p[i] < 0) p[i] += P;
	}
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		int a, b; scanf("%d %d", &a, &b);
		if (b > a) printf("%d\n", p[a]);
		else
		{
			int tt = a / b;
			int res = 0;
			for (int i = 0; i < pmr && pent[i] <= tt; i++)
			{
				int r = a - b * pent[i];
				int u = coef[pent[i]] * p[r];
				if (u < 0) u += P;
				res += u;
				if (res >= P) res -= P;
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
