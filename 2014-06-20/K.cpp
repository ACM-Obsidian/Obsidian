#include <cstdio>
#include <algorithm>
struct rec {
	int a, b, id;
	long long t;
} a[200000];
int fa, fb, n, res[400000], tmp[400000];
int cmp(rec a, rec b) { return a.t < b.t; }
int main() {
	scanf("%d%d%d", &n, &fa, &fb);
	long long l = 0, r = fa + fb;
	for (int i = 0; i < n; i++)
		scanf("%d%d%lld", &a[i].a, &a[i].b, &a[i].t), r += a[i].a + a[i].b, a[i].id = i+1;
	std::sort(a, a+n, cmp);
	while (l < r) {
		long long mid = l+r>>1;
		long long t = 0, sa = 0, sb = 0, min = ~0ULL>>1;
		int flag = 1;
		for (int i = 0; i < n; i++) {
			if (t + fa + sa + fb + a[i].a > std::min(a[i].t+mid - sb - a[i].b, min)) {
				t += fa + sa + fb + sb, min = ~0ULL>>1;
				sa = sb = 0;
				if (t + fa + fb + a[i].a + a[i].b > a[i].t + mid) {
					flag = 0;
					break;
				}
			}
			sa += a[i].a, sb += a[i].b;
			min = std::min(min, a[i].t+mid - sb);
		}
		if (!flag) l = mid+1;
		else r = mid;
	}
	printf("%lld\n", l);
	long long t = 0, sa = 0, sb = 0, min = ~0ULL>>1;
	int lr = 0, lt = 0;
	for (int i = 0; i < n; i++) {
		if (t + fa + sa + fb + a[i].a > std::min(a[i].t+l - sb - a[i].b, min)) {
			t += fa + sa + fb + sb, min = ~0ULL>>1;
			sa = sb = 0;
			for (int j = 0; j < lt; j++) res[lr++] = -tmp[j];
			for (int j = 0; j < lt; j++) res[lr++] = tmp[j];
			lt = 0;
		}
		sa += a[i].a, sb += a[i].b;
		min = std::min(min, a[i].t+l - sb);
		tmp[lt++] = a[i].id;
	}
	for (int j = 0; j < lt; j++) res[lr++] = -tmp[j];
	for (int j = 0; j < lt; j++) res[lr++] = tmp[j];
	for (int i = 0; i < 2*n; i++) printf("%d%c", res[i], " \n"[i == 2*n-1]);
	return 0;
}
