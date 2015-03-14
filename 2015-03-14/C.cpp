#include <cstdio>
#include <cstring>
#include <map>
#include <string>
std::map<std::string, int> T;
int a[100][100], b[100][100], tmp[100][100], c[100], m;
char s[100001], t[21];
void mul(int a[100][100], int b[100][100], int c[100][100]) {
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			tmp[i][j] = 0;
			for (int k = 0; k < m; k++)
				tmp[i][j] |= a[i][k] & b[k][j];
		}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = tmp[i][j];
}
int main() {
	freopen("cipher.in", "r", stdin);
	freopen("cipher.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%s%s", s, t);
		if (T.find(std::string(s)) == T.end())
			T.insert(std::make_pair(std::string(s), m++));
		if (T.find(std::string(t)) == T.end())
			T.insert(std::make_pair(std::string(t), m++));
		a[T[std::string(s)]][T[std::string(t)]] = 1;
	}
	for (int i = 0; i < m; i++)
		b[i][i] = 1;
	int k2 = k;
	for (; k; k >>= 1, mul(a, a, a))
		if (k & 1) mul(b, a, b);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			if (b[j][i]) c[i]++;
	int ans = 1;
	while (scanf("%s", s) == 1) {
		int i = 0, l = strlen(s);
		while (1) {
			for (; i < l; i++)
				if (s[i] >= 'a' && s[i] <= 'z') break;
			if (i == l) break;
			std::string t;
			for (; i < l && s[i] >= 'a' && s[i] <= 'z'; t += s[i], i++);
			if (k2 > 0)
				if (T.find(t) == T.end())
					ans = 0;
				else
					ans = 1LL * ans * c[T[t]] % 1234567891;
		}
	}
	printf("%d\n", ans);
	return 0;
}
