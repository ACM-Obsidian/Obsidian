#include <cstdio>
#include <cstring>
int a[100], b[100], c[100];
char s[101];
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		int i = 0, l = strlen(s);
		for (; i < l; i++)
			if (s[i] != '0') break;
		if (i == l) i -= 1;
		for (int j = 0; j < l-i; j++)
			a[j] = s[l-1-j] - '0';
		int f = l-i; a[f] = 0;
		memcpy(b, a, sizeof a);
		memcpy(c, a, sizeof a);
		for (int i = 0, s, g = 0; i <= f; i++)
			s = a[i] * 5 + g, b[i] = s % 10, g = s / 10;
		for (int i = 0, s, g = 0; i <= f; i++)
			s = a[i] * 7 + g, c[i] = s % 10, g = s / 10;
		for (int i = 0, s, g = 2; i <= f; i++)
			s = b[i] + g, b[i] = s % 10, g = s / 10;
		for (int i = 0, s, g = 3; i <= f; i++)
			s = c[i] + g, c[i] = s % 10, g = s / 10;
		puts("3");
		for (int i = (a[f] ? f : f-1); i >= 0; i--)
			printf("%d", a[i]);
		puts("");
		for (int i = (b[f] ? f : f-1); i >= 0; i--)
			printf("%d", b[i]);
		puts("");
		for (int i = (c[f] ? f : f-1); i >= 0; i--)
			printf("%d", c[i]);
		puts("");
	}
	return 0;
}
