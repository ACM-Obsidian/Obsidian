#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

struct pt {
	double x, y;
	pt (void) {}
	pt (double _x, double _y) : x(_x), y(_y) {}
	pt operator- (const pt& v) const {
		return pt(x - v.x, y - v.y);
	}
	double operator* (const pt& v) const {
		return x * v.x + y * v.y;
	}
	double operator% (const pt& v) const {
		return x * v.y - y * v.x;
	}
	double len (void) const {
		return sqrt(x * x + y * y);
	}
};

const int N = 100010;
pt ori[N];

double vcos (const pt& a, const pt& b) {
	return a * b / a.len() / b.len();
}
double area (int a, int b, int c) {
	return fabs((ori[b] - ori[a]) % (ori[c] - ori[a]));
}

int main () {
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
	int Kase = 0;
	int n; while (scanf("%d", &n) == 1) {
		++Kase;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &ori[i].x, &ori[i].y);
		}
		pt goat;
		scanf("%lf %lf", &goat.x, &goat.y);
		int ans_a = 0, ans_b = 1, ans_c = 2;
		double t_area = -100;
		for (int a = 0; a < n; a++) {
			int b = (a + 1) % n, c = (a + 2) % n;
			while (1) {
				++c;
				if (c == n) c = 0;
				if (c == a) break;
				if ((ori[a] - ori[c]) % (goat - ori[c]) < -1e-08) continue;
				while (1) {
					int tb = b + 1;
					if (tb == n) tb = 0;
					if ((ori[c] - ori[b]) % (goat - ori[b]) < -1e-08) b = tb;
					else {
						if ((ori[b] - ori[a]) % (goat - ori[a]) >= -1e-08) {
							double t = area(a, b, c);
							if (t > t_area) {
								t_area = t;
								ans_a = a, ans_b = b, ans_c = c;
							}
						}
						if ((ori[tb] - ori[a]) % (goat - ori[a]) >= -1e-08 && area(a, tb, c) > area(a, b, c)) b = tb;
						else break;
					}
				}
			}
		}
		printf("Case #%d: The maximal triangle is formed by vertices %d, %d and %d.\n", Kase, ans_a + 1, ans_b + 1, ans_c + 1);
	}
	return 0;
}
