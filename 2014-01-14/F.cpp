#include <cstdio>
#include <vector>
char s[10], t[1000][10];
std::vector<int> ans;
int main() {
	freopen("fraud.in", "r", stdin);
	freopen("fraud.out", "w", stdout);
	scanf("%s", s);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", t[i]);
		int flag = 1;
		for (int j = 0; j < 9; j++)
			if (s[j] != t[i][j] && s[j] != '*')
				flag = 0;
		if (flag) ans.push_back(i);
	}
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < ans.size(); i++)
		puts(t[ans[i]]);
	return 0;
}
