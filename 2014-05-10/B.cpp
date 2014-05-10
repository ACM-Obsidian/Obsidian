#include <cstdio>
#include <algorithm>
int n;
char s[5];
void solve() {
	int l = -2000000000, r = 2000000000;
	scanf("%d", &n);
	while (n--) {
		int x;
		scanf("%s%d", s, &x);
		if (s[0] == '>')
			if (s[1] == '=') l = std::max(l, x);
			else l = std::max(l, x+1);
		else if (s[0] == '<')
			if (s[1] == '=') r = std::min(x, r);
			else r = std::min(x-1, r);
		else
			l = r = x;
	}
	if (l == -2000000000 || r == 2000000000) puts("-1");
	else printf("%d\n", r-l+1);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
