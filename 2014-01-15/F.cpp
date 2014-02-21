#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
const int dx[4] = {-1, -1, 1, 1};
const int dy[4] = {-1, 1, 1, -1};
int f[10][10][65536], id[10][10], ans, mask;
char s[10][10];
std::queue<std::pair<std::pair<int, int>, int> > q;
void bfs() {
	while (!q.empty()) {
		int x = q.front().first.first, y = q.front().first.second, cmask = q.front().second;
		if (__builtin_popcount(mask-cmask) > ans)
			ans = __builtin_popcount(mask-cmask);
		f[x][y][cmask] = 0;
		q.pop();
		for (int d = 0; d < 4; d++)
			if (x+2*dx[d] >= 0 && x+2*dx[d] < 10 && y+2*dy[d] >= 0 && y+2*dy[d] < 10
					&& cmask & 1<<id[x+dx[d]][y+dy[d]] && s[x+2*dx[d]][y+2*dy[d]] == '#') {
			   int tx = x+2*dx[d], ty = y+2*dy[d], tmask = cmask&~(1<<id[x+dx[d]][y+dy[d]]);
			   if (f[tx][ty][tmask]) continue;
			   f[tx][ty][tmask] = 1;
			   q.push(std::make_pair(std::make_pair(tx, ty), tmask));
			}
	}
}
void solve() {
	for (int i = 0; i < 10; scanf("\n"), i++)
		for (int j = 0; j < 10; j++) s[i][j] = getchar();
	ans = 0;
	mask = 0;
	for (int i = 1; i < 9; i += 2)
		for (int j = 2; j < 9; j += 2)
			if (s[i][j] == 'B')
				mask |= 1 << id[i][j];
	for (int i = 0; i < 10; i += 2)
		for (int j = 1; j < 10; j += 2)
			if (s[i][j] == 'W') {
				s[i][j] = '#';
				f[i][j][mask] = 1;
				q.push(std::make_pair(std::make_pair(i, j), mask));
				bfs();
				s[i][j] = 'W';
			}
	mask = 0;
	for (int i = 2; i < 9; i += 2)
		for (int j = 1; j < 9; j += 2)
			if (s[i][j] == 'B')
				mask |= 1 << id[i][j];
	for (int i = 1; i < 10; i += 2)
		for (int j = 0; j < 10; j += 2)
			if (s[i][j] == 'W') {
				s[i][j] = '#';
				f[i][j][mask] = 1;
				q.push(std::make_pair(std::make_pair(i, j), mask));
				bfs();
				s[i][j] = 'W';
			}
	printf("%d\n", ans);
}
int main() {
	for (int i = 1, cnt = 0; i < 9; i += 2)
		for (int j = 2; j < 9; j += 2)
			id[i][j] = cnt++;
	for (int i = 2, cnt = 0; i < 9; i += 2)
		for (int j = 1; j < 9; j += 2)
			id[i][j] = cnt++;
	int T;
	for (scanf("%d\n", &T); T--; solve());
	return 0;
}
