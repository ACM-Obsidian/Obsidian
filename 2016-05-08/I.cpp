#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1510;
char map[N][N];
int color[N][N];

int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int r, c;

typedef pair<int, int> P;
#define X first
#define Y second
P pt[N * N]; int pt_top;

P queue[N * N];
void dfs(int x, int y, int cl, int conn = 4) {
	color[x][y] = cl;
	// indeed a bfs
	int ql = 0, qr = 0;
	queue[qr++] = P(x, y);
	while (qr > ql) {
		int x = queue[ql].X, y = queue[ql].Y;
		ql++;
		if (map[x][y] == '#') {
			pt[pt_top++] = P(x, y);
		}
		for (int i = 0; i < conn; i++) {
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx < 0 || tx >= r || ty < 0 || ty >= c) {
				continue;
			}
			if (map[tx][ty] != map[x][y]) {
				continue;
			}
			if (color[tx][ty] != 0) {
				continue;
			}
			color[tx][ty] = cl;
			queue[qr++] = P(tx, ty);
		}
	}
}

int dis[N][N];
void clear_for_longest() {
	for (int i = 0; i < pt_top; i++) {
		dis[pt[i].X][pt[i].Y] = -1;
	}
}
int ans_x, ans_y, ans_long;
void bfs_longest(int x, int y) {
	clear_for_longest();
	int ql = 0, qr = 0;
	ans_long = 0, ans_x = x, ans_y = y;
	queue[qr++] = P(x, y);
	dis[x][y] = 0;
	while (qr > ql) {
		int x = queue[ql].X, y = queue[ql].Y;
		if (dis[x][y] > ans_long) {
			ans_long = dis[x][y];
			ans_x = x;
			ans_y = y;
		}
		ql++;
		for (int i = 0; i < 8; i++) {	
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx < 0 || tx >= r || ty < 0 || ty >= c) {
				continue;
			}
			if (map[tx][ty] != map[x][y]) {
				continue;
			}
			if (dis[tx][ty] == -1 || dis[tx][ty] > dis[x][y] + 1) {
				dis[tx][ty] = dis[x][y] + 1;
				queue[qr++] = P(tx, ty);
			}
		}
	}
}

int main () {
	// freopen("in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T) {
		scanf("%d %d", &r, &c);
		r += 2;
		c += 2;
		for (int j = 0; j < c; j++) map[0][j] = '.';
		map[0][c] = 0;
		for (int i = 1; i <= r - 2; i++) {
			map[i][0] = '.';
			scanf("%s", &map[i][1]);
			map[i][c - 1] = '.';
			map[i][c] = 0;
		}
		for (int j = 0; j < c; j++) map[r - 1][j] = '.';
		map[r - 1][c] = 0;
		memset(color, 0, sizeof color);
		int tc = 1;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (map[i][j] == '.' && color[i][j] == 0) {
					dfs(i, j, tc);
					++tc;
				}
			}
		}
		int P = 0, K = 0, U = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (map[i][j] == '#' && color[i][j] == 0) {
					int xx = i, yy = j;
					pt_top = 0;
					dfs(i, j, -1, 8);

					bool tmp;

					// is P?
					int last_color = -1;
					tmp = false;
					for (int i = 0; !tmp && i < pt_top; i++) {
						int x = pt[i].X;
						int y = pt[i].Y;
						for (int j = 0; j < 4; j++) {
							int tx = x + dx[j];
							int ty = y + dy[j];
							if (tx < 0 || tx >= r || ty < 0 || ty >= c) {
								continue;
							}
							if (map[tx][ty] == '.') {
								if (last_color == -1) {
									last_color = color[tx][ty];
								} else if (last_color != color[tx][ty]) {
									tmp = true;
									break;
								}
							}
						}
					}
					if (tmp) {
						++P;
						continue;
					}

					// K or U
					bfs_longest(xx, yy);
					bfs_longest(ans_x, ans_y);
					double S = ans_long;
					double T = pt_top;
					double X = T / (S * S);
					// printf("Block (%d, %d): S = %.0f, T = %.0f, X = %f\n", xx, yy, S, T, X);
					if (X > 0.15) {
						++K;
					} else {
						++U;
					}
				}
			}
		}

		printf("P: %d\nK: %d\nU: %d\ntotal: %d\n", P, K, U, P + K + U);
	}
	return 0;
}
