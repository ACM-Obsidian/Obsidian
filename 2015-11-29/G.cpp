#include <cstdio>
#include <cstring>
#include <algorithm>
int f[2000][2000];
long long g[2000][2000];
char s[2001], t[4001];
int n;
long long k;
const long long inf = 2000000000000000000LL;
int main() {
	scanf("%s", s);
	n = strlen(s);
	scanf("%lld", &k);
	memset(f, 0x3F, sizeof f);
	for (int i = 0; i < n; i++)
		f[i][i] = 1, g[i][i] = 1;
	for (int i = 0; i+1 < n; i++)
		if (s[i] == s[i+1])
			f[i][i+1] = 2, g[i][i+1] = 1;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < n-i; j++) {
			int k = i+j;
			if (s[j] == s[k]) {
				if (i > 1) {
					f[j][k] = f[j+1][k-1] + 2;
					g[j][k] = g[j+1][k-1];
				}
			} else {
				if (f[j][k-1] + 2 < f[j][k]) {
					f[j][k] = f[j][k-1] + 2;
					g[j][k] = g[j][k-1];
				}
				if (f[j+1][k] + 2 < f[j][k]) {
					f[j][k] = f[j+1][k] + 2;
					g[j][k] = g[j+1][k];
				} else if (f[j+1][k] + 2 == f[j][k])
					g[j][k] += g[j+1][k];
			}
			g[j][k] = std::min(g[j][k], inf);
		}
	int anslen = f[0][n-1];
	if (g[0][n-1] < k) {
		puts("NONE");
		return 0;
	}
	int l = 0, r = n-1;
	long long ans = 0;
	for (int i = 0; i < anslen+1>>1; i++) {
		int j = 0;
		for (; j < 26; j++) {
			int ll = l, rr = r;
			if (s[ll]-'a' == j) ll++;
			if (s[rr]-'a' == j) rr--;
			if ((ll > rr ? rr-ll+1 : f[ll][rr]) + (i + 1) * 2 > anslen)
				continue;
			if ((ll > rr ? 1 : g[ll][rr]) + ans >= k)
				break;
			ans += g[ll][rr];
		}
		if (s[l]-'a' == j) l++;
		if (s[r]-'a' == j) r--;
		t[i] = t[anslen-1-i] = j+'a';
	}
	puts(t);
	return 0;
}
