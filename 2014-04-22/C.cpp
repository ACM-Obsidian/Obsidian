#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
const char *sym = "WAKJSD";
int w, h, map[202][202], u[202][202];
char res[40805];
std::vector<std::pair<int, int> > q, q2;
void floodfill(int x0, int y0, int f) {
	q.clear();
	int l = 0, r = 1; q.push_back(std::pair<int, int>(x0, y0));
	u[x0][y0] = 1;
	while (l < r) {
		int x = q[l].first, y = q[l].second; l++;
		for (int d = 0; d < 4; d++)
			if (x + dx[d] >= 0 && x + dx[d] < h && y + dy[d] >= 0 && y + dy[d] < w
					&& !u[x+dx[d]][y+dy[d]] && (f || !map[x+dx[d]][y+dy[d]])) {
				u[x+dx[d]][y+dy[d]] = 1;
				q.push_back(std::pair<int, int>(x+dx[d], y+dy[d]));
				r++;
			}
	}
}
void solve() {
	memset(map, 0, sizeof map);
	for (int i = 0; i < h; scanf("\n"), i++)
		for (int j = 0; j < w; j++) {
			char ch = getchar();
			int num = 0;
			if (ch <= '9') num = ch-48;
			else num = ch-55;
			for (int k = 0; k < 4; k++)
				map[i+1][4*j+4-k] = num >> k & 1;
		}
	h += 2, w = w*4+2;
	memset(u, 0, sizeof u);
	floodfill(0, 0, 0);
	int l = 0;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (!u[i][j]) {
				floodfill(i, j, 1); q2 = q;
				for (int k = 0; k < q2.size(); k++) u[q2[k].first][q2[k].second] = 0;
				int cnt = 0;
				for (int k = 0; k < q2.size(); k++)
					if (!map[q2[k].first][q2[k].second] && !u[q2[k].first][q2[k].second])
						floodfill(q2[k].first, q2[k].second, 0), cnt++;
				for (int k = 0; k < q2.size(); k++) u[q2[k].first][q2[k].second] = 1;
				res[l++] = sym[cnt];
			}
	res[l] = 0;
	std::sort(res, res + l);
	puts(res);
}
int main() {
	int _ = 0;
	while (scanf("%d%d\n", &h, &w), h)
		printf("Case %d: ", ++_), solve();
	return 0;
}
