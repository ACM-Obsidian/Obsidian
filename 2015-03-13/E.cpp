#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n;
double ll; // ll should be 1.0 / n

inline pair<int, int> sector (double x, double y) {
	int tx = (int)(x / ll);
	int ty = (int)(y / ll);
	if (x == n) x = n - 1;
	if (y == n) y = n - 1;
	return make_pair(tx, ty);
}

#define X first
#define Y second

bool comp (const pair<pair<double, double>, int>& x, const pair<pair<double, double>, int>& y) {
	pair<int, int> sx, sy;
	sx = sector(x.X.X, x.X.Y);
	sy = sector(y.X.X, y.X.Y);
	if (sx.X != sy.X) return sx.X < sy.X;
	else if (sx.Y != sy.Y) {
		if (sx.X & 1) return sx.Y > sy.Y;
		else return sx.Y < sy.Y;
	}
	else return x.Y < y.Y;
}

pair<pair<double, double>, int> arr[100010];

int main () {
	freopen("polyline.in", "r", stdin);
	freopen("polyline.out", "w", stdout);
	scanf("%d", &n);
	ll = 1.0 / n;
	for (int i = 0; i < n * n; i++) {
		double x, y; scanf("%lf %lf", &x, &y);
		arr[i] = make_pair(make_pair(x, y), i);
	}
	sort(arr, arr + n * n, comp);
	for (int i = 0; i < n * n; i++) printf("%d%c", arr[i].Y + 1, " \n"[i == n * n - 1]);
	return 0;
}
