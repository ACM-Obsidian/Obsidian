#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 2000;

int a[MAXN], b[MAXN], A, B, n;
int A1, Aw1, A2, Aw2, B1, Bw1, B2, Bw2;

inline double Cal(int x, int y) {
	return (x ? (double) A / a[x] : 0) + (y ? (double) B / b[y] : 0);
}

int main(void) {
	freopen("oil.in", "r", stdin);
	freopen("oil.out", "w", stdout);
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i <= n; i++) scanf("%d %d", a + i, b + i);
	A1 = A2 = B1 = B2 = ~0U>>1;
	for (int i = 1; i <= n; i++) {
		if (a[i] < A1) {
			A2 = A1, Aw2 = Aw1;
			A1 = a[i], Aw1 = i;
		} else
		if (a[i] < A2) {
			A2 = a[i], Aw2 = i;
		}
		if (b[i] < B1) {
			B2 = B1, Bw2 = Bw1;
			B1 = b[i], Bw1 = i;
		} else
		if (b[i] < B2) {
			B2 = b[i], Bw2 = i;
		}
	}
	if (Aw1 != Bw1) {
		printf("%.2lf\n", Cal(Aw1, Bw1));
	} else {
		printf("%.2lf\n", max(Cal(Aw1, Bw2), Cal(Aw2, Bw1)));
	}
	return 0;
}

