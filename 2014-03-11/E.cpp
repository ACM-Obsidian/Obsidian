#include <cstdio>
#include <cmath>
const double pi = 3.14159265358979324;
const int S = 20220, T = 65820;
int l[100], d[100], m[100], n, w, h;
void solve() {
	scanf("%d%d", &w, &h);
	for (int i = 0; i < n-1; i++) scanf("%d%d", &m[i], &d[i]);
	scanf("%d", &m[n-1]);
	l[0] = 0;
	for (int i = 1; i < n; i++) l[i] = l[i-1] + d[i-1] + w;
	int x;
	while (scanf("%d", &x), x) {
		printf("Apartment %d: ", x);
		int num = x%100, fl = x/100;
		if (num < 1 || num > n || fl < 1 || fl > m[num-1]) {
			puts("Does not exist\n");
			continue;
		}
		num--, fl--;
		double ll = 0, rr = pi;
		for (int i = 0; i < num; i++)
			if (m[i] > fl) {
				double th = atan2((m[i] - fl) * h, l[num] - l[i] - w);
				if (th > ll) ll = th;
			}
		for (int i = num+1; i < n; i++)
			if (m[i] > fl) {
				double th = atan2((m[i] - fl) * h, l[num] - l[i] + w);
				if (th < rr) rr = th;
			}
		int lt = int(ll / pi * (T-S) + S + 1e-8), rt = int(rr / pi * (T-S) + S + 1e-8);
		printf("%02d:%02d:%02d - %02d:%02d:%02d\n\n", lt/3600, (lt/60)%60, lt%60, rt/3600, (rt/60)%60, rt%60);
	}
}
int main() {
	int _ = 0;
	while (scanf("%d", &n), n)
		printf("Apartment Complex: %d\n\n", ++_), solve();
	return 0;
}
