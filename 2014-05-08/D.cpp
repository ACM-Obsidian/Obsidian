#include <cstdio>
#include <cstring>
#include <string>
#define P 23333333333333333LL
std::string pref[101], suf[101];
long long hpref[101][100000], hsuf[101][100000], f[101], phpref[100000], phsuf[100000];
int n;
char p[100001];
void solve() {
	scanf("%s", p);
	int l = strlen(p);
	long long hash = 0, pow = 1;
	for (int i = 0; i < l; i++) {
		hash = (hash * 3 + (p[i]-47)) % P;
		phpref[i] = hash;
	}
	hash = 0;
	for (int i = l-1; i >= 0; i--) {
		hash = (hash + pow * (p[i]-47)) % P;
		phsuf[i] = hash;
		pow = (pow * 3) % P;
	}
	f[0] = (l == 1 && p[0] == '0');
	f[1] = (l == 1 && p[0] == '1');
	for (int i = 2; i <= n; i++) {
		f[i] = f[i-1] + f[i-2];
		for (int j = 1; j < l; j++)
			if (j <= suf[i-1].size() && l-j <= pref[i-2].size() && hsuf[i-1][suf[i-1].size()-j] == phpref[j-1] && hpref[i-2][l-j-1] == phsuf[j])
				f[i]++;
	}
	printf("%lld\n", f[n]);
}
int main() {
	pref[0] = suf[0] = "0";
	pref[1] = suf[1] = "1";
	for (int i = 2; i <= 100; i++) {
		if (pref[i-1].size() >= 100000) pref[i] = pref[i-1];
		else pref[i] = (pref[i-1] + pref[i-2]).substr(0, 100000);
		if (suf[i-2].size() >= 100000) suf[i] = suf[i-2];
		else {
			suf[i] = suf[i-1] + suf[i-2];
			if (suf[i].size() > 100000) suf[i] = suf[i].substr(suf[i].size() - 100000);
		}
	}
	for (int i = 0; i <= 100; i++) {
		long long hash = 0, pow = 1;
		for (int j = 0; j < pref[i].size(); j++) {
			hash = (hash * 3 + (pref[i][j]-47)) % P;
			hpref[i][j] = hash;
		}
		hash = 0;
		for (int j = suf[i].size()-1; j >= 0; j--) {
			hash = (hash + pow * (suf[i][j]-47)) % P;
			hsuf[i][j] = hash;
			pow = (pow * 3) % P;
		}
	}
	int _ = 0;
	while (scanf("%d", &n) == 1)
		printf("Case %d: ", ++_), solve();
	return 0;
}
