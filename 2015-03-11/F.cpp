#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 16;

char str[20];
int S;

std::vector<long long> Ans;

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

inline long long modmul(long long a, long long b, long long c) {
	long long q = (long long)((long double)a*(long double)b/(long double)c);
	long long r = a*b-c*q;
	r %= c;
	if (r < 0) r += c;
	return r;
}
inline long long power(long long n, long long k, long long r) {
	long long t = n, s = 1;
	for (; k; k >>= 1, t = modmul(t, t, r))
		if (k & 1) s = modmul(s, t, r);
	return s;
}
inline int millerrabin(long long x, long long tester) {
	long long k = x-1; for (; !(k & 1); k >>= 1);
	long long y = power(tester, k, x);
	if (y == 1) return 1;
	for (; k < x-1; k <<= 1, y = modmul(y, y, x))
		if (y == x-1) return 1;
	return 0;
}
inline int is_prime(long long x) {
	if (x == 1)
		return false;
	if (x == 2 || x == 3 || x == 5 || x == 7 || x == 11 || x == 13 || x == 17 || x == 19 || x == 23 || x == 1662803)
		return true;
	if (!(x % 2) || !(x % 3) || !(x % 5) || !(x % 7) || !(x % 11))
		return false;
	if (x < 1122004669633LL)
		return millerrabin(x, 2) && millerrabin(x, 13) && millerrabin(x, 23) && millerrabin(x, 1662803);
	return millerrabin(x, 2) && millerrabin(x, 3) && millerrabin(x, 5) && millerrabin(x, 7) && millerrabin(x, 11) &&
		millerrabin(x, 13) && millerrabin(x, 17) && millerrabin(x, 19) && millerrabin(x, 23);
}

void Dfs(int x, int y, long long sum) {
	Ans.push_back(sum);
	if (S == (1 << 16) - 1) {
		return;
	}
	for (int k = 0; k < 8; k++) {
		int nx = x + dx[k], ny = y + dy[k];
		int pos = nx * 4 + ny;
		if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && !(S & (1 << pos))) {
			int t = str[pos] - 48;
			S |= 1 << pos;
			Dfs(nx, ny, sum * 10 + t);
			S ^= 1 << pos;
		}
	}
}

int main(void) {
	freopen("lottery.in", "r", stdin);
	freopen("lottery.out", "w", stdout);
	int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) {
		Ans.clear();
		printf("Ticket %d", _);
		scanf("%s", str);
		std::vector<std::pair<int, int> > start;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				int pos = i * 4 + j;;
				S |= 1 << pos;
				Dfs(i, j, str[pos] - 48);
				S ^= 1 << pos;
			}
		std::sort(Ans.begin(), Ans.end());
		Ans.resize(std::unique(Ans.begin(), Ans.end()) - Ans.begin());
		int i = Ans.size()-1;
		for (; i >= 0; i--)
			if (is_prime(Ans[i]))
				break;
		if (i == -1) {
			puts(" is unlucky.");
		} else {
			printf(", maximum prime is %I64d.\n", Ans[i]);
		}
	}
	return 0;
}

