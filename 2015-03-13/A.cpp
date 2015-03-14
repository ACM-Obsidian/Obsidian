#include <cstdio>
#include <vector>
#include <algorithm>
#define P 1000000007
int b[33][33], tmp[33][33], f[33][33];
int pwr[30][33][33], store[10000][33][33], a[33][33];
int n, m, r, l;
std::vector<int> d;
int power(int a, int n) {
	int s = 1, t = a;
	for (; n; n>>=1, t = 1LL*t*t%P)
		if (n & 1) s = 1LL*s*t%P;
	return s;
}
int calcphi(int n) {
	int t = n;
	for (int i = 2; i * i <= n; i++)
		if (!(n % i)) {
			t /= i, t *= i-1;
			for (; !(n % i); n /= i);
		}
	if (n > 1)
		t /= n, t *= n-1;
	return t;
}
void mul(int a[33][33], int b[33][33], int c[33][33]) {
	int t = 1<<m-1;
	for (int i = 0; i < t; i++)
		for (int j = 0; j < t; j++)
			tmp[i][j] = 0;
	for (int i = 0; i < t; i++)
		for (int j = 0; j < t; j++)
			for (int k = 0; k < t; k++)
				tmp[i][k] = (tmp[i][k] + 1LL * a[i][j] * b[j][k]) % P;
	for (int i = 0; i < t; i++)
		for (int j = 0; j < t; j++)
			c[i][j] = tmp[i][j];
}
int calc(int n, int k) {
	if (n >= m) {
		int t = k-1;
		for (; t >= 0; t--)
			if (!(n % d[t]) && n / d[t] <= 5 && d[t] >= m)
				break;
		if (t < 0) {
			for (int i = 0; i < 1<<m-1; i++)
				for (int j = 0; j < 1<<m-1; j++)
					b[i][j] = 0;
			for (int i = 0; i < 1<<m-1; i++)
				b[i][i] = 1;
			int p = 0;
			for (int t = n-m+1; t; t>>=1, p++)
				if (t & 1) mul(b, pwr[p], b);
		} else {
			for (int i = 0; i < 1<<m-1; i++)
				for (int j = 0; j < 1<<m-1; j++)
					b[i][j] = store[t][i][j];
			for (int x = 0; x+1 < n / d[t]; x++)
				mul(b, a, b), mul(b, store[t], b);
		}
		for (int i = 0; i < 1<<m-1; i++)
			for (int j = 0; j < 1<<m-1; j++)
				store[k][i][j] = b[i][j];
		int ans = 0;
		for (int i = 0; i < 1<<m-1; i++)
			for (int j = 0; j < 1<<m-1; j++)
				if (f[i][j])
					ans = (ans + b[i][j]) % P;
		return ans;
	} else {
		int ans = 0;
		int tmp[20];
		for (int i = 0; i < 1<<n; i++) {
			for (int j = 0; j * n < m * 2; j++)
				for (int k = 0; k < n; k++)
					tmp[j * n + k] = i >> k & 1;
			bool flag = true;
			for (int j = 0; j < m; j++) {
				int cnt = 0;
				for (int k = 0; k < m; k++)
					cnt += tmp[j + k];
				if (cnt > r) {
					flag = false;
					break;
				}
			}
			if (flag) ans++;
		}
		return ans;
	}
}
int main() {
	freopen("bar.in", "r", stdin);
	freopen("bar.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &r);
	for (int i = 0; i < 1<<m-1; i++)
		if (__builtin_popcount(i) <= r) {
			pwr[0][i][i >> 1] = 1;
			if (__builtin_popcount(i + (1 << m-1)) <= r)
				if (m != 1)
					pwr[0][i][(i >> 1) + (1 << m-2)] = 1;
				else
					pwr[0][i][0]++;
		}
	for (int i = 1; 1<<i <= n; i++)
		mul(pwr[i-1], pwr[i-1], pwr[i]);
	for (int i = 0; i < 1<<m-1; i++)
		a[i][i] = 1;
	for (int i = 0; i < m-1; i++)
		mul(a, pwr[0], a);
	for (int i = 0; i < 1<<m-1; i++) if (__builtin_popcount(i) <= r)
		for (int j = 0; j < 1<<m-1; j++) if (__builtin_popcount(j) <= r) {
			f[i][j] = 1;
			for (int k = 1; k < m; k++) {
				int tmp = ((i << k) + (j >> m-1 - k)) & ((1 << m) - 1);
				if (__builtin_popcount(tmp) > r) {
					f[i][j] = 0;
					break;
				}
			}
		}
	int ans = 0;
	for (int i = 1; i * i <= n; i++)
		if (!(n % i)) {
			d.push_back(i);
			if (i * i < n)
				d.push_back(n / i);
		}
	std::sort(d.begin(), d.end());
	for (int i = 0; i < d.size(); i++)
		ans = (ans + 1LL * calc(d[i], i) * calcphi(n / d[i])) % P;
	ans = 1LL * ans * power(n, P-2) % P;
	printf("%d\n", ans);
	return 0;
}
