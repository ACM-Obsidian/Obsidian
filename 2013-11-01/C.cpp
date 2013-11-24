#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
#define X first
#define Y second
pii recv[3030];
int arr[3030];
int rec[3030][3030];
int route[3030][3030];
int ansr[3030];

int main ()
{
	freopen("fibsubseq.in", "r", stdin);
	freopen("fibsubseq.out", "w", stdout);
	int n; scanf("%d", &n);
	if (n == 1)
	{
		int x; scanf("%d", &x);
		printf("1\n%d\n", x);
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		int x; scanf("%d", &x);
		recv[i] = pii(x, i + 1);
		arr[i + 1] = x;
	}
	sort(recv, recv + n);
	int ans = 1, e1, e2;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			rec[i][j] = 2;
			route[i][j] = -1;
			int es = arr[j] - arr[i];
			pii q(es, i);
			int l = -1, r = n;
			while (r - l > 1)
			{
				int mid = (l + r) >> 1;
				if (recv[mid] < q) l = mid;
				else r = mid;
			}
			if (l != -1 && recv[l].X == es)
			{
				rec[i][j] = rec[recv[l].Y][i] + 1;
				route[i][j] = recv[l].Y;
			}
			if (rec[i][j] > ans)
			{
				ans = rec[i][j];
				e1 = i, e2 = j;
			}
		}
	}
	printf("%d\n", ans); int max_ansr = 0;
	for (int i = 2; i < ans; i++)
	{
		ansr[max_ansr++] = e2;
		int tt = route[e1][e2];
		e2 = e1, e1 = tt;
	}
	ansr[max_ansr++] = e2;
	ansr[max_ansr++] = e1;
	for (int i = max_ansr - 1; i >= 0; i--)
	{
		printf("%d%c", arr[ansr[i]], " \n"[i == 0]);
	}
	return 0;
}
