#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

long long ans[100010];

int main ()
{
	freopen("audit.in", "r", stdin);
	freopen("audit.out", "w", stdout);

	long long H, P, C, K, N; scanf("%lld %lld %lld %lld %lld", &H, &P, &C, &K, &N);
	long long cr = P * K * C;
	long long rh = N / cr;
	if (rh)
	{
		H -= rh * K * C; N -= rh * cr;
	}
	// printf("REDUCE: %lld %lld %lld %lld %lld\n", H, P, C, K, N);

	long long th = H / (C * K);
	if (th)
	{
		for (int i = 0; i < C; i++) ans[i] += th * P * K;
		H -= th * C * K;
	}
	int nC = 0;
	while (H >= K) ans[nC] += P * K, H -= K, nC++;
	ans[nC] += P * H;
	// for (int i = 0; i < C; i++) printf("%lld%c", ans[i], " \n"[i == C - 1]);

	long long tb = N / P;
	// printf("tb = %lld\n", tb);
	nC = 0;
	if (tb)
	{
		N -= tb * P;
		while (tb >= K) ans[nC] -= P * K, tb -= K, nC++;//, printf("tb = %lld, nC = %d\n", tb, nC);
		ans[nC] -= P * tb;
	}
	ans[nC] -= N;

	for (int i = 0; i < C; i++) printf("%lld%c", ans[i], " \n"[i == C - 1]);
	return 0;
}
