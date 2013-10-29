#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 11;

int n, c[MAXN], ans;

std::map <unsigned long long,long> Q;
void Dfs(long l1, long l2) {
	if ( l1 >= n) {
		ans++;
		return;
	}

	unsigned long long aim = l1 *10 + l2;long p[10]; memcpy(p,c,sizeof p);
	std::sort(p + 1, p + n + 1);
	for (long i = 1; i <= n; i++) aim = aim * 100 + c[i];

	if( Q.count(aim) ){ ans += Q[aim]; return;}

	long c1 = 0, c2 = 0, w = ans;
	for (long i = 0;i <= 2; i++){
		c1 += i; if(c1 == 1) c2 = 1;else c2 = 3 - c1;

		if( c[l2] - c2 > (n - l1 - 1) * 3 || c[l2] - c2 < 0) continue;
		if( c[l1] - c1 > (n - l2 ) * 3 || c[l1] - c1 < 0) continue;

		c[l2] -= c2, c[l1] -= c1;
		Dfs( l2 == n ? l1 + 1 : l1, l2 == n ? l1 + 2 : l2 +1);
		c[l2] += c2, c[l1] += c1;
	}
	Q[aim] = ans - w;
}

int main(void) {
	freopen("history.in", "r", stdin);
	freopen("history.out", "w", stdout);
	while (scanf("%d", &n) == 1) {
		ans = 0; Q.clear();
		for (int i = 1; i <= n; i++) scanf("%d", c + i);
		Dfs(1, 2);
		printf("%d\n", ans);
	}
	return 0;
}


