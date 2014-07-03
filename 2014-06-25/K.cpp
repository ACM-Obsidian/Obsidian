#include <cstdio>
#include <algorithm>
std::pair<int, int> e[2000000];
int p[22][2000000];
int cmp(std::pair<int, int> a, std::pair<int, int> b) {
	return a.first < b.first || a.first == b.first && a.second > b.second;
}
int main() {
	int n, k; scanf("%d%d", &n, &k);
	int m = 0;
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		if (x > y) e[m] = std::make_pair(x, y+n+1), m++;
		else e[m] = std::make_pair(x, y+1), e[m+1] = std::make_pair(x+n, y+n+1), m += 2;
	}
	std::sort(e, e + m, cmp);
	int maxr = -1, j = 0;
	for (int i = 0; i < m; i++)
		if (e[i].second > maxr) e[j++] = e[i], maxr = e[i].second;
	m = j;
	j = 0;
	for (int i = 0; i < m; i++) {
		while (j < m && e[j].first <= e[i].second) j++;
		if (j-1 > i) p[0][i] = j-1;
		else p[0][i] = -1;
	}
	for (int j = 1; j < 22; j++)
		for (int i = 0; i < m; i++)
			if (p[j-1][i] == -1) p[j][i] = -1;
			else p[j][i] = p[j-1][p[j-1][i]];
	int ans = ~0U>>1;
	for (int i = 0; i < m; i++) {
		int t = i, u = 0;
		if (e[i].second - e[i].first >= n) ans = 1;
		for (int j = 21; j >= 0; j--)
			if (p[j][t] != -1 && e[p[j][t]].second - e[i].first < n)
				t = p[j][t], u += 1<<j;
		if (p[0][t] != -1 && u+2 < ans) ans = u+2;
	}
	if (ans > ~0U>>2) puts("impossible");
	else printf("%d\n", ans);
	return 0;
}
