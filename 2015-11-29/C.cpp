#include <cstdio>
#include <algorithm>
int a[50][50], f[101][50][50], g[50], q[51];
int main() {
	int n, m, A, B, C;
	scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
	std::vector<int> z;
	z.push_back(A);
	z.push_back(B);
	z.push_back(C);
	for (int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y), x--, y--;
		a[x][y] = 1;
	}
	for (int i = 0; i < n; i++)
		f[0][i][i] = 1;
	for (int i = 0; i <= *std::max_element(z.begin(), z.end()); i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (f[i][j][k])
					for (int l = 0; l < n; l++)
						if (a[k][l])
							f[i+1][j][l] = 1;
	for (int i = 0; i < n-1; i++)
		g[i] = ~0U>>2;
	while (1) {
		int update = 0;
		for (int i = 0; i < n; i++) {
			int tmp = 0;
			for (int j = 0; j < 3; j++) {
				int tmp1 = ~0U>>2;
				for (int k = 0; k < n; k++)
					if (f[z[j]][i][k] && g[k] < tmp1)
						tmp1 = g[k];
				if (tmp1 > tmp)
					tmp = tmp1;
			}
			if (tmp + 1 < g[i]) {
				g[i] = tmp + 1;
				update = 1;
			}
		}
		if (!update)
			break;
	}
	if (g[0] > (int)(~0U>>3))
		puts("IMPOSSIBLE");
	else
		printf("%d\n", g[0]);
	return 0;
}
