#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int M = 100010;
int toc[M + M], n1, n2, m, r;
int endt, endslot;

int pq[M + M], pqmr;

inline int getleast (int n)
{
	int res;
	if (pqmr)
	{
		res = pq[pqmr - 1];
		++toc[res];
		if (toc[res] >= n) --pqmr;
	}
	else
	{
		res = endt;
		++endslot;
		if (endslot >= n) ++endt, endslot = 0;
	}
	return res;
}

int t1[M], t2[M];
long long res1[M], res2[M];

int main ()
{
	scanf("%d %d %d %d", &n1, &n2, &m, &r);
	for (int i = 1; i <= m; i++) scanf("%d %d", &t1[i], &t2[i]);
	
	int inque;
	long long ad;
	
	// L to R (1)
	inque = 0, ad = 0, pqmr = 0;
	for (int i = 1; i <= m; i++)
	{
		inque += t1[i]; 
		toc[i] = min(inque, n1 + 1);
		inque -= toc[i];
	}
	endt = m + 1, endslot = 0;
	if (inque)
	{
		int tt = inque / n1;
		endt += tt;
		endslot = inque - tt * n1;
	}
	for (int i = m; i >= 1; i--)
	{
		if (toc[i] > n1)
		{
			--toc[i];
			int togo = getleast(n1);
			ad += togo - i;
		}
		else if (toc[i] < n1) pq[pqmr++] = i;
		res1[i] = ad;
	}
	
	// R to L (2)
	inque = 0, ad = 0, pqmr = 0;
	for (int i = 1; i <= m + r - 1; i++)
	{
		inque += (i <= m ? t2[i] : 0); 
		toc[i] = min(inque, n2 + 1);
		if (toc[i] < n2 + 1) pq[pqmr++] = i;
		inque -= toc[i];
	}
	reverse(pq, pq + pqmr);
	endt = m + r, endslot = 0;
	if (inque)
	{
		int tt = inque / (n2 + 1);
		endt += tt;
		endslot = inque - tt * (n2 + 1);
	}
	for (int i = 1; i <= m + r - 1; i++)
	{
		if (pqmr && pq[pqmr - 1] <= i) --pqmr;
		if (toc[i] > n2)
		{
			--toc[i];
			int togo = getleast(n2 + 1);
			ad += togo - i;
		}
		if (i - r + 1 >= 1) res2[i - r + 1] = ad;
	}
	
	long long ans = res1[1] + res2[1]; int pl = 1;
	for (int i = 2; i <= m; i++)
		if (res1[i] + res2[i] < ans) ans = res1[i] + res2[i], pl = i;
		
	printf("%d\n", pl);
	// system("pause");
	return 0;
}
