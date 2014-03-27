#include <cstdio>
#include <cstring>
#include <algorithm>

#pragma GCC optimize("O3")

using namespace std;

const int MAXN = 103;
const int MAXM = 1005;
const long long base = 13331;

// the i-th string, and the j position, and the k direction
inline int encode(int i, int j, int k) {
	if (i < 0) return -1;
	return (i << 11) + (j << 1) + k;
}
inline pair<pair<int,int>, int> decode(int x) {
	if (x < 0) return make_pair(make_pair(-1, 0), 0);
	return make_pair(make_pair(x >> 11, (x >> 1) & 1023), x&1);
}

int n, len[MAXN]; char ch[MAXN][MAXM];

long long pow[MAXM], sum[MAXN][MAXM], sum_rev[MAXN][MAXM];

int Trans[2][MAXN][MAXM][MAXN], cost[2][MAXN][MAXM][MAXN];

inline long long getHash(int k, int l, int r) {
	return sum[k][r] - sum[k][l - 1] * pow[r - l + 1];
}
inline long long getHashrev(int k, int l, int r) {
	return sum_rev[k][l] - sum_rev[k][r + 1] * pow[r - l + 1];
}

int vis[2][MAXN][MAXM], inp[2][MAXN][MAXM];
int d[MAXN * MAXM * 2], fim[2][MAXN][MAXM];
int f[2][MAXN][MAXM], para[2 * MAXN * MAXM];

inline bool cmp(int x, int y) {
	pair<pair<int, int>, int> X = decode(x);
	pair<pair<int, int>, int> Y = decode(y);
	return fim[X.second][X.first.first][X.first.second] < fim[Y.second][Y.first.first][Y.first.second];
}

int main(void) {
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	memset(vis, -1, sizeof vis);
	pow[0] = 1; for (int i = 1; i < MAXM; i++) pow[i] = pow[i - 1] * base;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch[i] + 1);
		len[i] = strlen(ch[i] + 1);
		for (int j = 1; j <= len[i]; j++) {
			sum[i][j] = sum[i][j - 1] * base + ch[i][j] - 'a' + 1;
		}
		for (int j = len[i]; j >= 1; j--) {
			sum_rev[i][j] = sum_rev[i][j + 1] * base + ch[i][j] - 'a' + 1;
		}
		long long tmp = len[i] / 2;
		if (getHash(i, 1, tmp) == getHashrev(i, len[i] - tmp + 1, len[i])) {
			puts("-1");
			return 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= len[i]; j++) {
			for (int k = 1; k <= n; k++) {
				if (len[k] > j) {
					long long Ti = getHash(i, 1, j);
					long long Tj = getHashrev(k, 1, j);
					if (Ti == Tj) {
						Trans[0][i][j][k] = encode(k, len[k] - j, 1);
						cost[0][i][j][k] = 2 * j;
						inp[1][k][len[k] - j]++;
					}
					Ti = getHash(i, len[i] - j + 1, len[i]);
					Tj = getHashrev(k, len[k] - j + 1, len[k]);
					if (Ti == Tj) {
						Trans[1][i][j][k] = encode(k, len[k] - j, 0);
						cost[1][i][j][k] = 2 * j;
						inp[0][k][len[k] - j]++;
					}
				}
				if (len[k] < j) {
					long long Ti = getHash(i, j - len[k] + 1, j);
					long long Tj = getHashrev(k, 1, len[k]);
					if (Ti == Tj) {
						Trans[0][i][j][k] = encode(i, j - len[k], 0);
						cost[0][i][j][k] = 2 * len[k];
						inp[0][i][j - len[k]]++;
					}
					Ti = getHash(i, len[i] - j + 1, len[i] - j + 1 + len[k] - 1);
					if (Ti == Tj) {
						Trans[1][i][j][k] = encode(i, j - len[k], 1);
						cost[1][i][j][k] = 2 * len[k];
						inp[1][i][j - len[k]]++;
					}
				}
				if (len[k] == j) {
					long long Ti = getHash(i, 1, j);
					long long Tj = getHashrev(k, 1, len[k]);
					if (Ti == Tj) {
						Trans[0][i][j][k] = -1;
					}
					Ti = getHash(i, len[i] - j + 1, len[i]);
					if (Ti == Tj) {
						Trans[1][i][j][k] = -1;
					}
				}
			}
		}
	}
	int head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= len[i]; j++)
			for (int k = 0; k < 2; k++) if (inp[k][i][j] == 0) d[++tail] = encode(i, j, k);
	while (head <= tail) {
		pair<pair<int, int>, int> now = decode(d[head++]);
		fim[now.second][now.first.first][now.first.second] = head - 1;
		for (int i = 1; i <= n; i++) {
			int next_ = Trans[now.second][now.first.first][now.first.second][i];
			pair<pair<int, int>, int> next = decode(next_);
			if (next_ > 0 && !--inp[next.second][next.first.first][next.first.second]) {
				d[++tail] = next_;
			}
		}
	}
	head = 1, tail = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= len[i]; j++) {
			int tmp = j / 2;
			if (getHash(i, 1, tmp) == getHashrev(i, j - tmp + 1, j)) {
				d[++tail] = encode(i, len[i] - j, 1);
				vis[1][i][len[i] - j] = 0;
				f[1][i][len[i] - j] = j;
			}
			if (getHash(i, len[i] - tmp + 1, len[i]) == getHashrev(i, len[i] - j + 1, len[i] - j + 1 + tmp - 1)) {
				d[++tail] = encode(i, len[i] - j, 0);
				vis[0][i][len[i] - j] = 0;
				f[0][i][len[i] - j] = j;
			}
		}
		d[++tail] = encode(i, len[i], 0);
		vis[0][i][len[i]] = 0;
		d[++tail] = encode(i, len[i], 1);
		vis[1][i][len[i]] = 0;
	}
	while (head <= tail) {
		pair<pair<int, int>, int> now = decode(d[head++]);
		if (inp[now.second][now.first.first][now.first.second]) {
			puts("-1");
			return 0;
		}
		int step = vis[now.second][now.first.first][now.first.second];
		for (int i = 1; i <= n; i++) {
			int next_ = Trans[now.second][now.first.first][now.first.second][i];
			if (next_ == -1) {
				puts("-1");
				return 0;
			}
			if (next_ != 0) {
				pair<pair<int, int>, int> next = decode(next_);
				if (vis[next.second][next.first.first][next.first.second] == -1) {
					d[++tail] = next_;
					vis[next.second][next.first.first][next.first.second] = step + 1;
				}
			}
		}
	}
	sort(d + 1, d + tail + 1, cmp);
	int Ans = 0;
	for (int i = 1; i <= tail; i++) {
		pair<pair<int, int>, int> now = decode(d[i]);
		int which = now.first.first, pos = now.first.second, dir = now.second;
		int tmp = f[dir][which][pos], common = 0;
		for (int j = 1; j <= n; j++) {
			if (Trans[dir][which][pos][j]) {
				pair<pair<int, int>, int> next = decode(Trans[dir][which][pos][j]);
				f[next.second][next.first.first][next.first.second] = max(f[next.second][next.first.first][next.first.second],  tmp + cost[dir][which][pos][j]);
			} else {
				int l = 1, r = min(pos, len[j]);
				while (l <= r) {
					int mid = (l + r) >> 1;
					long long Ti = dir == 0 ? getHash(which, pos - mid + 1, pos) : getHash(which, len[which] - pos + 1, len[which] - pos + 1 + mid - 1);
					long long Tj = dir == 0 ? getHashrev(j, 1, mid) : getHashrev(j, len[j] - mid +1, len[j]);
					if (Ti == Tj) l = mid + 1; else r = mid - 1;
				}
				common = max(common, r * 2);
			}
		}
		Ans = max(Ans, f[dir][which][pos] + common);
	}
	for (int i = 1; i <= n; i++)
		for (int r = 1; r <= len[i]; r++)
			for (int l = 1; l <= r; l++) {
				int tmp = (r - l + 1) / 2;
				if (getHash(i, l, l + tmp - 1) == getHashrev(i, r - tmp + 1, r)) Ans = max(Ans, r - l + 1);
			}
	printf("%d\n", Ans);
	return 0;
}

