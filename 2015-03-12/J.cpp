#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 90;
const int mod = 1000000000;

int mat[N][N];

inline void swap (int a[], int b[], int n) {
	for (int i = 0; i < n; i++) swap(a[i], b[i]);
}
inline void addTimes (int a[], int b[], int k, int n) {
	for (int i = 0; i < n; i++) {
		a[i] = ((long long)b[i] * k + a[i]) % mod;
	}
}
inline int determint (int a[][N], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%4d ", a[i][j] == mod - 1 ? -1 : a[i][j]);
		}
		printf("\n");
	}

	int ans = 1;
	for (int i = 0; i < n; i++) {
		int piv = -1;
		for (int j = i; j < n; j++) {
			if (a[j][i] != 0) {
				piv = j;
				break;
			}
		}
		if (piv == -1) return 0;
		if (piv != i) swap(a[piv], a[i], n), ans *= -1;
		for (int j = i + 1; j < n; j++) {
			while (a[j][i] != 0) {
				int t = a[j][i] / a[i][i];
				addTimes(a[j], a[i], mod - t, n);
				if (a[j][i] == 0) break;
				swap(a[j], a[i], n);
				ans *= -1;
			}
		}
	}
	if (ans < 0) ans = mod + ans;
	for (int i = 0; i < n; i++) {
		ans = (long long)ans * a[i][i] % mod;
	}
	return ans;
}

int n, m;

int _crd[N][N];

inline int crd (int x, int y) {
	return _crd[x][y];
}
inline bool in (int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

char map[N][N];

int H[6][N] = {{1, 0, 1, 0, 2, 0}, {0, 1, 0, 2, 0, 3}, {1, 0, 2, 0, 3, 0}, {0, 2, 0, 3, 0, 4}, {2, 0, 3, 0, 4, 0}, {0, 3, 0, 4, 0, 6}};

int main () {
	printf("%d\n", determint(H, 6));
	// freopen("join.in", "r", stdin);
	// freopen("join.out", "w", stdout);
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) scanf("%s", map[i]);
		int crdtop = 0;
		memset(_crd, 0, sizeof _crd);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] != '*') _crd[i][j] = crdtop++;
			}
		}
		memset(mat, 0, sizeof mat);
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				if (map[x][y] == '*') continue;
				int a = crd(x, y);
				for (int k = 0; k < 4; k++) {
					int tx = x + dx[k], ty = y + dy[k];
					if (in(tx, ty) && map[tx][ty] != '*') {
						++mat[a][a];
						mat[a][crd(tx, ty)] = mod - 1;
					}
				}
			}
		}
		mat[0][0] = 1;
		for (int i = 1; i < n * m; i++) mat[0][i] = 0, mat[i][0] = 0;
		printf("%d\n", determint(mat, crdtop));
	}
	return 0;
}
