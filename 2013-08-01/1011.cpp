#include <cstdio>
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		int n, m, x;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) scanf("%d", &x);
		printf(x ? "Alice\n" : "Bob\n");
	}
	return 0;
}
