#include <cstdio>
#include <cstring>

const int MAXN = 100010;

unsigned long long s[MAXN];
int N = 100000;

inline int cal(int x, int y) {
	char s1[10], s2[10];
	sprintf(s1 + 1, "%d", x);
	sprintf(s2 + 1, "%d", y);
	int n = strlen(s1 + 1), m = strlen(s2 + 1);
	int ret = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			int k = 0;
			while (s1[i + k] == s2[j + k] && i + k <= n && j + k <= m) k++;
			ret = ret < k ? k : ret;
		}
	return ret;
}

int main(void) {
	freopen("a_submit.cpp", "w", stdout);
	for (int i = 1; i <= N; i++) {
		s[i] = s[i - 1];
		for (int j = 1; j < i; j++) {
			s[i] += cal(i, j) * 2;
		}
		s[i] += cal(i, i);
	}
	putchar('{');
	for (int i = 1; i <= N; i++) {
		printf("%I64d, ", s[i]);
	}
	putchar('}');
	return 0;
}

