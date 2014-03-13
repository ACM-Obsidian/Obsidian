#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1121;

int f[2][MAXN][MAXN], a[MAXN], top = 0;
int n, k;

int main(void) {
	freopen("D.txt", "r", stdin);
	for (int i = 2; i < MAXN; i++) {
		bool ok = true;
		for (int j = 2; (long long)j * j <= i; j++) if (i % j == 0) {
			ok = false;
			break;
		}
		if (ok) a[++top] = i;
	}
	while (scanf("%d%d", &n, &k), n || k) {
		int now = 0, last = 1;
		memset(f[last], 0, sizeof f[last]);
		for (int i = 0; i <= top; i++) f[last][0][i] = 1;
		for (int l = 1; l <= k; l++) {
			memset(f[now], 0, sizeof f[now]);
			for (int i = 2; i <= n; i++) {
				for (int j = l; j <= top; j++) {
					f[now][i][j] = f[now][i][j - 1] + (a[j] <= i ? f[last][i - a[j]][j - 1] : 0);
				}
			}
			swap(now, last);
		}
		printf("%d\n", f[last][n][top]);
	}
	return 0;
}

