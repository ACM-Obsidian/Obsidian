#include <cstdio>
#include <vector>
long long a[5][256][1000], x[1000];
char s[50000][6];
std::vector<std::pair<int, int> > ans;
int main() {
	int n; scanf("%d", &n);
	int k = (n+63)/64;
	long long lastmask = (1LL<<(n&63))-1;
	if (lastmask == 0) lastmask = -1;
	for (int i = 0; i < n; i++) {
		scanf("%s", s[i]);
		for (int j = 0; j < 5; j++)
			a[j][s[i][j]][i>>6] |= 1LL<<(i&63);
	}
	int cnt = 0;
	long long ansnum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) x[j] = 0;
		for (int j = 0; j < 5; j++)
			for (int t = 0; t < k; t++)
				x[t] |= a[j][s[i][j]][t];
		for (int j = i>>6; cnt < 100000 && j < k; j++) {
			long long tmp = ~x[j];
			while (tmp) {
				int loc = __builtin_ctzll(tmp), t = (j<<6)+loc;
				if (t < n && t > i) {
					cnt++;
					ans.push_back(std::pair<int, int>(i, t));
					if (cnt == 100000) break;
				}
				tmp -= 1LL<<loc;
			}
		}
		for (int j = 0; j < k-1; j++)
			ansnum += __builtin_popcountll(~x[j]);
		ansnum += __builtin_popcountll(~x[k-1] & lastmask);
	}
	printf("%d\n", cnt);
	for (int i = 0; i < ans.size(); i++)
		printf("%d %d\n", ans[i].first+1, ans[i].second+1);
	return 0;
}
