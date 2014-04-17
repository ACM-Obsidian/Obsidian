#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10;

int n, m, x[4], y[4];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

inline int get(int i) {
	return i == 3 ? n * m : (i + 1) * m * n / 4;
}

int vis[MAXN][MAXN], Ans;

inline int in(int X, int Y) {
	return !(X >= 0 && X < n && Y >= 0 && Y < m && !vis[X][Y]);
}

int im[MAXN][MAXN];
inline void Dfs(int X, int Y, int step) {
	if (X == 0 && Y == 1 && step == n * m) {
		Ans++;
		return;
	}
	if (im[X][Y] >= 0 && im[X][Y] != step) return;
	for (int i = 0; i < 4; i++) if (step < get(i)) {
		int d = get(i) - step;
		if (d < std::abs(X - x[i]) + std::abs(Y - y[i])) return;
	}
	if (in(X - 1, Y) && in(X + 1, Y) && !in(X, Y - 1) && !in(X, Y + 1)) return;
	if (!in(X - 1, Y) && !in(X + 1, Y) && in(X, Y - 1) && in(X, Y + 1)) return;
	vis[X][Y] = 1;
	for (int k = 0; k < 4; k++) {
		int nx = X + dx[k], ny = Y + dy[k];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
			Dfs(nx, ny, step + 1);
		}
	}
	vis[X][Y] = 0;
}

int main(void) {
	freopen("in", "r", stdin);
	int kase = 0; while (scanf("%d%d", &n, &m), n || m) {
		memset(im, -1, sizeof im);
		Ans = 0;
		im[0][1] = n * m;
		int ok = 1;
		for (int i = 0; i < 3; i++) {
			scanf("%d%d", x + i, y + i); 
			if (im[x[i]][y[i]] > 0) {
				ok = 0;
			}
			im[x[i]][y[i]] = get(i);
		} 
		x[3] = 0; y[3] = 1;
		if (ok) Dfs(0, 0, 1);
		printf("Case %d: %d\n", ++kase, Ans);
	}
	return 0;
}

