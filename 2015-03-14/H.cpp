#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2010;
const int MASK = 1023;

int dp[N][N];

int main () {
	freopen("sultan.in", "r", stdin);
	freopen("sultan.out", "w", stdout);
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < N - 1; i++) dp[0][i] = 1;
	for (int i = 2; i < N - 1; i++) {
		for (int j = i; j >= 2; j--) {
			dp[i][j] = dp[i - j][j] + dp[i][j + 1];
			dp[i][j] &= MASK;
		}
	}
	int n; while (scanf("%d", &n) == 1) {
		printf("%d\n", dp[n][2]);
	}
	return 0;
}
