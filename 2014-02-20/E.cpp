#include <cstdio>
#include <cstring>
#include <algorithm>

int n, L1, L2; char ch[100010]; long long Ans;

int main(void) {
	freopen("energy.in", "r", stdin);
	freopen("energy.out", "w", stdout);
	scanf("%d", &n); scanf("%s", ch); int Len = strlen(ch);
	for (int i = 0; i < Len; i++) {
		if (ch[i] == '1') {
			if (L1 + L2 * 2 < n) L1++;
			else if (L2 > 0) L2--, L1++;
		}
		if (ch[i] == '2') {
			if (L1 + L2 * 2 <= n - 2) L2++;
		}
		Ans += (long long)(L1 + L2);
	}
	printf("%lld\n", Ans);
	return 0;
}

