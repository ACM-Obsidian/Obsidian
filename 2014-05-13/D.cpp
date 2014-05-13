#include <cstdio>
#include <algorithm>
#include <map>
const int p[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
long long c[63][63];
int now[15];
std::map<long long, long long> T;
void dfs(int dep, int upper, long long lim) {
	long long num = 1, sum = 1;
	int n = 0;
	for (int i = 0; i < dep; n += now[i], i++)
		for (int j = 0; j < now[i]; j++) num *= p[i];
	for (int i = 0; i < dep; i++) {
		long long tmp = c[n][now[i]];
		if ((~0ULL>>1) / sum < tmp) {
			sum = -1;
			break;
		}
		sum *= tmp;
		n -= now[i];
	}
	if (sum > 0) {
		std::map<long long, long long>::iterator it = T.find(sum);
		if (it == T.end()) T.insert(std::make_pair(sum, num));
		else if (it->second > num) it->second = num;
	}
	for (int i = 1; i <= upper; i++) {
		lim /= p[dep];
		if (lim == 0) break;
		now[dep] = i;
		dfs(dep+1, i, lim);
	}
}
int main() {
	c[0][0] = 1;
	for (int i = 1; i <= 62; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = c[i-1][j] + c[i-1][j-1];
	}
	dfs(0, 62, ~0ULL>>1);
	long long x;
	while (scanf("%lld", &x) != EOF) printf("%lld %lld\n", x, T[x]);
	return 0;
}
