#include <cstdio>
#include <cstring>
int a[17], l, cnt[16];
char s[17];
int main() {
	gets(s);
	l = strlen(s);
	for (int i = 0; i < l; i++) {
		if (s[l-i-1] < 58) a[i] = s[l-i-1]-48;
		else a[i] = s[l-i-1]-55;
		cnt[a[i]]++;
	}
	int ans = 0;
	for (int i = 0; i < l; i++) {
		cnt[a[i]]--;
		int flag = 0;
		for (int j = 0; j < 16; j++)
			if (cnt[j] > 1) {
				flag = 1;
				break;
			}
		if (flag) continue;
		for (int j = a[i]+1; j < 16; j++)
			if (cnt[j] == 0) {
				flag = 1;
				cnt[j] = 1;
				a[i] = j;
				for (int k = 0, p = i-1; k < 16 && p >= 0; k++)
					if (cnt[k] == 0) a[p--] = k;
				break;
			}
		if (flag) {
			ans = 1;
			break;
		}
	}
	if (!ans) {
		a[l++] = 1; a[l-2] = 0;
		for (int i = l-3, j = 2; i >= 0; i--, j++)
			a[i] = j;
	}
	for (int i = l-1; i >= 0; i--)
		if (a[i] < 10) putchar(a[i]+48);
		else putchar(a[i]+55);
	puts("");
	return 0;
}

