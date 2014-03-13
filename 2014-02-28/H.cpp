#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define x first
#define y second
typedef std::pair<double, double> point;
const double eps = 1e-10;
point operator +(point a, point b) {
	return point(a.first+b.first, a.second+b.second);
}
point operator -(point a, point b) {
	return point(a.first-b.first, a.second-b.second);
}
point operator *(point a, double b) {
	return point(a.first*b, a.second*b);
}
double mult(point a, point b) {
	return a.first*b.first+a.second*b.second;
}
double cross(point a, point b) {
	return a.first*b.second-a.second*b.first;
}
int parallel(point a, point b) {
	return mult(a,a) < eps*eps || mult(b,b) < eps*eps || cross(a,b)*cross(a,b)/(mult(a,a)*mult(b,b)) < eps*eps;
}
int line_line_cross(point a1, point s1, point a2, point s2, point *res) {
	if (parallel(s1, s2))
		if (parallel(a2-a1, s1))
			return -1;
		else
			return 0;
	double k1 = cross(a2-a1,s2)/cross(s1,s2);
	*res = a1+s1*k1;
	return 1;
}
point a[100], b[100];
int n;
void solve() {
	for (int i = 0; i < n; i++)
		scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		std::vector<double> tmp;
		tmp.push_back(0), tmp.push_back(sqrt(mult(b[i]-a[i],b[i]-a[i])));
		for (int j = 0; j < n; j++) if (i != j) {
			point p;
			int ret = line_line_cross(a[i], b[i]-a[i], a[j], b[j]-a[j], &p);
			if (ret == 1 && mult(p-a[i],p-b[i]) < 0 && mult(p-a[j],p-b[j])<0)
				tmp.push_back(mult(p-a[i],b[i]-a[i])/sqrt(mult(b[i]-a[i],b[i]-a[i])));
		}
		std::sort(tmp.begin(), tmp.end());
		if (tmp.size() == 2) cnt += int((tmp[1]-tmp[0])/50+1e-8)+1;
		else {
			cnt += int((tmp[1]-tmp[0]+25)/50+1e-8)+int((tmp[tmp.size()-1]-tmp[tmp.size()-2]+25)/50+1e-8);
			for (int i = 1; i+2 < tmp.size(); i++)
				cnt += int((tmp[i+1]-tmp[i])/50+1e-8);
		}
	}
	printf("Trees = %d\n", cnt);
}
int main() {
	freopen("streets.in", "r", stdin);
	int _ = 0;
	while (scanf("%d", &n), n) printf("Map %d\n", ++_), solve();
	return 0;
}
