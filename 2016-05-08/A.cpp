#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	for (; T; T--) {
		int n, p;
		scanf("%d %d", &n, &p);
		int ans = 0;
		double best = -1;
		for (int i = 0; i < n; i++) {
			int l; double r;
			scanf("%d %lf", &l, &r);
			if (p >= l && r > best) {
				best = r;
				ans = i + 1;
			}
		}
		printf("%d\n", ans);
	}
}
