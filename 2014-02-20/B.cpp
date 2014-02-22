#include <cstdio>
#include <algorithm>
std::pair<int, int> a[10];
char s[10][200], t[20];
int inval;
int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", s[i]);
		a[i].first = 0, a[i].second = i;
	}
	for (int i = 0; i < m; i++) {
		scanf("%s", t);
		int cnt = 0, x;
		for (int j = 0; j < n; j++)
			if (t[j] == 'X') cnt++, x = j;
		if (cnt == 1) a[x].first--;
		else inval++;
	}
	std::sort(a, a + n);
	for (int i = 0; i < n; i++)
		printf("%s %.2lf%%\n", s[a[i].second], (double)-a[i].first*100 / m + 1e-10);
	printf("Invalid %.2lf%%\n", (double)inval*100 / m + 1e-10);
	return 0;
}
