#include <cstdio>
#include <cmath>
#include <ctime>
int v[10000000];
int main() {
	freopen("wizard.in", "r", stdin);
	freopen("wizard.out", "w", stdout);
	int top = 0;
	double tmp = 0, a = log(3) / log(10), l = log(9) / log(10);
	for (int i = 1; ; i++) {
		tmp += a;
		if (tmp - int(tmp) >= l) {
			v[top++] = i;
			i += 5; tmp += a * 5;
			if (top == 10000000) break;
		}
	}
	int T; scanf("%d", &T);
	while (T--) {
		int k; scanf("%d", &k);
		printf("%d\n", v[k-1]);
	}
	return 0;
}
