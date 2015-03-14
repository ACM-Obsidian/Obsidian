#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
#include <cmath>
#define R(l, r) ((rand() % (r) - (l) + 1) + (l))

using namespace std;

const double PI = 3.14159265358979324;

set<pair<int, int> > S;
vector<pair<int, int> > a;
int n;

inline int co_line(const pair<int, int> a, const pair<int, int> b, const pair<int, int> c) {
	if ((a.first - b.first) * (c.second - b.second) - (a.second - b.second) * (c.first - b.first) == 0) return true;
	return false;
}

inline int valid(const vector<pair<int, int> >& a) {
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < j; k++) {
				if (co_line(a[i], a[j], a[k])) {
					printf("%d %d, %d %d, %d %d\n", a[i].first, a[i].second, a[j].first, a[j].second, a[k].first, a[k].second);
					return false;
				}
			}
		}
	return true;
}

int main(void) {
	srand(time(0));
	int kase = 0; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) {
		printf("Case #%d: ", _);
		S.clear(); a.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			double A = PI * 2 * (double)i / n;
			double r = n * (1 - (double)((i % 10) * (i % 10)) / 100);
			double xx = r * cos(A);
			double yy = r * sin(A);
			int x = (int)(xx), y = (int)(yy);
			a.push_back(make_pair(x, y));
		}
		printf("%d\n", valid(a));
	}
	return 0;
}

