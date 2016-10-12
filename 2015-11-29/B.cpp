#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1010;

double radi[N];

typedef pair<double, double> pdd;
pdd st[N]; // (X, r)

int main () {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf", &radi[i]);
	}
	int top = 0;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		double x = radi[i];
		for (int j = 0; j < top; j++) {
			double r1 = st[j].second;
			double r2 = radi[i];
			double ad = sqrt((r1 + r2) * (r1 + r2) - (r1 - r2) * (r1 - r2));
			double nx = st[j].first + ad;
			if (nx > x) x = nx;
		}
		st[i] = pdd(x, radi[i]);
		++top;
		ans = max(ans, x + radi[i]);
	}
	printf("%.8f\n", ans);
	return 0;
}
