#include <cstdio>
#include <cstring>
char a[16][14][14], ans[20][20];
int k, w, h, n, f[16];
int put(int k, int i, int j) {
	for (int p = 0; p < 3*h-2; p++)
		for (int q = 0; q < 3*w-2; q++)
			if (a[k][p][q] != '.') {
				int x = i*h+p-(h-1), y = j*w+q-(w-1);
				if (x < 0 || x > n*h || y < 0 || y > n*w || ans[x][y] != 0)
					return 0;
				ans[x][y] = a[k][p][q];
			}
	return 1;
}
int dfs(int k) {
	if (k == n*n) return 1;
	char tmp[20][20];
	memcpy(tmp, ans, sizeof ans);
	switch (f[k]) {
		case 0:
			if (put(k, 0, 0) && dfs(k+1)) return 1;
			memcpy(ans, tmp, sizeof ans);
			break;
		case 1:
			if (put(k, 0, n-1) && dfs(k+1)) return 1;
			memcpy(ans, tmp, sizeof ans);
			break;
		case 2:
			if (put(k, n-1, n-1) && dfs(k+1)) return 1;
			memcpy(ans, tmp, sizeof ans);
			break;
		case 3:
			if (put(k, n-1, 0) && dfs(k+1)) return 1;
			memcpy(ans, tmp, sizeof ans);
			break;
		case 4:
			for (int i = 1; i < n-1; i++) {
				if (put(k, i, 0) && dfs(k+1))
					return 1;
				memcpy(ans, tmp, sizeof ans);
			}
			break;
		case 5:
			for (int i = 1; i < n-1; i++) {
				if (put(k, 0, i) && dfs(k+1))
					return 1;
				memcpy(ans, tmp, sizeof ans);
			}
			break;
		case 6:
			for (int i = 1; i < n-1; i++) {
				if (put(k, i, n-1) && dfs(k+1))
					return 1;
				memcpy(ans, tmp, sizeof ans);
			}
			break;
		case 7:
			for (int i = 1; i < n-1; i++) {
				if (put(k, n-1, i) && dfs(k+1))
					return 1;
				memcpy(ans, tmp, sizeof ans);
			}
			break;
		case 8:
			for (int i = 1; i < n-1; i++)
				for (int j = 1; j < n-1; j++) {
					if (put(k, i, j) && dfs(k+1))
						return 1;
					memcpy(ans, tmp, sizeof ans);
				}
			break;
	}
	return 0;
}
int main() {
	freopen("ascii.in", "r", stdin);
	freopen("ascii.out", "w", stdout);
	scanf("%d%d%d\n", &k, &w, &h);
	if (k == 1) {
		printf("%d %d\n", w, h);
		for (int i = 0; i < h; printf("\n"), i++)
			for (int j = 0; j < w; j++) putchar('A');
		return 0;
	}
	for (n = 1; n <= 4; n++)
		if (n*n == k) break;
	for (int i = 0; i < k; i++) {
		int fu = 1, fl = 1, fd = 1, fr = 1;
		for (int p = 0; p < 3*h-2; scanf("\n"), p++)
			for (int q = 0; q < 3*w-2; q++)
				a[i][p][q] = getchar();
		for (int j = 0; j < w; j++)
			if (a[i][h-2][w-1+j] != '.' || a[i][h-1][w-1+j] == '.')
				fu = 0;
		for (int j = 0; j < h; j++)
			if (a[i][h-1+j][w-2] != '.' || a[i][h-1+j][w-1] == '.')
				fl = 0;
		for (int j = 0; j < w; j++)
			if (a[i][2*h-1][w-1+j] != '.' || a[i][2*h-2][w-1+j] == '.')
				fd = 0;
		for (int j = 0; j < h; j++)
			if (a[i][h-1+j][2*w-1] != '.' || a[i][h-1+j][2*w-2] == '.')
				fr = 0;
		if (fu && fl) f[i] = 0;
		else if (fu && fr) f[i] = 1;
		else if (fd && fr) f[i] = 2;
		else if (fd && fl) f[i] = 3;
		else if (fl) f[i] = 4;
		else if (fu) f[i] = 5;
		else if (fr) f[i] = 6;
		else if (fd) f[i] = 7;
		else f[i] = 8;
	}
	dfs(0);
	printf("%d %d\n", n*w, n*h);
	for (int i = 0; i < n*h; printf("\n"), i++)
		for (int j = 0; j < n*w; j++)
			putchar(ans[i][j]);
	return 0;
}
