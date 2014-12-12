#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 55;
const int MAX_T = 1010;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool go[N][N][4];
bool ok[N][N][MAX_T][4];
bool ans[N][N];

int check_point[MAX_T];

inline int dir (int x0, int y0, int x1, int y1) {
	if (x0 == x1) {
		if (y1 > y0) return 3;
		else return 2;
	} else {
		if (x1 > x0) return 1;
		else return 0;
	}
}
inline void mark_go (int x0, int y0, int x1, int y1) {
	int d = dir(x0, y0, x1, y1);
	while (x0 != x1 || y0 != y1) {
		go[x0][y0][d] = true;
		x0 += dx[d], y0 += dy[d];
	}
}
inline int ch2dir (char a) {
	if (a == 'N') return 3;
	else if (a == 'S') return 2;
	else if (a == 'W') return 0;
	else return 1; // 'E'
}
inline int rev (int d) {
	return d ^ 1;
}

int main ()
{
	int n, x0, y0, T; scanf("%d %d %d %d", &n, &x0, &y0, &T);
	int X = 0, Y = 0;
	for (int i = 0; i < n; i++) {
		int x0, y0, x1, y1; scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
		mark_go(x0, y0, x1, y1);
		mark_go(x1, y1, x0, y0);
		X = max(X, max(x0, x1));
		Y = max(Y, max(y0, y1));
	}
	memset(check_point, -1, sizeof check_point);
	int cur = 0;
	for (int i = 0; i < T; i++) {
		char ch[5]; int c; scanf("%d %s", &c, ch);
		int d = ch2dir(ch[0]);
		cur += c;
		check_point[cur] = d;
	}
	for (int d = 0; d < 4; d++) {
		ok[x0][y0][0][d] = true;
	}
	for (int tt = 0; tt <= cur; tt++) {
		for (int x = 0; x <= X; x++) {
			for (int y = 0; y <= Y; y++) {
				// DEBUG
				/* for (int d = 0; d < 4; d++) {
					if (ok[x][y][tt][d]) printf("%d: %d %d %d\n", tt, x, y, d);
				} */

				if (tt == cur) {
					int ud = check_point[tt];
					for (int d = 0; d < 4; d++) if (ok[x][y][tt][d]) {
						if (d == ud || (ud != rev(d) && go[x][y][ud]))
							ans[x][y] = true;
					}
				}
				else {
					for (int td = 0; td < 4; td++) if (ok[x][y][tt][td]) {
						for (int d = 0; d < 4; d++) if (go[x][y][d] && d != rev(td)) {
							if (check_point[tt] != -1) {
								if (td != check_point[tt] && d != check_point[tt])
									continue;
							}
							int tx = x + dx[d], ty = y + dy[d];
							ok[tx][ty][tt + 1][d] = true;
						}
					}
				}
			}
		}
	}
	for (int x = 0; x <= X; x++) {
		for (int y = 0; y <= Y; y++) {
			if (ans[x][y]) {
				printf("%d %d\n", x, y);
			}
		}
	}
	return 0;
}
