#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long ll;

int v[N], w[N];
int id[N], p, q;

bool comp (const int& a, const int& b)
{
	return (ll)v[a] * q - (ll)w[a] * p > (ll)v[b] * q - (ll)w[b] * p;
}

int main ()
{
	freopen("k.in", "r", stdin);
	int n, k; scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d %d", &v[i], &w[i]), id[i] = i;
	p = 0, q = 0;
	for (int i = 0; i < k; i++) p += v[i], q += w[i];
	while (1)
	{
		int tp = 0, tq = 0;
		sort(id, id + n, comp);
		for (int i = 0; i < k; i++) tp += v[id[i]], tq += w[id[i]];
		if ((ll)p * tq >= (ll)q * tp) break;
		p = tp, q = tq;
	}
	for (int i = 0; i < k; i++) printf("%d%c", id[i] + 1, " \n"[i == k - 1]);
	return 0;
}
