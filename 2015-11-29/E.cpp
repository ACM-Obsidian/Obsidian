#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
int cnt[20];
int tmp_cnt[20];
ll max_prod, ans;
int len, ss;

ll frac[30];
char str[40];

inline ll perm() {
	int s = 0;
	for (int i = 0; i < 10; i++) s += cnt[i];
	ll t = frac[s];
	for (int i = 0; i < 10; i++) t /= frac[cnt[i]];
	return t;
}

void dfs_3(int remain_sum, int remain_num, ll prod, int cur_num) {
	if (cur_num == 10 && remain_sum == 0 && remain_num == 0 && prod == max_prod) {
		bool cont = true;
		memcpy(tmp_cnt, cnt, sizeof cnt);

		for (int i = 0; cont && i < len; i++) {
			int c = str[i] - '0';
			for (int j = 0; j < c; j++) {
				if (cnt[j] > 0) {
					--cnt[j];
					ans += perm();
					++cnt[j];
				}
			}
			if (cnt[c] > 0) {
				--cnt[c];
			} else {
				cont = false;
			}
		}

		memcpy(cnt, tmp_cnt, sizeof cnt);
		return;
	} else if (cur_num == 10) {
		return;
	}
	for (int i = 0; i <= remain_num; i++) {
		if (remain_sum >= 0 && prod <= max_prod) {
			cnt[cur_num] = i;
			dfs_3(remain_sum, remain_num - i, prod, cur_num + 1);
		}
		remain_sum -= cur_num;
		prod *= (cur_num + 1);
		if (remain_sum < 0 || prod > max_prod) {
			break;
		}
	}
}

void dfs_2(int remain_sum, int remain_num, ll prod, int cur_num) {
	if (cur_num == 10 && remain_sum == 0 && remain_num == 0 && prod < max_prod) {
		ans += perm();
		return;
	} else if (cur_num == 10) {
		return;
	}
	for (int i = 0; i <= remain_num; i++) {
		if (remain_sum >= 0 && prod < max_prod) {
			cnt[cur_num] = i;
			dfs_2(remain_sum, remain_num - i, prod, cur_num + 1);
		}
		remain_sum -= cur_num;
		prod *= (cur_num + 1);
		if (remain_sum < 0 || prod > max_prod) {
			break;
		}
	}
}


ll dp[30][300];
ll dp_1(int sum, int num) {
	ll ans = 0;
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for (int i = 0; i < num; i++) {
		int max_sum = i * 9;
		for (int j = 0; j <= max_sum; j++) {
			if (dp[i][j] == 0) continue;

			for (int k = 0; k <= 9; k++) {
				dp[i + 1][j + k] += dp[i][j];
			}
		}
	}
	for (int j = 0; j < sum; j++) {
		ans += dp[num][j];
	}
	return ans;
}

int main () {
	while (scanf("%s", str) == 1) {
	len = strlen(str);
	ss = 0;
	for (int i = 0; i < len; i++) {
		ss += str[i] - '0';
	}

	frac[0] = 1;
	for (int i = 1; i <= 18; i++) frac[i] = frac[i - 1] * i;

	ans = dp_1(ss, len);
	
	max_prod = 1;
	for (int i = 0; i < len; i++) max_prod *= (str[i] - '0' + 1);

	dfs_2(ss, len, 1, 0);
	dfs_3(ss, len, 1, 0);
	printf("%lld\n", ans);
	}
	return 0;
}
