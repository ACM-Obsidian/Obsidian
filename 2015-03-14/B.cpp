#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

int n, k;
int a[MAXN][MAXN], f[MAXN];

int main(void) {
	freopen("cabbage.in", "r", stdin);
	freopen("cabbage.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= k; j++) {
			int x; scanf("%d", &x);
			a[i][x] = j;
		}
	f[n + 1] = 0;
	for (int i = k; i >= 1; i--) {
		int cnt = 0;
		for (int j = 1; j <= n; j++) cnt += a[j][i] < a[j][f[i + 1]];
		if (cnt > n / 2) f[i] = i; else f[i] = f[i + 1];
	}
	if (f[1] == 0) puts("Nothing"); else
	printf("%d\n", f[1]);
	return 0;
}

