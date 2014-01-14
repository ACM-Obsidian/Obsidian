#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000010;

int n, p, c, h, sum, last;
int a[MAXN], cnt[MAXN], b[MAXN], Ans[MAXN], top, other[MAXN];
int num[MAXN];

int main(void) {
	freopen("kabaleo.in", "r", stdin);
	freopen("kabaleo.out", "w", stdout);
	scanf("%d%d%d%d", &n, &p, &c, &h);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), cnt[a[i]]++, other[a[i]]++;
	for (int i = 1; i <= p; i++) {
		scanf("%d", b + i);
		if (i != 1) other[b[i]]++;
		if (i != 1 && b[i] != h) sum++;
		last = b[i];
	}
	if (n == 1) {
		if (last == h) puts("1\n1"); else puts("0\n");
	} else if (n == 2) {
		if (sum + (b[1] != h) != 0 || cnt[h] == 0 || cnt[h] == 1 && b[1] != h) {
			puts("0\n");
		} else {
			if (cnt[h] == 2) puts("2\n1 2"); else {
				if (a[1] == h) puts("1\n2");
				else puts("1\n1");
			}
		}
	} else {
		int it = 0;
		for (int i = 1; i <= c; i++) if (i != h) num[other[i]]++, it = max(it, other[i]);
		for (int i = 1; i <= n; i++) {
			cnt[a[i]]--; cnt[b[1]]++;
			if (a[i] != b[1]) {
				other[a[i]]--; if (a[i] != h) num[other[a[i]]]++, num[other[a[i]] + 1]--;
				other[b[1]]++; if (b[1] != h) num[other[b[1]]]++, num[other[b[1]] - 1]--;
			}
			int tmp = 0; 
			if (num[it + 1]) tmp = it + 1; else
			if (num[it]) tmp = it;
			else tmp = it - 1;
			if (tmp < cnt[h] - sum) {
				Ans[++top] = i;
			}
			cnt[a[i]]++; cnt[b[1]]--;
			if (a[i] != b[1]) {
				other[a[i]]++; if (a[i] != h) num[other[a[i]]]++, num[other[a[i]] - 1]--;
				other[b[1]]--; if (b[1] != h) num[other[b[1]]]++, num[other[b[1]] + 1]--;
			}
		}
		printf("%d\n", top);
		for (int i = 1; i <= top; i++) printf("%d ", Ans[i]);
	}
	return 0;
}

