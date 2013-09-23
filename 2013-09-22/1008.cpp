#include <cstdio>
int a[4], b[4];
void mul(int *a, int *b, int k) {
	int c[4];
	c[0] = (1LL*a[0]*b[0]+1LL*a[1]*b[2])%k;
	c[1] = (1LL*a[0]*b[1]+1LL*a[1]*b[3])%k;
	c[2] = (1LL*a[2]*b[0]+1LL*a[3]*b[2])%k;
	c[3] = (1LL*a[2]*b[1]+1LL*a[3]*b[3])%k;
	a[0] = c[0], a[1] = c[1], a[2] = c[2], a[3] = c[3];
}
int main() {
	int k, l;
	for (; scanf("%d%d", &k, &l) != EOF; ) {
		a[0] = 2*l%k, a[1] = k-l%k;
		if (a[1] == k) a[1] = 0;
		a[2] = 1, a[3] = 0;
		b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1;
		for (int i = k-1; i; i>>=1, mul(a, a, k))
			if (i&1) mul(b, a, k);
		printf("%d\n", int((2LL*l*b[0]+2LL*b[1]+k-1)%k));
	}
	return 0;
}
