#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(void) {
	int kase; scanf("%d", &kase); while (kase--) {
		int n, sharp = 0, other = 0, last_is_sharp = 0; 
		int ok = 1;
		char ch[100];
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", ch);
			if (ch[0] == '#') {
				if (last_is_sharp == 1) ok = 0;
				last_is_sharp = 1;
				sharp++;
			} else {
				last_is_sharp = 0;
				other ++;
			}
		}
		if (sharp != other + 1) ok = 0;
		puts(ok?"Yes":"No");
	}
	return 0;
}
