#include <cstdio>
#include <vector>
#include <algorithm>
std::vector<int> a[200], b[200][200];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n*(n-1)/2; i++) {
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		x--, y--;
		if (x > y) std::swap(x, y);
		for (int j = 0; j < k; j++) {
			int z;
			scanf("%d", &z);
			a[x].push_back(z);
			a[y].push_back(z);
			b[x][y].push_back(z);
		}
		std::sort(b[x][y].begin(), b[x][y].end());
	}
	int flag = 1;
	for (int i = 0; i < n; i++) {
		std::sort(a[i].begin(), a[i].end());
		a[i].resize(std::unique(a[i].begin(), a[i].end()) - a[i].begin());
		for (int j = 0; j < i; j++) {
			int k = 0, l = 0, p = 0;
			for (; k < a[i].size() && l < a[j].size(); )
				if (a[i][k] < a[j][l]) k++;
				else if (a[i][k] > a[j][l]) l++;
				else {
					if (p >= b[j][i].size() || b[j][i][p] != a[i][k]) {
						flag = 0;
						break;
					}
					k++, l++, p++;
				}
			if (!flag) break;
		}
		if (!flag) break;
	}
	if (flag) {
		puts("Yes");
		for (int i = 0; i < n; i++) {
			printf("%d", (int)a[i].size());
			for (int j = 0; j < a[i].size(); j++) printf(" %d", a[i][j]);
			puts("");
		}
	} else puts("No");
	return 0;
}
