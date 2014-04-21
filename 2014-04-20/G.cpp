#include <cstdio>
#include <cstring>
char map[1000][1000];
int l[1000][1000], r[1000][1000], u[1000][1000], d[1000][1000];
int fl[1000][1000][5], fr[1000][1000][5], fu[1000][1000][5], fd[1000][1000][5];
int n, m, k, L, len[100];
char op[100], s[100];
int check(int x, int y) {
	int p = 0;
	if (map[x][y] == '#') return 0;
	if (map[x][y] == s[0]) p++;
	int t;
	for (int i = 0; i < k; i++)
		switch (op[i]) {
			case 'L':
				if (l[x][y] < len[i]) return 0;
				t = y;
				while (p < L && fl[x][t][s[p]-'1'] != -1 && fl[x][t][s[p]-'1'] >= y - len[i])
					t = fl[x][t][s[p]-'1'], p++;
				y -= len[i];
				break;
			case 'R':
				if (r[x][y] < len[i]) return 0;
				t = y;
				while (p < L && fr[x][t][s[p]-'1'] != -1 && fr[x][t][s[p]-'1'] <= y + len[i])
					t = fr[x][t][s[p]-'1'], p++;
				y += len[i];
				break;
			case 'U':
				if (u[x][y] < len[i]) return 0;
				t = x;
				while (p < L && fu[t][y][s[p]-'1'] != -1 && fu[t][y][s[p]-'1'] >= x - len[i])
					t = fu[t][y][s[p]-'1'], p++;
				x -= len[i];
				break;
			case 'D':
				if (d[x][y] < len[i]) return 0;
				t = x;
				while (p < L && fd[t][y][s[p]-'1'] != -1 && fd[t][y][s[p]-'1'] <= x + len[i])
					t = fd[t][y][s[p]-'1'], p++;
				x += len[i];
				break;
		}
	return p == L;
}
int main() {
	scanf("%d%d\n", &n, &m);
	for (int i = 0; i < n; scanf("\n"), i++)
		for (int j = 0; j < m; j++) map[i][j] = getchar();
	for (int i = 0; i < n; i++) {
		if (map[i][0] == '#') l[i][0] = -1;
		else l[i][0] = 0;
		memset(fl[i][0], -1, sizeof(fl[i][0]));
		for (int j = 1; j < m; j++)
			if (map[i][j] == '#') {
				l[i][j] = -1;
				memset(fl[i][j], -1, sizeof(fl[i][j]));
			} else {
				l[i][j] = l[i][j-1] + 1;
				memcpy(fl[i][j], fl[i][j-1], sizeof(fl[i][j]));
				if (map[i][j-1] > '0' && map[i][j-1] <= '5')
					fl[i][j][map[i][j-1]-'1'] = j-1;
			}
		if (map[i][m-1] == '#') r[i][m-1] = -1;
		else r[i][m-1] = 0;
		memset(fr[i][m-1], -1, sizeof(fr[i][m-1]));
		for (int j = m-2; j >= 0; j--)
			if (map[i][j] == '#') {
				r[i][j] = -1;
				memset(fr[i][j], -1, sizeof(fr[i][j]));
			} else {
				r[i][j] = r[i][j+1] + 1;
				memcpy(fr[i][j], fr[i][j+1], sizeof(fr[i][j]));
				if (map[i][j+1] > '0' && map[i][j+1] <= '5')
					fr[i][j][map[i][j+1]-'1'] = j+1;
			}
	}
	for (int j = 0; j < m; j++) {
		if (map[0][j] == '#') u[0][j] = -1;
		else u[0][j] = 0;
		memset(fu[0][j], -1, sizeof(fu[0][j]));
		for (int i = 1; i < n; i++)
			if (map[i][j] == '#') {
				u[i][j] = -1;
				memset(fu[i][j], -1, sizeof(fu[i][j]));
			} else {
				u[i][j] = u[i-1][j] + 1;
				memcpy(fu[i][j], fu[i-1][j], sizeof(fu[i][j]));
				if (map[i-1][j] > '0' && map[i-1][j] <= '5')
					fu[i][j][map[i-1][j]-'1'] = i-1;
			}
		if (map[n-1][j] == '#') d[n-1][j] = -1;
		else d[n-1][j] = 0;
		memset(fd[n-1][j], -1, sizeof(fd[n-1][j]));
		for (int i = n-2; i >= 0; i--)
			if (map[i][j] == '#') {
				d[i][j] = -1;
				memset(fd[i][j], -1, sizeof(fd[i][j]));
			} else {
				d[i][j] = d[i+1][j] + 1;
				memcpy(fd[i][j], fd[i+1][j], sizeof(fd[i][j]));
				if (map[i+1][j] > '0' && map[i+1][j] <= '5')
					fd[i][j][map[i+1][j]-'1'] = i+1;
			}
	}
	scanf("%d\n", &k);
	for (int i = 0; i < k; i++)
		scanf("%c %d\n", &op[i], &len[i]);
	scanf("%s", s);
	L = strlen(s);
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (check(i, j)) ans++;
	printf("%d\n", ans);
	return 0;
}
