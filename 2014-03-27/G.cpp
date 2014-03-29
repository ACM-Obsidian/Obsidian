#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

long long x[MAXN], c[MAXN], t[MAXN]; long long f[MAXN];
int n;

int p[MAXN], stack[MAXN], top;

long long X[MAXN], Y[MAXN], K[MAXN];

inline bool cmp(int x, int y) {
	if (X[x] != X[y]) return X[x] < X[y];
	else return Y[x] < Y[y];
}

inline bool cmp_slope(int x, int y) {
	return K[x] > K[y];
}

inline long long rotate(int mid, int x, int y) {
	return (X[x] - X[mid]) * (Y[y] - Y[mid]) - (X[y] - X[mid]) * (Y[x] - Y[mid]);
}

inline void Update(long long *f, int from, int to) {
//	printf("Update %d to %d\n", from, to);
	f[to] = max(f[to], f[from] + c[from] * std::abs(x[from] - x[to]) + t[to]);
}

inline void Make(int l, int r) {
	int mid = (l + r) >> 1;
	for (int i = l; i <= mid; i++) p[i] = i;
	sort(p + l, p + mid + 1, cmp);
	top = 0;
	for (int i = l; i <= mid; i++) {
		int now = p[i];
		while (top >= 2 && rotate(now, stack[top], stack[top - 1]) <= 0) {
			top--;
		}
		stack[++top] = now;
	}
//	while (top > 1 && X[stack[top]] == X[stack[top - 1]]) top--;
	int head = 1;
//	while (head < top && X[stack[head]] == X[stack[head + 1]]) head++;
	for (int i = mid + 1; i <= r; i++) p[i] = i;
	sort(p + mid + 1, p + r + 1, cmp_slope);
	for (int i = mid + 1; i <= r; i++) {
		int now = p[i];
		while (head < top && Y[stack[head + 1]] - Y[stack[head]] >= K[now] * (X[stack[head + 1]] - X[stack[head]]))
			head++;
		Update(f, stack[head], now);
	}
}

inline void Cal(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	Cal(l, mid);
	for (int i = l; i <= mid; i++) {
		X[i] = c[i];
		Y[i] = c[i] * x[i] + f[i];
	}
	for (int i = mid + 1; i <= r; i++) {
		K[i] = x[i];
	}
	Make(l, r);
	for (int i = l; i <= mid; i++) {
		X[i] = c[i];
		Y[i] = f[i] - c[i] * x[i];
	}
	for (int i = mid + 1; i <= r; i++) {
		K[i] = -x[i];
	}
	Make(l, r);
	Cal(mid + 1, r);
}

long long g[MAXN];

int main(void) {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf(LL LL LL, x + i, c + i, t + i), f[i] = -100000000000000000ll;
	f[1] = 0;
	Cal(1, n);
	printf(LL "\n", f[n]);
	return 0;
}

