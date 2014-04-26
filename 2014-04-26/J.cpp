#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <complex>

#define pi 3.14159265358979324
using namespace std;
typedef std::complex<double> Complex;

const int MAXN = 200010;

struct Edge {
	int y; Edge *next, *opt; int flag;
}*a[MAXN], POOL[MAXN << 1], *data = POOL;

int n, sum[MAXN], stack[MAXN], top, Ans[MAXN], M, isleaf[MAXN];
Complex *e, x[262144], y[262144];

void fft_prepare(int maxn, Complex *&e) {
	e = new Complex[2*maxn-1];
	e += maxn-1;
	e[0] = Complex(1, 0);
	for (int i = 1; i < maxn; i <<= 1)
		e[i] = Complex(cos(2*pi*i/maxn), sin(2*pi*i/maxn));
	for (int i = 3; i < maxn; i++)
		if ((i & -i) != i) e[i] = e[i - (i&-i)] * e[i&-i];
	for (int i = 1; i < maxn; i++) e[-i] = e[maxn-i];
}

void dft(Complex *a, int N, int f, Complex *e, int maxn) {
	int d = maxn / N * f;
	Complex x;
	for (int n = N, m; m = n / 2, m >= 1; n = m, d *= 2)
		for (int i = 0; i < m; i++)
			for (int j = i; j < N; j += n)
				x = a[j] - a[j+m], a[j] += a[j+m], a[j+m] = x * e[d*i];
	for (int i = 0, j = 1; j < N-1; j++) {
		for (int k = N/2; k > (i ^= k); k /= 2);
		if (j < i) std::swap(a[i], a[j]);
	}
}

void FFT(const vector<int>& _a, const vector<int>& _b, vector<int>& s) {
	s.clear();
	if (!_a.size() || !_b.size()) return;
	int S = *max_element(_a.begin(), _a.end()) + *max_element(_b.begin(), _b.end());
	int t = 1; while (t <= S) t *= 2;
	for (int i = 0; i < t; i++) x[i] = 0, y[i] = 0;
	for (int i = 0; i < (int)_a.size(); i++) x[_a[i]] = 1;
	for (int i = 0; i < (int)_b.size(); i++) y[_b[i]] = 1;
	dft(x, t, 1, e, M);
	dft(y, t, 1, e, M);
	for (int i = 0; i < t; i++) x[i] *= y[i];
	dft(x, t, -1, e, M);
	for (int i = 0; i < t; i++)
		if (std::abs(x[i].real()) > 0.5) s.push_back(i);
}

inline void CalSum(int u, int father) {
	stack[++top] = u; sum[u] = 1;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag && p->y != father) {
		CalSum(p->y, u);
		sum[u] += sum[p->y];
	}
}

vector<vector<int> > list[2]; vector<int> tmp;

inline void getDepth(int u, int father, int deep) {
	for (Edge *p = a[u]; p; p = p->next) if (p->flag && p->y != father) {
		getDepth(p->y, u, deep + 1);
	}
	if (isleaf[u]) tmp.push_back(deep);
}

inline void Dfs(int u) {
	top = 0; CalSum(u, 0);
	if (top == 1) return;
	int mid = 0, best = ~0u>>1;
	for (int i = 1; i <= top; i++) {
		int Max = sum[u] - sum[stack[i]];
		for (Edge *p = a[stack[i]]; p; p = p->next) if (p->flag && sum[p->y] < sum[stack[i]]) {
			Max = max(Max, sum[p->y]);
		}
		if (Max < best) best = Max, mid = stack[i];
	}
	//printf("@%d: ", mid); for (int i = 1; i <= top; i++) printf("%d ", stack[i]); puts("");
	list[0].clear(); list[1].clear();
	for (Edge *p = a[mid]; p; p = p->next) if (p->flag) {
		tmp.clear();
		getDepth(p->y, mid, 1);
		list[0].push_back(tmp);
		if (isleaf[mid]) {
			for (int i = 0; i < (int)tmp.size(); ++i) Ans[tmp[i]] = 1;
		}
	}
	/*
	for (int i = 0; i < (int)list[0].size(); i++) {
		for (int j = 0; j < (int)list[0][i].size(); j++) printf("%d ", list[0][i][j]);
		puts("");
	}
	*/
	int now = 0, next = 1;
	while (list[now].size() > 1) {
		for (int i = list[now].size() - 1; i >= 1; i -= 2) {
			FFT(list[now][i], list[now][i - 1], tmp);
			for (int j = 0; j < (int)tmp.size(); j++) Ans[tmp[j]] = 1;
			for (int j = 0; j < (int)list[now][i].size(); j++) {
				list[now][i - 1].push_back(list[now][i][j]);
			}
			list[next].push_back(list[now][i - 1]);
			list[now].pop_back();
			list[now].pop_back();
		}
		if (list[now].size() == 1) list[next].push_back(list[now][0]), list[now].clear();
		now ^= 1, next ^= 1;
	}
	for (Edge *p = a[mid]; p; p = p->next) if (p->flag) {
		p->flag = p->opt->flag = 0;
		Dfs(p->y);
	}
}

inline void getLeaf(int u) {
	int cnt = 0;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
		++cnt;
		p->opt->flag = false;
		getLeaf(p->y);
		p->opt->flag = 1;
	}
	if (cnt == 0 || (u == 1 && cnt == 1)) isleaf[u] = 1;
}

int main(void) {
//	freopen("in", "r", stdin);
//	freopen("ou", "w", stdout);
	scanf("%d", &n);
	M = 1; while (M <= n) M *= 2;
	fft_prepare(M, e);
	for (int i = 1; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		Edge *tmp = data++;
		tmp->y = y; tmp->next = a[x]; a[x] = tmp;
		tmp = data++;
		tmp->y = x; tmp->next = a[y]; a[y] = tmp;
		a[x]->flag = a[y]->flag = true;
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}
	getLeaf(1);
	Dfs(1);
	int cnt = 0;
	for (int i = 1; i <= n; i++) if (Ans[i]) cnt++;
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) if (Ans[i]) printf("%d\n", i);
	return 0;
}

