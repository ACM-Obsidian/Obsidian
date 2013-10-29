#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

long long n, t, w[MAXN], d[MAXN], p[MAXN]; int fim[MAXN], Ans[MAXN], fim_x[MAXN];

inline bool cmp(int x, int y) {
	return p[x] - d[x] * t < p[y] - d[y] * t;
}

inline bool cmp2(int x, int y) {
	return w[x] < w[y];
}

int main(void) {
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	while (scanf("%lld%lld", &n, &t) == 2) {
		for (int i = 1; i <= n; i++) scanf("%lld", w + i), fim[i] = i, fim_x[i] = i;
		for (int i = 1; i <= n; i++) scanf("%lld", d + i);
		for (int i = 1; i <= n; i++) scanf("%lld", p + i);
		sort(fim + 1, fim + n + 1, cmp);
		sort(fim_x + 1, fim_x + n + 1, cmp2);
		for (int i = 1; i <= n; i++) {
			Ans[fim[i]] = fim_x[i];
		}
		for (int i = 1; i <= n; i++) printf("%d%c", Ans[i], " \n"[i == n]);
	}
	return 0;
}

