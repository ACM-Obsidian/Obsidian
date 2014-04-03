#include <cstdio>
#include <cstring>
#include <algorithm>
int f[1000000], g[1000000], n;
char s[1000001], tmp[1000001];
void judge(int len) {
	long long pred = 0, succ = 0, pow = 1;
	for (int i = 1; i < len; i++) {
		pred = (pred * 31 + (tmp[i-1] - 'a' + 1)) % 23333333333333333LL;
		succ = (succ + (tmp[len-i] - 'a' + 1) * pow) % 23333333333333333LL;
		pow = pow * 31 % 23333333333333333LL;
		if (pred != succ) f[n - len + i-1] = 1;
	}
}
void solve() {
	n = strlen(s);
	for (int i = 0; i < n; i++) f[i] = 0;
	f[n-1] = 1;
	int flag = -1;
	for (int i = 0; flag == -1 && i < n; i++)
		if (s[i] == s[(i+1)%n]) flag = i;
	if (flag == -1) {
		for (int i = 1; i < n; i++)
			if (!(n%i)) {
				g[i] = 0;
				for (int j = 0; !g[i] && j < n; j++)
					if (s[j] != s[(j+i)%n]) g[i] = 1;
			}
		f[0] = 1;
		for (int i = 1; i < n-1; i++)
			f[i] = g[std::__gcd(n-i-1, n)];
	} else {
		int last = flag;
		for (int i = flag+1; i < n; i++)
			if (s[i] == s[(i+1)%n]) {
				int len = i - last;
				for (int j = 0; j < len; j++) tmp[j] = s[last+1+j];
				judge(len);
				last = i;
			}
		int len = n - last + flag;
		for (int j = 0; j < len; j++) tmp[j] = s[(last+1+j)%n];
		judge(len);
	}
	for (int i = 0; i < n; i++) putchar(f[i]+48);
	puts("");
}
int main() {
	int _ = 0;
	while (scanf("%s", s) == 1)
		printf("Case %d: ", ++_), solve();
	return 0;
}
