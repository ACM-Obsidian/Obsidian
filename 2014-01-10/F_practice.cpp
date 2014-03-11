#include <cstdio>
#include <cstring>
const char *sym = "AaBbCcDdEeFfGgHhIiJjKkLlMmN";
const int dx[6] = {1, 0, 0, -1, 0, 0};
const int dy[6] = {0, 1, 0, 0, -1, 0};
const int dz[6] = {0, 0, 1, 0, 0, -1};
int a[3][3][3], f[27], x[27], y[27];
int dfs(int k, int x, int y, int z, int td) {
	if (k == 27) return 1;
	if (f[k]) {
		for (int d = 0; d < 6; d++)
			if (d != td && d != (td+3)%6
					&& x+dx[d] >= 0 && x+dx[d] < 3
					&& y+dy[d] >= 0 && y+dy[d] < 3
					&& z+dz[d] >= 0 && z+dz[d] < 3
					&& a[x+dx[d]][y+dy[d]][z+dz[d]] == -1) {
				a[x+dx[d]][y+dy[d]][z+dz[d]] = k;
				if (dfs(k+1, x+dx[d], y+dy[d], z+dz[d], d))
					return 1;
				a[x+dx[d]][y+dy[d]][z+dz[d]] = -1;
			}
	} else {
		int d = td;
		if (x+dx[d] >= 0 && x+dx[d] < 3
				&& y+dy[d] >= 0 && y+dy[d] < 3
				&& z+dz[d] >= 0 && z+dz[d] < 3
				&& a[x+dx[d]][y+dy[d]][z+dz[d]] == -1) {
			a[x+dx[d]][y+dy[d]][z+dz[d]] = k;
			if (dfs(k+1, x+dx[d], y+dy[d], z+dz[d], d))
				return 1;
			a[x+dx[d]][y+dy[d]][z+dz[d]] = -1;
		}
	}
	return 0;
}
void dfs0() {
	memset(a, -1, sizeof a);
	a[0][0][0] = 0, a[1][0][0] = 1;
	if (dfs(2, 1, 0, 0, 0)) return;
	a[0][0][0] = a[1][0][0] = -1;
	a[1][1][0] = 0, a[2][1][0] = 1;
	if (dfs(2, 2, 1, 0, 0)) return;
	a[2][1][0] = -1;
	a[1][1][1] = 1;
	if (dfs(2, 1, 1, 1, 2)) return;
	a[1][1][0] = a[1][1][1] = -1;
}
int main() {
	freopen("folding.in", "r", stdin);
	freopen("folding.out", "w", stdout);
	for (int i = 0; i < 15; scanf("\n"), i++)
		for (int j = 0; j < 15; j++) {
			char ch = getchar();
			if (ch != '.') {
				int k = 0;
				for (; sym[k] != ch; k++);
				x[k] = i, y[k] = j;
			}
		}
	int td;
	for (int i = 1; i < 27; i++) {
		int d = 0;
		for (; d < 6; d++)
			if (x[i] == x[i-1]+dx[d] && y[i] == y[i-1]+dy[d] && dz[d] == 0)
				break;
		if (i > 1) f[i] = (d != td);
		td = d;
	}
	dfs0();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; putchar(" \n"[j == 2]), j++)
			for (int k = 0; k < 3; k++) putchar(sym[a[i][j][k]]);
	return 0;
}
