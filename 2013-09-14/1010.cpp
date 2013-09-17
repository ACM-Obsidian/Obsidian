#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

int n, a[MAXN], cnt[50], m;

int main(void) {
	//freopen("in", "r", stdin);
	int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) {
		memset(cnt, 0, sizeof cnt);
		long long Ans = 0;
		scanf("%d%d", &n, &m); for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		int last = 1, now = 0;
		for (int j = 1; j <= n; j++) {
			for (int i = 0; i <= 30; i++) if (a[j] & (1 << i)) cnt[i]++, now |= 1 << i;
			while (last <= j && now >= m) {
				for (int i = 0; i <= 30; i++) if (a[last] & (1 << i)) {
					cnt[i]--;
					if (cnt[i] == 0) now -= 1 << i;
				}
				last++;
			}
			Ans += (long long) j - last + 1;
		}
		printf("Case #%d: %I64d\n", _, Ans);
	}
	return 0;
}
