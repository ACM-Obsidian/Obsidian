#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int P = 1000000007;

struct Mat {
	int x[2][2];

	Mat& operator*=(const Mat& m) {
		Mat res;

		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				res.x[x][y] = 0;
			}
		}
		for (int k = 0; k < 2; k++) {
			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 2; y++) {
					res.x[x][y] = ((long long)this->x[x][k] * m.x[k][y] + res.x[x][y]) % P;
				}
			}
		}
		*this = res;
		return *this;
	}
};

Mat operator* (const Mat& a, const Mat& b) {
	Mat res = a;
	res *= b;
	return res;
}

const int M = 20010;
int le[M], ri[M], up[M], dn[M];
Mat A[M];

int main () {
	int T; scanf("%d", &T);
	for (; T; --T) {
		long long n; int m;
		long long x0, y0;
		scanf("%lld %d %lld %lld", &n, &m, &x0, &y0);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d", &up[i], &dn[i], &le[i], &ri[i]);
		}
		for (int i = 0; i < m; i++) {
			int t = le[i] + ri[i] + up[i] + dn[i] + 1;
			int t2 = -le[i] + ri[i] + up[i] - dn[i];
			if (t2 < 0) {
				t2 += P;
			}
			A[i].x[0][0] = t;
			A[i].x[0][1] = t2;
			A[i].x[1][0] = 0;
			A[i].x[1][1] = t;
		}
		Mat K;
		K.x[0][0] = K.x[1][1] = 1;
		K.x[0][1] = K.x[1][0] = 0;
		for (int i = 0; i < m; i++) {
			K *= A[i];
		}
		long long r = n / m;
		Mat Ans;
		Ans.x[0][0] = Ans.x[1][1] = 1;
		Ans.x[1][0] = Ans.x[0][1] = 0;
		while (r) {
			if (r & 1) Ans *= K;
			K *= K;
			r >>= 1;
		}
		int remain = n % m;
		for (int i = 0; i < remain; i++) {
			Ans *= A[i];
		}
		x0 = (x0 % P + P) % P;
		y0 = (y0 % P + P) % P;
		int realAns = ((x0 + y0) * Ans.x[0][0] + Ans.x[0][1]) % P;
		printf("%d\n", realAns);
	}
	return 0;
}
