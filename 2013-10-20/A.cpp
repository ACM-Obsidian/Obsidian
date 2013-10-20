#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10010;

int n, a[MAXN], p[3];

int main(void) {
//	freopen("in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		if (n < 3) {puts("0"); continue;}
		sort(a + 1, a + n + 1);
		int S = 0;
		for (int i = 1; i < n; i++) S += a[i];
		if (a[n] > S * 2) {
			printf("%d\n", S);
		} else printf("%d\n", (S + a[n]) / 3);
	}
	return 0;
}
