#include <cstdio>
#include <cstring>
struct rec {
	int x, y;
} q[1001000];
int f[1001][1000][2];
int main() {
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n;
	scanf("%d", &n);
	memset(f, -1, sizeof f);
	for (int i = 1; i < 10; i++)
		f[i][i%n][0] = i, f[i][i%n][1] = 0, q[i-1].x = i, q[i-1].y = i%n;
	int l = 0, r = 9;
	for (; l < r; l++) {
		if (q[l].x == n && q[l].y == 0) break;
		int x = q[l].x, y = q[l].y;
		for (int i = 0; i < 10; i++)
			if (x+i <= n && f[x+i][(y*10+i)%n][0] == -1) {
				f[x+i][(y*10+i)%n][0] = i, f[x+i][(y*10+i)%n][1] = y;
				q[r].x = x+i, q[r].y = (y*10+i)%n, r++;
			}
	}
	int ans[10000], ll = 0;
	for (int x = q[l].x, y = q[l].y, t; x; t = f[x][y][1], x -= f[x][y][0], y = t)
		ans[ll++] = f[x][y][0];
	for (int i = ll-1; i >= 0; i--) putchar(ans[i]+48); puts("");
	return 0;
}
