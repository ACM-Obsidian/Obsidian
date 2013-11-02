#include <cstdio>
#include <cstring>
const int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
const int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
struct rec {
	int x1, y1, x2, y2;
	rec(int x1_, int y1_, int x2_, int y2_)
		:x1(x1_), y1(y1_), x2(x2_), y2(y2_) {}
	rec() {}
} q[4096];
int f[8][8][8][8];
rec pre[8][8][8][8];
char s1[3], s2[3], t1[3], t2[3], ans[4096][5];
int main() {
	freopen("knights.in","r",stdin);
	freopen("knights.out","w",stdout);
	scanf("%s%s%s%s", s1, s2, t1, t2);
	int sx1 = s1[0]-97, sy1 = s1[1]-49, sx2 = s2[0]-97, sy2 = s2[1]-49;
	int tx1 = t1[0]-97, ty1 = t1[1]-49, tx2 = t2[0]-97, ty2 = t2[1]-49;
	memset(f, -1, sizeof f);
	f[sx1][sy1][sx2][sy2] = 0;
	q[0] = rec(sx1, sy1, sx2, sy2);
	int l = 0, r = 1;
	for (; l < r; l++) {
		int x1 = q[l].x1, y1 = q[l].y1, x2 = q[l].x2, y2 = q[l].y2;
		for (int d = 0; d < 8; d++)
			if (x1+dx[d] >= 0 && x1+dx[d] < 8 && y1+dy[d] >= 0 && y1+dy[d] < 8 && (x1+dx[d] != x2 || y1+dy[d] != y2) && f[x1+dx[d]][y1+dy[d]][x2][y2] == -1) {
				f[x1+dx[d]][y1+dy[d]][x2][y2] = f[x1][y1][x2][y2]+1;
				pre[x1+dx[d]][y1+dy[d]][x2][y2] = rec(x1, y1, x2, y2);
				q[r++] = rec(x1+dx[d], y1+dy[d], x2, y2);
			}
		for (int d = 0; d < 8; d++)
			if (x2+dx[d] >= 0 && x2+dx[d] < 8 && y2+dy[d] >= 0 && y2+dy[d] < 8 && (x2+dx[d] != x1 || y2+dy[d] != y1) && f[x1][y1][x2+dx[d]][y2+dy[d]] == -1) {
				f[x1][y1][x2+dx[d]][y2+dy[d]] = f[x1][y1][x2][y2]+1;
				pre[x1][y1][x2+dx[d]][y2+dy[d]] = rec(x1, y1, x2, y2);
				q[r++] = rec(x1, y1, x2+dx[d], y2+dy[d]);
			}
	}
	if (f[tx1][ty1][tx2][ty2] != -1) {
		int x1 = tx1, y1 = ty1, x2 = tx2, y2 = ty2, num = f[x1][y1][x2][y2];;
		printf("%d\n", num);
		for (int i = num-1; i >= 0; i--) {
			rec t = pre[x1][y1][x2][y2];
			int x1_ = t.x1, y1_ = t.y1, x2_ = t.x2, y2_ = t.y2;
			if (x1_ == x1 && y1_ == y1)
				sprintf(ans[i], "B %c%c", x2+97, y2+49);
			else
				sprintf(ans[i], "W %c%c", x1+97, y1+49);
			x1 = x1_, y1 = y1_, x2 = x2_, y2 = y2_;
		}
		for (int i = 0; i < num; i++) puts(ans[i]);
	} else puts("-1");
	return 0;
}
