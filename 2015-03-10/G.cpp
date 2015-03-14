#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 11;

int f[MAXN][1 << MAXN];
int a[MAXN][MAXN];

int n = 11;

int main(void) {
		freopen("lineup.in", "r", stdin);
		freopen("lineup.out", "w", stdout);
	int kase; scanf("%d", &kase); while (kase--) {
		memset(f, 0xcf, sizeof f);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
				if (a[i][j] == 0) a[i][j] = f[0][0];
			}
		for (int i = 0; i < n; i++) f[0][1 << i] = a[i][0];
		for (int i = 1; i < n; i++) {
			for (int S = 0; S < (1 << n); S++) {
				for (int next = 0; next < n; next++) if (S & (1 << next)) {
					f[i][S] = max(f[i][S], f[i - 1][S ^ (1 << next)] + a[next][i]);
				}
			}
		}
		printf("%d\n", f[n - 1][(1 << n) - 1]);
	}
	return 0;
}

