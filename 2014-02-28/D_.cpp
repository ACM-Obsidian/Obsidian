#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3")

char S[50], ans[50], ans2[50];
int l, f[50], cnt[256], cnt2[256];
std::vector<int> tmp, tmp2;
std::vector<int> g[50][50];
void solve() {
	l = strlen(S);
	int flag = 0;
	for (int n = (l+1)/2; n < l; n++)
		for (int i = 0; i < l; i++) {
			tmp.clear();
			for (int j = 0; j < n; j++) tmp.push_back(j);
			int p = 0;
			g[n][i].clear();
			for (int j = 0; j < l-n; j++) {
				g[n][i].push_back(tmp[p]);
				tmp.erase(tmp.begin()+p);
				if (tmp.size()) p = (p+i)%tmp.size();
			}
		}
	ans[0] = 0;
	for (int n = l/2; n; n--) {
		flag = 0;
		for (int i = 0; i < l-1; i++) {
			tmp.clear();
			for (int j = 0; j < l; j++) tmp.push_back(j);
			tmp2.clear();
			int p = 0;
			for (int j = 0; j < n; j++) {
				tmp2.push_back(tmp[p]);
				tmp.erase(tmp.begin()+p);
				p = (p+i)%tmp.size();
			}
			for (int s = 0; s < l; s++) {
				for (int k = 65; k < 65+26; k++)
					cnt[k] = cnt2[k] = 0;
				for (int k = 0; k < l; k++)
					cnt[S[k]]++;
				for (int k = 0; k < n; k++)
					cnt2[S[tmp2[k]]]++;
				int flag3 = 0;
				for (int k = 65; k < 65+26; k++)
					if (cnt2[k]*2>cnt[k]) flag3 = 1;
				if (!flag3) {
					for (int k = 0; k < n; k++) ans2[k] = S[tmp2[k]];
					ans2[n] = 0;
					for (int j = i+1; flag != -1 && j < l; j++) {
						for (int t = 0; t < l-n; t++) {
							int flag2 = 1;
							for (int k = 0; k < n; k++) {
								int tt = g[l-n][j][k]+t;
								if (tt >= l-n) tt -= l-n;
								if (S[tmp2[k]] != S[tmp[tt]]) {
									flag2 = 0;
									break;
								}
							}
							if (flag2)
								if (!flag) {
									strcpy(ans, ans2);
									flag = 1;
								} else if (strcmp(ans, ans2) != 0) {
									flag = -1;
									break;
								}
						}
					}
				}
				if (flag == -1) break;
				for (int j = 0; j < tmp.size(); j++) tmp[j] = (tmp[j]+1)%l;
				std::sort(tmp.begin(), tmp.end());
				for (int j = 0; j < tmp2.size(); j++) tmp2[j] = (tmp2[j]+1)%l;
			}
			if (flag == -1) break;
		}
		if (flag != 0) break;
	}
	if (flag == -1) puts("Codeword not unique");
	else puts(ans);
}

int main() {
	freopen("insecure.in", "r", stdin);
	int _ = 0;
	while (gets(S), strcmp(S, "X") != 0)
		printf("Code %d: ", ++_), solve();
	return 0;
}
