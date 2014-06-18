#include <cstdio>
#include <algorithm>
const int MAXN = 1000010;

std::pair<int, int> a[MAXN]; int n;
int f[MAXN][2], g[MAXN][2];
int Ans[MAXN];

int main(void) {
	int kase; scanf("%d", &kase); while (kase--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			char s1[10], s2[10];
			scanf("%s %s", s1, s2);
			a[i].first = s1[0] - 'A' + 1;
			a[i].second = s2[0] - 'A' + 1;
		}
		int ok = 0;
		for (int t = 0; t <= 1; t++) {
			f[1][t] = 1; f[1][!t] = 0;
			int tmp = t == 0 ? a[1].first : a[1].second;
			for (int i = 2; i <= n; i++) {
				f[i][0] = f[i][1] = 0;
				if (a[i - 1].first != a[i].first && f[i - 1][0])
					f[i][0] = 1, g[i][0] = 0;
				if (a[i - 1].second != a[i].first && f[i - 1][1])
					f[i][0] = 1, g[i][0] = 1;
				if (a[i - 1].first != a[i].second && f[i - 1][0])
					f[i][1] = 1, g[i][1] = 0;
				if (a[i - 1].second != a[i].second && f[i - 1][1])
					f[i][1] = 1, g[i][1] = 1;
			}
			if ((f[n][0] && a[n].first != tmp) || (f[n][1] && a[n].second != tmp)) {
				int t = (f[n][0] && a[n].first != tmp) ? 0 : 1;
				for (int i = n; i >= 1; i--) {
					Ans[i] = t ? a[i].second : a[i].first;
					t = g[i][t];
				}
				ok = 1;
				for (int i = 1; i <= n; i++) putchar(Ans[i] + 'A' - 1); puts("");
				break;
			}
		}
		if (!ok) puts("-");
	}
	return 0;
}

