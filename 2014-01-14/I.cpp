#include <cstdio>
struct intv {
	int l, r;
} a[100001];
char ret[5];
int main() {
	int p, v; scanf("%d%d", &p, &v);
	for (int i = 0; i <= v; i++)
		a[i].l = 0, a[i].r = p;
	int k = 0;
	while (1) {
		long long cnt = 0;
		for (int i = 0; i <= v; i++)
			cnt += a[i].r - a[i].l + 1;
		if (cnt == 1) {
			for (int i = 0; i <= v; i++)
				if (a[i].l == a[i].r)
					printf("answer %d\n", a[i].l + k*i);
			fflush(stdout);
			break;
		}
		int l = 0, r = 1000000000;
		while (l < r) {
			int mid = l+r>>1;
			long long cnt2 = 0;
			for (int i = 0; i <= v; i++) {
				int tr = a[i].r;
				if (mid - k*i < tr) tr = mid - k*i;
				if (tr >= a[i].l) cnt2 += tr - a[i].l + 1;
			}
			if (cnt2 < cnt/2) l = mid+1;
			else r = mid;
		}
		printf("check 0 %d\n", l);
		fflush(stdout);
		scanf("%s", ret);
		if (ret[0] == 'Y')
			for (int i = 0; i <= v; i++) {
				if (l - k*i < a[i].r) a[i].r = l - k*i;
				if (a[i].r < a[i].l) a[i].r = a[i].l-1;
			}
		else
			for (int i = 0; i <= v; i++) {
				if (l+1 - k*i > a[i].l) a[i].l = l+1 - k*i;
				if (a[i].r < a[i].l) a[i].r = a[i].l-1;
			}
		k++;
	}
	return 0;
}
