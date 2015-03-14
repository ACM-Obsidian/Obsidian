#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;

int dp[N][2];

int pass[N][2], drib[N][2];

int main () {
	freopen("counterattack.in", "r", stdin);
	freopen("counterattack.out", "w", stdout);
	int kase; for (scanf("%d", &kase); kase; --kase) {
		int n; scanf("%d", &n);
		scanf("%d %d", &dp[0][0], &dp[0][1]);
		int s0, s1; scanf("%d %d", &s0, &s1);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n - 1; j++) scanf("%d", &pass[j][i]);
			for (int j = 0; j < n - 1; j++) scanf("%d", &drib[j][i]);
		}
		for (int i = 1; i < n; i++) {
			dp[i][0] = min(dp[i - 1][0] + drib[i - 1][0], dp[i - 1][1] + pass[i - 1][1]);
			dp[i][1] = min(dp[i - 1][1] + drib[i - 1][1], dp[i - 1][0] + pass[i - 1][0]);
		}
		printf("%d\n", min(dp[n - 1][0] + s0, dp[n - 1][1] + s1));
	}
	return 0;
}
