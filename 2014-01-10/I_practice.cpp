#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
std::map<double, std::pair<int, int> > T;
std::vector<std::pair<int, int> > v;
int a[401][401], ra[401][401];
short f[201][401][401];
int r, c;
char g[201][401][401];
void push(int x1, int y1, int x2, int y2, int d, int ff) {
	int delta = 0;
	if (x1 == x2 && y1 == y2) {
		if (x1+x2 == r && y1+y2 == c) {
			delta = a[x1][y1];
			if (delta > 2) delta = 2;
		} else {
			if (a[x1][y1]) delta++;
			if (ra[x1][y1]) delta++;
		}
	} else if (x1+x2 == r && y1+y2 == c) {
		delta = a[x1][y1];
		if (delta > 2) delta = 2;
		int tmp = ra[x1][y1];
		if (tmp > 2) tmp = 2;
		delta += tmp;
	} else {
		if (a[x1][y1]) delta++;
		if (ra[x1][y1]) delta++;
		if (a[x2][y2]) delta++;
		if (ra[x2][y2]) delta++;
	}
	if (ff + delta > f[x1+y1][x1][x2]) {
		f[x1+y1][x1][x2] = ff + delta;
		g[x1+y1][x1][x2] = d;
	}
}
int main() {
	freopen("identification.in", "r", stdin);
	freopen("identification.out", "w", stdout);
	for (int i = 0; i <= 400; i++)
		for (int j = 0; i+j <= 400; j++)
			T.insert(std::make_pair(i * 97.05276 + j * 128.05858, std::make_pair(i, j)));
	int n; scanf("%d", &n);
	double max;
	std::map<double, std::pair<int, int> >::iterator it;
	for (int i = 0; i < n; i++) {
		double x; scanf("%lf", &x);
		if (x > max) max = x;
		it = T.lower_bound(x - 1e-8);
		if (it != T.end() && fabs(it->first - x) < 1e-8)
			v.push_back(it->second);
	}
	it = T.lower_bound(max - 1e-8);
	r = it->second.first, c = it->second.second;
	for (int i = 0; i < v.size(); i++)
		if (v[i].first <= r && v[i].second <= c)
			a[v[i].first][v[i].second]++, ra[r-v[i].first][c-v[i].second]++;
	memset(f, 0xC0, sizeof f);
	f[0][0][r] = 0;
	int ans = -1;
	for (int i = 0; i < (r+c)/2; i++) {
		int il = 0, ir = i;
		if (i-c > 0) il = i-c;
		if (ir > r) ir = r;
		for (int x1 = il; x1 <= ir; x1++)
			for (int x2 = r-ir; x2 <= r-il; x2++) {
				int y1 = i-x1, y2 = r+c-i-x2;
				if (x1 < r && x2 > 0) push(x1+1, y1, x2-1, y2, 0, f[i][x1][x2]);
				if (x1 < r && y2 > 0) push(x1+1, y1, x2, y2-1, 1, f[i][x1][x2]);
				if (y1 < c && x2 > 0) push(x1, y1+1, x2-1, y2, 2, f[i][x1][x2]);
				if (y1 < c && y2 > 0) push(x1, y1+1, x2, y2-1, 3, f[i][x1][x2]);
			}
	}
	std::string str = "";
	int i = (r+c)/2, x1, x2;
	int il = 0, ir = i;
	if (i-c > 0) il = i-c;
	if (ir > r) ir = r;
	if (!(r+c&1)) {
		for (int x = il; x <= ir; x++)
			if (f[i][x][x] > ans) ans = f[i][x][x], x1 = x2 = x;
	} else {
		for (int x = il; x <= ir; x++) {
			if (i-x < c && f[i][x][x] > ans) ans = f[i][x][x], x1 = x2 = x, str = "Q";
			if (x < r && f[i][x][x+1] > ans) ans = f[i][x][x+1], x1 = x, x2 = x+1, str = "P";
		}
	}
	for (; i > 0; i--)
		switch (g[i][x1][x2]) {
			case 0: x1--, x2++; str = "P" + str + "P"; break;
			case 1: x1--; str = "P" + str + "Q"; break;
			case 2: x2++; str = "Q" + str + "P"; break;
			case 3: str = "Q" + str + "Q"; break;
		}
	puts(str.c_str());
	return 0;
}
