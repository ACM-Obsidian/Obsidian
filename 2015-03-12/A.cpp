#include <cstdio>
#include <string>
#define P 10007
char t[100001];
int a[100], f[101][513], c[513][513];
int power(int a, int n) {
	int s = 1, t = a;
	for (; n; n>>=1, t = t*t%P)
		if (n & 1) s = s*t%P;
	return s;
}
int main() {
	freopen("arrays.in", "r", stdin);
	freopen("arrays.out", "w", stdout);
	c[1][1] = 1;
	for (int i = 2; i <= 512; i++)
		for (int j = 1; j <= i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j] * j) % P;
	scanf("%[^\n]", t);
	int n = 0;
	for (; ; n++)
		if (t[n] == ']')
			break;
	n--;
	int len = 2;
	for (int i = n-1; i >= 0; i--) {
		a[i] = 1;
		int j = i+len+1;
		for (; t[j] == ','; j += len+2, a[i]++);
		len = j-i+1;
	}
	for (int i = 1; i <= 512; i++)
		f[n][i] = 1;
	int t = 512;
	for (int i = n-1; i >= 0; i--) {
		t /= a[i];
		for (int j = 1; j <= t; j++) {
			f[i][j] = 0;
			for (int k = 1; k <= j * a[i]; k++)
				f[i][j] = (f[i][j] + c[j * a[i]][k] * f[i+1][k]) % P;
		}
	}
	printf("%d\n", f[0][1]);
	return 0;
}
