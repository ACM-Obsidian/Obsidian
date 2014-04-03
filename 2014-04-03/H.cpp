#include <cstdio>
#include <algorithm>

const int MAXN = 20;

char f[MAXN][1 << MAXN];
int n, t[MAXN], x[MAXN], pow[1 << MAXN];

inline int trans(int s, int i) {
	int low = s & ((1 << i) - 1);
	int high = (s >> (i + 1)) << i;
	return (low + high) ^ ((1 << (n - 1)) - 1);
}

int main(void) {
	// freopen("in", "r", stdin);
	for (int i = 0; i < MAXN; i++) pow[1 << i] = i;
	int kase = 0;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) scanf("%d%d", t + i, x + i);
		for (int i = 0; i < n; i++) {
			for (int S = 1; S < (1 << (n - 1)); S++) {
				f[i][S] = 0; int tmp = S, sum = 0, cnt = 0;
				while (tmp) {
					int t = tmp & -tmp;
					f[i][S] |= f[i][S - t];
					sum += ::t[pow[t] < i ? pow[t] : pow[t] + 1];
					cnt++; tmp -= t;
				}
				if (sum / cnt >= t[i] - x[i] && sum / cnt <= t[i] + x[i]) f[i][S] = 1;
			}
		}
		int ans = 20;
		for (int S = 0; S < (1 << n); S++) {
			int tmp = S, ok = 1, cnt = 0;
			while (tmp) {
				int t = tmp & -tmp;
				cnt++;
				ok &= f[pow[t]][trans(S, pow[t])];
				tmp -= t;
			}
			if (ok) ans = std::min(ans, n - cnt);
		}
		printf("Case %d: %d\n", ++kase, ans);
	}
	return 0;
}

