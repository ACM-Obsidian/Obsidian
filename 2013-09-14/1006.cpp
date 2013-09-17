#include <cstdio>
#include <cstring>
int b[100000], l, cans[100001], cant[100001];
char s[100001], t[100001], cur[100001], curt[100001];
int can(char *s, int i) {
	if (i >= l) return 1;
	if (s[i] == '0') return 0;
	for (int j = i+1; j < l; j++)
		if (s[j] == '1') return 0;
	return 1;
}
void solve() {
	gets(s), gets(t);
	l = strlen(s);
	cans[l] = 1;
	for (int i = l-1; i >= 0; i--)
		cans[i] = cans[i+1] && (s[i] != '1');
	cant[l] = 1;
	for (int i = l-1; i >= 0; i--)
		cant[i] = cant[i+1] && (t[i] != '1');
	int xorsum = 0, cnt = 0, flag = 0;
	memset(b, 0, sizeof b);
	cur[l] = 0;
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < 2; j++)
			if ((s[i] == j+48 || s[i] == '?') && (t[i] == 49-j || t[i] == '?'))
				if (i == l-1 || cans[i+2] && s[i+1] != '0' && cant[i+2] && t[i+1] != '0')
					if (xorsum != -1 && xorsum == j) {
						b[0]++;
						if (!flag) {
							flag = 1;
							for (int k = 0; k < i; k++)
								if (s[k] != '?') cur[k] = s[k]; else cur[k] = t[k];
							cur[i] = j+48;
							if (i < l-1) {
								cur[i+1] = '1';
								for (int k = i+2; k < l; k++) cur[k] = '0';
							}
							strcpy(curt, cur);
							curt[i] = 97-cur[i];
						} else flag = 2;
					} else if (xorsum == -1 && cnt > 0) {
						b[cnt-1]++;
						if (!flag && cnt > 1 || flag) flag = 2;
						else {
							flag = 1;
							int tmpxor = j, pos;
							for (int k = 0; k < i; k++)
								if (s[k] != '?') cur[k] = s[k], tmpxor ^= s[k]-48;
								else if (t[k] != '?') cur[k] = t[k], tmpxor ^= t[k]-48;
								else pos = k;
							cur[pos] = tmpxor+48;
							cur[i] = j+48;
							if (i < l-1) {
								cur[i+1] = '1';
								for (int k = i+2; k < l; k++) cur[k] = '0';
							}
							strcpy(curt, cur);
							curt[i] = 97-cur[i];
						}
					}
		if (s[i] == '?' && t[i] == '?')
			if (xorsum != -1 || cnt != 0) xorsum = -1, cnt++;
			else;
		else if (s[i] != '?' && t[i] != '?' && s[i] != t[i]) xorsum = -1, cnt = 0;
		else if (s[i] != '?')
			if (xorsum != -1) xorsum ^= s[i]-48;
			else;
		else
			if (xorsum != -1) xorsum ^= t[i]-48;
	}
	if (!flag) puts("Impossible");
	else if (flag == 1) puts(cur), puts(curt);
	else {
		int sum = 0;
		for (int i = l-1; i >= 0; i--) sum = (sum*2+b[i])%1000000007;
		printf("Ambiguous %d\n", sum);
	}
}
int main() {
	int T; scanf("%d\n", &T);
	for (int _ = 1; _ <= T; _++) printf("Case #%d:\n", _), solve();
	return 0;
}
