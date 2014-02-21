#include <cstdio>
int a[256];
char s[100];
int main() {
	freopen("arrange.in", "r", stdin);
	freopen("arrange.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		a[int(s[0])] = 1;
	}
	int ans = 0;
	while (a[int(65+ans)]) ans++;
	printf("%d\n", ans);
	return 0;
}
