#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

const int N = 200;
const int Base = 100000000;

struct bigInt {
	int arr[N], m;
	bigInt (void) : m(1) {
		arr[0] = 0;
	}
	bigInt (int a) : m(1) {
		arr[0] = a;
		simplify();
	}	
	int& operator[] (const int& a) {
		return arr[a];
	}
	void print (void) {
		printf("%d", arr[m - 1]);
		for (int i = m - 2; i >= 0; i--) {
			printf("%08d", arr[i]);
		}
	}
	void simplify (void) {
		for (int i = 0; i < m; i++) {
			if (i == m - 1 && arr[i] >= Base) arr[m++] = 0;
			arr[i + 1] += arr[i] / Base;
			arr[i] %= Base;
		}
	}
	bigInt& operator+= (const bigInt& a) {
		if (m < a.m) {
			for (int i = m; i < a.m; i++) arr[i] = 0;
			m = a.m;
		}
		for (int i = 0; i < a.m; i++) arr[i] += a.arr[i];
		simplify();
		return *this;
	}
	bool isZero (void) {
		return m == 1 && arr[0] == 0;
	}
};
bigInt operator+ (bigInt& a, bigInt& b) {
	bigInt c(a);
	c += b;
	return c;
}

int n, m;

inline int Load (int s, int p) {
	return (s & (3 << (p << 1))) >> (p << 1);
}
inline void Save (int& s, int p, int k) {
	s ^= ((Load(s, p) ^ k) << (p << 1));
}

int vs[1010]; int vtop; // uid -> 4
int dict[250010]; // 4 -> uid

bigInt dp[2][9][1010];

inline bool valid (int s) {
	int st = 0;
	for (int i = 0; i <= m; i++) {
		int k = Load(s, i);
		if (k == 3) return false;
		if (k == 1) ++st;
		else if (k == 2) --st;
		if (st < 0) return false;
	}
	return st == 0;
}

int bracket[250010][9];

int main () {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	scanf("%d %d", &n, &m);
	bigInt ans;
	int maxS = 1 << ((m + 1) * 2);
	vtop = 0;
	for (int s = 0; s < maxS; s++) {
		if (valid(s)) vs[vtop++] = s;
	}
	memset(dict, -1, sizeof dict);
	for (int i = 0; i < vtop; i++) {
		dict[vs[i]] = i;
	}
	for (int i = 0; i < vtop; i++) {
		int S = vs[i];
		int stack[10], stop = 0;
		for (int j = 0; j <= m; j++) {
			int k = Load(S, j);
			if (k == 1) stack[stop++] = j;
			if (k == 2) {
				int jj = stack[--stop];
				bracket[S][j] = jj;
				bracket[S][jj] = j;
			}
		}
	}

	dp[0][0][dict[0]] = 1;
	for (int x = 0; x < n; x++) {
		int t = x & 1;
		for (int y = 0; y < m; y++) {
			for (int s = 0; s < vtop; s++) if (!dp[t][y][s].isZero()) {
				bigInt V = dp[t][y][s];
				int S = vs[s];
				int v1 = Load(S, y);
				int v2 = Load(S, y + 1);
				if (v1 == 0 && v2 == 0) {
					dp[t][y + 1][s] += V;
					Save(S, y, 1);
					Save(S, y + 1, 2);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 1 && v2 == 0 || v1 == 0 && v2 == 1) {
					Save(S, y, 0);
					Save(S, y + 1, 1);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
					Save(S, y, 1);
					Save(S, y + 1, 0);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 2 && v2 == 0 || v1 == 0 && v2 == 2) {
					Save(S, y, 0);
					Save(S, y + 1, 2);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
					Save(S, y, 2);
					Save(S, y + 1, 0);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 1 && v2 == 1) {
					Save(S, bracket[S][y + 1], 1);
					Save(S, y, 0);
					Save(S, y + 1, 0);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 2 && v2 == 2) {
					Save(S, bracket[S][y], 2);
					Save(S, y, 0);
					Save(S, y + 1, 0);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 2 && v2 == 1) {
					Save(S, y, 0);
					Save(S, y + 1, 0);
					assert(dict[S] != -1);
					dp[t][y + 1][dict[S]] += V;
				} else if (v1 == 1 && v2 == 2) {
					Save(S, y, 0);
					Save(S, y + 1, 0);
					if (S == 0) ans += V;
				}
			}
		}
		for (int s = 0; s < vtop; s++) {
			int S = vs[s];
			if (Load(S, m) == 0) {
				S <<= 2;
				assert(dict[S] != -1);
				dp[t ^ 1][0][dict[S]] += dp[t][m][s];
			}
		}

		for (int y = 0; y <= m; y++) {
			for (int s = 0; s < vtop; s++) {
				dp[t][y][s] = 0;
			}
		}
	}

	ans.print();
	printf("\n");
	return 0;
}
