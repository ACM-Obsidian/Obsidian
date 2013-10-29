#include <cstdio>
#include <cstring>
#include <queue>
int a, b, c;
long long h, f[100000];
std::priority_queue<long long> q;
int main() {
	freopen("elevator.in","r",stdin);
	freopen("elevator.out","w",stdout);
	scanf("%lld%d%d%d", &h, &a, &b, &c);
	if (b < a) a ^= b, b ^= a, a ^= b;
	if (c < a) a ^= c, c ^= a, a ^= c;
	if (c < b) b ^= c, c ^= b, b ^= c;
	memset(f, -1, sizeof f);
	f[0] = 0;
	if (b%a != 0)
		q.push(-b), f[b%a] = b;
	if (b%a != c%a && c%a != 0)
		q.push(-c), f[c%a] = c;
	for (; !q.empty(); q.pop()) {
		long long t = -q.top();
		if (f[(t+b)%a] == -1)
			q.push(-t-b), f[(t+b)%a] = t+b;
		if (f[(t+c)%a] == -1)
			q.push(-t-c), f[(t+c)%a] = t+c;
	}
	long long ans = 0;
	for (int i = 0; i < a; i++)
		if (f[i] != -1 && h-1 >= f[i]) ans += (h-1-f[i])/a+1;
	printf("%lld\n", ans);
	return 0;
}
