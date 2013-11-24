#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200;

pair<pair<int, int>, int> a[MAXN];

char ch[MAXN]; int n, k;

int main(void) {
	freopen("shuffle.in", "r", stdin);
	freopen("shuffle.out", "w", stdout);
	scanf("%s", ch); n = strlen(ch); scanf("%d", &k);
	for (int i = 0; i < n; i++) a[i].second = ch[i];
	for (int i = 0; i < k; i++) {
		for (int i = 0; i < n; i++) a[i].first.first = 0, a[i].first.second = -i;
		for (int i = 0; i < n; i++) {
			a[i].first.first = (i % 2)^1;
		}
		sort(a, a + n);
	}
	for (int i = 0; i < n;i++) putchar(a[i].second); puts("");
	return 0;
}

