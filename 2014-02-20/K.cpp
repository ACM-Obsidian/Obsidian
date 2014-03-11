#include <cstdio>
#include <algorithm>
int main() {
	freopen("kids.in", "r", stdin);
	freopen("kids.out", "w", stdout);
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	int g = std::__gcd(b, c);
	int b2 = c / g, c2 = b / g;
	int m = (a+1) / b2 + ((a+1) % b2 > 0);
	int n = (d+1) / c2 + ((d+1) % c2 > 0);
	int k = std::max(std::max(m, n), g);
	if (k & 1 && (a & 1 && b2 & 1 || d & 1 && c2 & 1)) k++;
	m = b2 * k, n = c2 * k;
	printf("%d %d\n", m, n);
	for (int i = 0; i < m; i++)
		for (int j = 1; j <= a/2; j++)
			printf("%d %d\n", i+1, (i+j)%m+1);
	if (a & 1)
		for (int i = 0; i < m/2; i++)
			printf("%d %d\n", i+1, i+m/2+1);
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= d/2; j++)
			printf("%d %d\n", i+m+1, (i+j)%n+m+1);
	if (d & 1)
		for (int i = 0; i < n/2; i++)
			printf("%d %d\n", i+m+1, i+n/2+m+1);
	for (int i = 0; i < b2; i++)
		for (int j = 0; j < k; j++)
			for (int p = 0; p < c2; p++)
				for (int q = 0; q < g; q++)
					printf("%d %d\n", i*k+j+1, p*k+(j+q)%k+m+1);
	return 0;
}
