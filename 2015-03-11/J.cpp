#include <cstdio>
#include <string>
char s[101];
std::string t;
int main() {
	freopen("turing.in", "r", stdin);
	freopen("turing.out", "w", stdout);
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; _++) {
		scanf("%s", s);
		t = s;
		int i = 0;
		for (; i < 10; i++) {
			int j = 0;
			for (; j < t.size(); j++)
				if (t[j] != '3') break;
			if (j+1 >= t.size() || t[j] != '2')
				break;
			std::string t2;
			for (int k = 0; k < (j > 6 ? 101 : 1<<j); k++) {
				if (k) t2 += '2';
				t2 += t.substr(j+1);
				if (t2.size() > 100)
					break;
			}
			t2 = t2.substr(0, 100);
			t = t2;
		}
		if (i < 10)
			printf("Case #%d: Machine hangs at %d%c%c iteration.\n", _, i+1, "snrt"[std::min(i, 3)], "tddh"[std::min(i, 3)]);
		else
			printf("Case #%d: Machine doesn't hang at 10th iteration.\n", _);
	}
	return 0;
}
