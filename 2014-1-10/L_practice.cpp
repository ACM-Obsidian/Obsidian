#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1520;

int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[] = {0, 1, 0, -1, -1, 1, 1, -1};

int n, m, a[MAXN][MAXN]; char ch[MAXN]; int _ = 0;
int S1[MAXN][MAXN], S2[MAXN][MAXN], S[MAXN][MAXN];

pair<int, int> d[MAXN * MAXN]; int color[MAXN][MAXN];

inline int In(int x, int y) {
	return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1 && a[x][y] == 0;
}

inline int& s(int x, int y) {if (x < 0 || y < 0) return _; else return S[x][y];}
inline int& s1(int x, int y) {if (x < 0 || y < 0) return _; else return S1[x][y];}
inline int& s2(int x, int y) {if (x < 0 || y < 0) return _; else return S2[x][y];}

int main(void) {
	freopen("labyrinth.in", "r", stdin);
	freopen("labyrinth.out", "w", stdout);
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch + 1);
		for (int j = 1; j <= m; j++) a[i][j] = ch[j] == '.';
	}
	a[0][0] = a[0][1] = a[1][0] = 1;
	a[n + 1][m] = a[n][m + 1] = a[n + 1][m + 1] = 1;

	int head = 1, tail = 0;

	for (int i = 2; i <= n + 1; i++) d[++tail] = make_pair(i, 0), color[i][0] = 1;
	for (int i = 1; i < m; i++) d[++tail] = make_pair(n + 1, i), color[n + 1][i] = 1;
	while (head <= tail) {
		pair<int, int> now = d[head++];
		for (int k = 0; k < 8; k++) {
			int nx = now.first + dx[k], ny = now.second + dy[k];
			if (In(nx, ny) && !color[nx][ny]) {
				color[nx][ny] = 1;
				d[++tail] = make_pair(nx, ny);
			}
		}
	}

	head = 1, tail = 0;
	for (int i = 1; i < n; i++) d[++tail] = make_pair(i, m + 1), color[i][m + 1] = 2;
	for (int i = 2; i <= m + 1; i++) d[++tail] = make_pair(0, i), color[0][i] = 2;
	while (head <= tail) {
		pair<int, int> now = d[head++];
		for (int k = 0; k < 8; k++) {
			int nx = now.first + dx[k], ny = now.second + dy[k];
			if (In(nx, ny) && !color[nx][ny]) {
				color[nx][ny] = 2;
				d[++tail] = make_pair(nx, ny);
			}
		}
	}

	for (int i = 0; i <= n + 1; i++)
		for (int j = 0; j <= m + 1; j++) {
			s(i, j) = -s(i - 1, j - 1) + s(i - 1, j) + s(i, j - 1) + !a[i][j];
			s1(i, j) = -s1(i - 1, j - 1) + s1(i - 1, j) + s1(i, j - 1) + (color[i][j] == 1);
			s2(i, j) = -s2(i - 1, j - 1) + s2(i - 1, j) + s2(i, j - 1) + (color[i][j] == 2);
		}

	pair<int, pair<int, int> > Ans; Ans.first = 2000;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) if (!(i == 1 && j == 1) && !(i == n && j == m) && a[i][j] == 1) {
			int l = 1, r = (i == j ? i - 1 : min(i, j)); int inf = r;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (s1(i + 1, j + 1) - s1(i - mid - 1, j + 1) - s1(i + 1, j - mid - 1) + s1(i - mid - 1, j - mid - 1) > 0 &&
					s2(i + 1, j + 1) - s2(i - mid - 1, j + 1) - s2(i + 1, j - mid - 1) + s2(i - mid - 1, j - mid - 1) > 0) {
					r = mid - 1;
				} else l = mid + 1;
			}
			if (l <= inf && s(i, j) - s(i - l, j) - s(i, j - l) + s(i - l, j - l) == 0) Ans = min(Ans, make_pair(l, make_pair(i, j)));
		}
	if (Ans.first != 2000) printf("%d %d %d\n", Ans.first, Ans.second.second - Ans.first + 1, Ans.second.first - Ans.first + 1);
	else puts("Impossible");
	return 0;
}

