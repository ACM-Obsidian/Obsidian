#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 210;

char ch[MAXN][MAXN]; int n, m;

inline bool check(int x1, int y1, int x2, int y2, char c = '#') {
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++) if (ch[i][j] == '#') {
			int x = i, y = j;
			while (x <= x2 && ch[x][j] == '#') x++; x--;
			while (y <= y2 && ch[i][y] == '#') y++; y--;
			for (int lx = i; lx <= x; lx++)
				for (int ly = j; ly <= y; ly++) {
					if (ch[lx][ly] != '#') return false;
					ch[lx][ly] = c;
				}
			for (int lx = x1; lx <= x2; lx++)
				for (int ly = y1; ly <= y2; ly++) if ((lx < i || lx > x || ly < j || ly > y) && ch[lx][ly] == '#') {
					return false;
				}
			return true;
		}
	return false;
}

int main(void) {
	freopen("rect.in", "r", stdin);
	freopen("rect.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch[i] + 1);
	}
	bool ok = false;
	for (int mid = 1; mid < n; mid++) {
		bool A1 = check(1, 1, mid, m);
		bool A2 = check(mid + 1, 1, n, m);
		if (A1 && A2) {
			check(1, 1, mid, m, 'a');
			check(mid + 1, 1, n, m, 'b');
			ok = true;
			break;
		}
	}
	if (!ok) {
		for (int mid = 1; mid < m; mid++) {
			bool A1 = check(1, 1, n, mid);
			bool A2 = check(1, mid + 1, n, m);
			if (A1 && A2) {
				check(1, 1, n, mid, 'a');
				check(1, mid + 1, n, m, 'b');
				ok = true;
				break;
			}
		}
	}
	if (ok) {
		puts("YES");
		for (int i = 1; i <= n; i++) puts(ch[i] + 1);
	} else puts("NO");
	return 0;
}

