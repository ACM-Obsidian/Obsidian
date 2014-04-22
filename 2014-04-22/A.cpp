#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 40;

int m;
struct base_m
{
	int arr[N];
	int& operator[] (const int n)
	{
		return arr[n];
	}
	base_m (void)
	{
		memset(arr, 0, sizeof arr);
	}
	base_m (long long a)
	{
		memset(arr, 0, sizeof arr);
		int id = 0;
		while (a)
		{
			arr[id++] = a % m;
			a /= m;
		}
	}
	base_m (long long a, int nm)
	{
		memset(arr, 0, sizeof arr);
		int id = 0;
		while (a)
		{
			if (id == nm)
			{
				arr[id++] = a;
				a = 0;
			}
			arr[id++] = a % m;
			a /= m;
		}
	}
	int sum (void)
	{
		int res = 0;
		for (int i = 0; i < N; i++) res += arr[i];
		return res;
	}
};

int main ()
{
	int a, p, q, r, s, kase = 0; while (scanf("%d %d %d %d %d %d", &a, &m, &p, &q, &r, &s), a)
	{
		printf("Case %d:", ++kase);
		if (m == 1) // very special case
		{
			if (s - r < q - p || s < q)
			{
				printf(" impossible\n");
			}
			else if (p >= r)
			{
				printf(" empty\n");
			}
			else
			{
				long long tl = r - p - 1, tr = s - q;
				if (tr / a <= tl / a) printf(" impossible\n");
				else printf(" %lldA\n", tl / a + 1);
			}
		}
		else
		{
			long long tp = p, tq = q;
			int nm = 0;
			int anslen = -1, rm; base_m ans;
			for (; s - r >= tq - tp && s >= tq; ++nm, tp *= m, tq *= m)
			{
				// printf("NM = %d, (%lld, %lld)\n", nm, tp, tq);
				if (tp >= r)
				{
					// printf("Condition 1\n");
					if (anslen == -1 || nm < anslen)
					{
						anslen = nm;
						rm = nm;
						ans = 0;
					}
				}
				else
				{
					// printf("Condition 2\n");

					long long tpl = r, tpr = s - (tq - tp);

					// printf("TPL = %lld, PL = %lld, TPR = %lld, PR = %lld\n", tpl, (tpl - tp - 1) / a, tpr, (tpr - tp) / a);

					base_m pl((tpl - tp - 1) / a, nm), pr((tpr - tp) / a, nm);
					base_m tans(0);

					/* for (int i = 5; i >= 0; i--)
						printf("%d ", pl[i]);
					printf("\n");
					for (int i = 5; i >= 0; i--)
						printf("%d ", pr[i]);
					printf("\n"); */

					bool ok = true;
					for (int i = N - 1; ok && i >= 0; i--)
					{
						if (i > nm && (pl[i] || pr[i])) ok = false;
						if (pl[i] == pr[i])
						{
							tans[i] = pl[i];
							if (i == 0) ok = false;
						}
						else
						{
							tans[i] = pl[i] + 1;
							for (int j = i - 1; j >= 0; j--) tans[j] = 0;
							break;
						}
					}

					// printf("OK = %d\n", ok);

					if (ok)
					{
						/* for (int i = m; i >= 0; i--)
							printf("%d ", tans[i]);
						printf("\n"); */

						int tl = tans.sum();
						if (anslen == -1 || nm + tl < anslen)
						{
							anslen = nm + tl;
							rm = nm;
							ans = tans;
						}
					}
				}
			}
			if (anslen == -1) printf(" impossible\n");
			else if (anslen == 0) printf(" empty\n");
			else 
			{
				int accu = 0;
				for (int i = rm; i >= 0; i--)
				{
					if (ans[i] != 0)
					{
						if (accu) printf(" %dM", accu), accu = 0;
						printf(" %dA", ans[i]);
					}
					if (i != 0) ++accu;
				}
				if (accu) printf(" %dM", accu);
				printf("\n");
			}
		}
	}
	return 0;
}
