#include <cstdio>
#include <cstring>
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
struct {
	int x, y;
} q[400];
char map[20][20];
int f[20][20], sx, sy, tx, ty;
int main() {
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	int n, m;
	scanf("%d%d\n", &n, &m);
	for (int i = 0; i < n; scanf("\n"), i++)
		for (int j = 0; j < m; j++) {
			map[i][j] = getchar();
			if (map[i][j] == 'S') sx = i, sy = j;
			if (map[i][j] == 'T') tx = i, ty = j;
		}
	memset(f, -1, sizeof f);
	int l = 0, r = 1;
	q[0].x = sx, q[0].y = sy;
	f[sx][sy] = 0;
	for (; l < r; l++) {
		int x = q[l].x, y = q[l].y;
		for (int d = 0; d < 4; d++) {
			int cnt = -1, x_ = x, y_ = y;
			for (; x_ >= 0 && x_ < n && y_ >= 0 && y_ < m && map[x_][y_] != '#'; )
				x_ += dx[d], y_ += dy[d], cnt++;
			cnt -= cnt / 2;
			x_ = x + dx[d]*cnt, y_ = y + dy[d]*cnt;
			if (f[x_][y_] == -1) {
				f[x_][y_] = f[x][y]+1;
				q[r].x = x_, q[r].y = y_, r++;
			}
		}
	}
	printf("%d\n", f[tx][ty]);
	return 0;
}
