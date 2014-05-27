#include <cstdio>
#include <algorithm>
#include <vector>
#define P 1051721729
#define Q 410021621
#define maxn 131072
int tmp[262144], *e = tmp + maxn, cnt[120001], cnt2[120001], x[120001], a[120001];
int **sum;
int pwr(int a, int n, int p) {
	int s = 1, t = a;
	for (; n; n >>= 1, t = 1LL * t * t % p)
		if (n & 1) s = 1LL * s * t % p;
	return s;
}
void dft(int *a, int N, int f) {
	int d = maxn / N * f;
	for (int n = N, m, x; m = n / 2, m >= 1; n = m, d *= 2)
		for (int i = 0; i < m; i++)
			for (int j = i; j < N; j += n)
				x = (a[j] - a[j+m] + P) % P, a[j] = (a[j] + a[j+m]) % P, a[j+m] = 1LL * x * e[d*i] % P;
	for (int i = 0, j = 1; j < N-1; j++) {
		for (int k = N/2; k > (i ^= k); k /= 2);
		if (j < i) std::swap(a[i], a[j]);
	}
}
void fft(std::vector<int> a, std::vector<int> b, std::vector<int>& c) {
	c.clear();
	int t = a.size() + b.size();
	int n = 1; while (n < t) n *= 2;
	int *ta = new int[n], *tb = new int[n];
	for (int i = 0; i < n; i++) {
		ta[i] = (i >= a.size() ? 0 : a[i]);
		tb[i] = (i >= b.size() ? 0 : b[i]);
	}
	dft(ta, n, 1), dft(tb, n, 1);
	for (int i = 0; i < n; i++)
		ta[i] = 1LL * ta[i] * tb[i] % P;
	dft(ta, n, -1);
	int rev = pwr(n, P-2, P);
	for (int i = 0; i < n; i++) ta[i] = 1LL * ta[i] * rev % P;
	c.resize(a.size()+b.size()-1);
	for (int i = 0; i < a.size()+b.size()-1; i++)
		c[i] = ta[i];
	delete [] ta;
	delete [] tb;
}
int main() {
	e[0] = 1, e[1] = Q;
	for (int i = 2; i < maxn; i++)
		e[i] = 1LL * e[i-1] * Q % P;
	for (int i = 1; i < maxn; i++)
		e[-i] = e[maxn - i];
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		cnt2[x]++;
	}
	int m = 0;
	for (int i = 1; i <= n; i++)
		if (cnt2[i] > 0) cnt[m++] = cnt2[i];
	std::vector<std::vector<int> > v, v2;
	for (int i = 0; i < m; i++) {
		std::vector<int> tmp;
		tmp.resize(cnt[i]+1);
		for (int j = 0; j <= cnt[i]; j++) tmp[j] = 1;
		v.push_back(tmp);
	}
	while (v.size() > 1) {
		v2.clear();
		for (int i = 0; i < v.size(); i += 2) {
			if (i+1 == v.size()) v2.push_back(v[i]);
			else {
				std::vector<int> tmp;
				fft(v[i], v[i+1], tmp);
				v2.push_back(tmp);
			}
		}
		v = v2;
	}
	for (int i = 0; i <= n; i++) a[i] = v[0][i];
	for (int i = 0; i < m; i++) x[i] = cnt[i]+1;
	std::sort(x, x + m);
	int k = std::unique(x, x + m) - x;
	sum = new int*[k];
	for (int i = 0; i < k; i++) {
		sum[i] = new int[n+1];
		for (int j = n; j >= 0; j--) {
			sum[i][j] = a[j];
			if (j + x[i] <= n) sum[i][j] = (sum[i][j] + sum[i][j + x[i]]) % P;
		}
	}
	int q; scanf("%d", &q);
	while (q--) {
		int u, v, ans; scanf("%d%d", &u, &v);
		if (cnt2[u] == 0) ans = ((v <= n ? a[v] : 0) + a[v-1]) % P;
		else {
			int p = std::lower_bound(x, x + k, cnt2[u]+1) - x;
			ans = ((v <= n ? a[v] : 0) + (sum[p][v-1] - (v <= n ? sum[p][v] : 0) + P) % P) % P;
		}
		printf("%d\n", ans);
	}
	return 0;
}
