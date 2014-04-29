#include <cstdio>
#include <cstring>
char s[51], t[51];
int l;
int main() {
	scanf("%s%s", s, t);
	l = strlen(s);
	while (1) {
		int op, num, flag = 0;
		char ch = 'a';
		for (; ch <= 'z'; ch++) {
			for (int i = 0; i < l; i++)
				if (t[i] == ch && s[i] != ch) {
					if (s[i] != '.') {
						int cnt = 0;
						for (int j = 0; j < l; j++)
							if (s[j] == s[i]) cnt++;
						int cnt2 = 0;
						for (int j = 0; j < l; j++)
							if (t[j] == s[i]) cnt2++;
						if (cnt > 1 || cnt2 == 0) {
							op = 0, num = i;
							flag = 1;
							break;
						}
					} else {
						op = 1;
						num = 0;
						for (; num < l; num++)
							if (s[num] == ch) break;
						flag = 1;
						break;
					}
				}
			if (flag) break;
		}
		if (!flag)
			for (int i = 0; i < l; i++)
				if (t[i] == '.' && s[i] != '.') {
					int cnt = 0;
					for (int j = 0; j < l; j++)
						if (s[j] == s[i]) cnt++;
					int cnt2 = 0;
					for (int j = 0; j < l; j++)
						if (t[j] == s[i]) cnt2++;
					if (cnt > 1 || cnt2 == 0) {
						op = 0, num = i;
						flag = 1;
						break;
					}
				}
		if (!flag)
			for (int i = 0; i < l; i++)
				if (s[i] == '.') {
					op = 1, num = 0;
					for (; num < l; num++)
						if (s[num] != '.') break;
					flag = 1;
					break;
				}
		if (!flag)
			for (char ch = 'a'; ch <= 'z'; ch++) {
				int cnt = 0;
				for (int i = 0; i < l; i++)
					if (s[i] == ch) cnt++;
				int cnt2 = 0;
				for (int j = 0; j < l; j++)
					if (t[j] == ch) cnt2++;
				if (cnt > 1 || cnt2 == 0) {
					op = 0, num = 0;
					for (; num < l; num++)
						if (s[num] == ch) break;
					flag = 1;
					break;
				}
			}
		printf("%s %d\n", op ? "dup" : "clr", num+1);
		fflush(stdout);
		int ret; scanf("%d", &ret);
		if (ret == -1) break;
		if (op) s[ret-1] = s[num];
		else s[num] = '.';
	}
	return 0;
}
