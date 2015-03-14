#include <cstdio>
#include <vector>
#include <algorithm>
int pwr[10], tmp[10], f[6561][4];
std::vector<int> v, v1;
int main() {
	freopen("wisemen.in", "r", stdin);
	freopen("wisemen.out", "w", stdout);
	int n, b, w, q;
	scanf("%d%d%d%d", &n, &b, &w, &q);
	pwr[0] = 1;
	for (int i = 1; i <= n; i++) pwr[i] = pwr[i-1] * 3;
	for (int i = 0; i < pwr[n]; i++) {
		int nb = 0, nw = 0;
		for (int j = 0; j < n; j++) {
			int t = i / pwr[j] % 3;
			if (t == 0) nb += 2;
			else if (t == 1) nw++, nb++;
			else nw += 2;
		}
		if (nb <= b && nw <= w)
			v.push_back(i);
	}
	for (int i = 1; i <= q; i++) {
		v1.clear();
		int who = (-i % n + n) % n;
		for (int j = 0; j < pwr[n-1]; j++)
			f[j][0] = 0;
		for (int j = 0; j < v.size(); j++) {
			int k = v[j] % pwr[who] + v[j] / pwr[who + 1] * pwr[who];
			f[k][++f[k][0]] = v[j];
		}
		for (int j = 0; j < pwr[n-1]; j++)
			if (f[j][0] > 1 && i < q || f[j][0] == 1 && i == q)
				for (int k = 1; k <= f[j][0]; k++)
					v1.push_back(f[j][k]);
		v = v1;
	}
	if (v.empty())
		puts("Impossible");
	else {
		int ans = *std::min_element(v.begin(), v.end());
		const char *repr[3] = {"BB", "BW", "WW"};
		for (int i = n-1; i >= 0; i--)
			printf("%s%c", repr[ans / pwr[i] % 3], " \n"[i == 0]);
	}
	return 0;
}
