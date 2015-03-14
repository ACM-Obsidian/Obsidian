#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

const int N = 50010;
double arr[N];

inline double C(int n, int m) {
	return arr[n] - arr[n - m] - arr[m];
}
inline double M(int x, int y) {
	int dx = x - 1, dy = y;
	return C(dx + dy, dx);
}

int main () {
	freopen("brother.in", "r", stdin);
	freopen("brother.out", "w", stdout);
	arr[0] = 0;
	for (int i = 1; i < N; i++) {
		arr[i] = arr[i - 1] + log(i);
	}
	int kase; for (scanf("%d", &kase); kase; --kase) {
		int k, m; scanf("%d %d", &k, &m);
		if (k < m) printf("0\n");
		else if (m == 0) printf("1\n");
		else {
			int x = k + 1, y = m;
			double a = M(y, x) - M(x, y);
			printf("%.8lf\n", 1 - exp(a));
		}
	}
	return 0;
}
