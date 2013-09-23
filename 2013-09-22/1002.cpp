#include <cstdio>
#include <algorithm>
using std::swap;
int f[10001], n, e, a[10000], A, B;
void construct(int *a, int min, int n, int e) {
	if (n == 0) return;
	if (n == 1) {
		a[min] = min;
		return;
	}
	int te = e - (n-1);
	int l = 0, r = (n-1)/2;
	for (int mid; mid = l+r>>1, l < r; )
		if (f[mid] + f[n-1-mid] > te) l = mid+1;
		else r = mid;
	if (l == 0 && f[n-1] > te) construct(a, min, n-1, te), a[min] = 0;
	else {
		construct(a, min, l, f[l]);
		construct(a, min+l+1, n-1-l, te-f[l]);
		a[min+l] = min+l;
	}
	int piv = (min*A+(min+n-1)*B)/(A+B);
	int tmp = a[min+l]; a[min+l] = a[min+n-1]; a[min+n-1] = a[piv]; a[piv] = tmp;
}
int T;
bool less_than(int x, int y) {
	T++;
	return x < y;
}
void work(int *array, int l, int r) {
	if (l >= r) return;
	swap(array[(l * A + r * B) / (A + B)], array[r]);
	int index = l;
	for (int i = l; i < r; i++)
		if (less_than(array[i], array[r]))
			swap(array[index++], array[i]);
	swap(array[r], array[index]);
	work(array, l, index - 1);
	work(array, index + 1, r);
}
int main() {
	f[1] = 0;
	for (int i = 2; i <= 10000; i++)
		f[i] = f[(i-1)/2] + f[i/2] + i-1;
	for (; scanf("%d%d%d%d", &n, &e, &A, &B) != EOF; ) {
		T = 0;
		if (e < f[n] || e > n*(n-1)/2) {
			puts("NOWAY");
			continue;
		}
		construct(a, 0, n, e);
		for (int i = 0; i < n-1; i++) printf("%d ", a[i]+1); printf("%d\n", a[n-1]+1);
		work(a, 0, n-1);
	}
	return 0;
}
