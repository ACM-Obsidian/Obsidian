#include <cstdio>
#include <algorithm>
int a[1000000], n, k;
int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 0; i < 2*n*k; i++) scanf("%d", &a[i]);
		std::sort(a, a+2*n*k);
		int l = 0, r = a[2*n*k-1]-a[0];
		while (l < r) {
			int mid = l+r>>1;
			int t = 0, cnt = 0, flag = 1;
			for (int i = 0, j = 0; i < 2*n*k; i = j) {
				j++; while (j < 2*n*k && a[j]-a[j-1] <= mid) j++;
				while (j >= 2*k*t+2) {
					if ((2*k*t+2-i)/2+cnt < t+1) flag = 0;
					t++;
				}
				if (!flag) break;
				cnt += (j-i)/2;
			}
			if (flag) r = mid;
			else l = mid+1;
		}
		printf("%d\n", l);
	}
	return 0;
}
