#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;

int arr[N], que[N], l, r;

void ins (int x)
{
	while (r > l && que[r - 1] > x) --r;
	que[r++] = x;
}
void del (int x)
{
	if (que[l] == x) ++l;
}

int main ()
{
	int n, k; scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	l = 0, r = 0;
	int s;
	for (int i = 0; i < k; i++) ins(arr[i]);
	for (s = 0; s + k < n; s++)
	{
		if (arr[s] != que[l]) break;
		del(arr[s]);
		ins(arr[s + k]);
	}
	sort(arr + s, arr + s + k);
	for (int i = 0; i < n; i++) printf("%d%c", arr[i], " \n"[i == n - 1]);
	return 0;
}
