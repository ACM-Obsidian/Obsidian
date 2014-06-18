#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const long long pwr = 131, mod = 23333333333333333;
const int N = 2000010;

int n;
char tA[N], tB[N], strA[N], strB[N];
long long hashA[N], hashB[N], tp[N];

inline long long getHash (long long hash[], int l, int r)
{
	if (hash == hashB)
	{
		int tl = n - r - 1, tr = n - l - 1;
		l = tl, r = tr;
	}
	if (l == 0) return hash[r];
	else return (hash[r] - hash[l - 1] * tp[r - l + 1]);
}

int main ()
{
	tp[0] = 1;
	for (int i = 1; i < N; i++) tp[i] = tp[i - 1] * pwr;
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		scanf("%d%s%s", &n, tA, tB);
		strA[0] = '#';
		for (int i = 0; i < n; i++) strA[i * 2 + 1] = tA[i], strA[i * 2 + 2] = '#';
		strB[0] = '#';
		for (int i = 0; i < n; i++) strB[i * 2 + 1] = tB[i], strB[i * 2 + 2] = '#';
		n = n * 2 + 1;
		strA[n] = strB[n] = 0;
		// printf("%s\n%s\n", strA, strB);

		hashA[0] = strA[0];
		for (int i = 1; i < n; i++)
			hashA[i] = (hashA[i - 1] * pwr + strA[i]);
		hashB[0] = strB[n - 1];
		for (int i = 1; i < n; i++)
			hashB[i] = (hashB[i - 1] * pwr + strB[n - 1 - i]);
		int ans = 0;
		for (int i = 0; i < n; i++) if (strA[i] == strB[i])
		{
			int maxlen = min(i, n - 1 - i);
			int l = 0, r = maxlen + 1;
			while (r - l > 1)
			{
				int mid = (l + r) >> 1;
				// printf("1: mid = %d, %lld %lld\n", mid, getHash(hashA, i - mid, i), getHash(hashB, i, i + mid));
				if (getHash(hashA, i - mid, i) == getHash(hashB, i, i + mid)) l = mid;
				else r = mid;
			}
			int tl = l;
			l = 0, r = maxlen + 1;
			while (r - l > 1)
			{
				int mid = (l + r) >> 1;
				// printf("2: mid = %d, %lld %lld\n", mid, getHash(hashA, i, i + mid), getHash(hashB, i - mid, i));
				if (getHash(hashA, i, i + mid) == getHash(hashB, i - mid, i)) l = mid;
				else r = mid;
			}
			int tt = min(tl, l);
			// printf("I = %d, TL = %d, TR = %d\n", i, tl, l);
			ans = max(ans, 2 * tt + 1);
		}
		printf("%d\n", ans / 2);
	}
	return 0;
}
