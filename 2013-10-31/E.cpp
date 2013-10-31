#include <cstdio>
int a[200], ans, sum[400], tmp[400], c[200][200][60];
void solve(int l, int r) {
	if (l == r) return;
	int mid = l+r>>1;
	int tmpx = a[r-1];
	for (int i = r-1; i > mid; i--) a[i] = a[i-1];
	a[mid] = tmpx;
	ans += r-l;
	for (int i = 0; i < 400; i++) tmp[i] = 0;
	for (int i = 0; i < 400; i++)
		for (int j = 0, g = 0; j < 60; j++)
			if (i+j < 400) {
				tmp[i+j] += sum[i]*c[r-l-1][mid-l][j]+g;
				g = tmp[i+j] / 10, tmp[i+j] %= 10;
			}
	for (int i = 0; i < 400; i++) sum[i] = tmp[i];
	solve(l, mid), solve(mid+1, r);
}
int main() {
	freopen("merge.in","r",stdin);
	freopen("merge.out","w",stdout);
	int n;
	scanf("%d", &n);
	c[0][0][0] = 2;
	for (int i = 1; i < n; i++) {
		c[i][0][0] = c[i][i][0] = 2;
		for (int j = 1; j < i; j++) {
			for (int k = 0, g = 0; k < 60; k++)
				c[i][j][k] = c[i-1][j][k]+c[i-1][j-1][k]+g, c[i][j][k] >= 10 ? (c[i][j][k] -= 10, g = 1) : g = 0;
		}
	}
	for (int i = 0; i < n; i++) a[i] = i;
	sum[0] = 1;
	solve(0, n-1);
	printf("%d\n", ans);
	for (int i = 0; i < n-1; i++) printf("%d ", a[i]+1);
	printf("%d\n", a[n-1]+1);
	int i = 399;
	for (; i; i--) if (sum[i]) break;
	for (; i >= 0; i--) putchar(sum[i]+48); puts("");
	return 0;
}
