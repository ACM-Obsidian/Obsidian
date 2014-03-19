#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
const double pi = 3.14159265358979324;
const double eps = 1e-10;
std::vector<std::pair<int, int> > b[6];
std::pair<int, int> cur[6];
int n, a[6], ans, u[6];
template<class T> std::pair<T,T> operator + (std::pair<T,T> a, std::pair<T,T> b) {
	return std::make_pair(a.first+b.first, a.second+b.second);
}
template<class T> std::pair<T,T> operator - (std::pair<T,T> a, std::pair<T,T> b) {
	return std::make_pair(a.first-b.first, a.second-b.second);
}
template<class T> std::pair<T,T> operator * (std::pair<T,T> a, double b) {
	return std::make_pair(a.first*b, a.second*b);
}
template<class T> T operator % (std::pair<T,T> a, std::pair<T,T> b) {
	return a.first*b.second-a.second*b.first;
}
std::pair<double,double> rotate(std::pair<double,double> a, double th) {
	return std::make_pair(a.first*cos(th)-a.second*sin(th), a.first*sin(th)+a.second*cos(th));
}
std::pair<double,double> line_line_cross(std::pair<double,double> a1, std::pair<double,double> s1, std::pair<double,double> a2, std::pair<double,double> s2) {
	double k1 = (a2-a1)%s2/(s1%s2);
	return a1+s1*k1;
}
int area() {
	int s = 0;
	for (int i = 0; i+1 < n-1; i++)
		s += cur[i] % cur[i+1];
	return s;
}
int abs_area() {
	int s = 0;
	for (int i = 0; i+1 < n-1; i++)
		s += abs(cur[i] % cur[i+1]);
	return s;
}
bool valid() {
	return area() == abs_area();
}
void dfs(int k) {
	if (k > 2 && (cur[k-1]-cur[k-2])%cur[k-1]>0) return;
	if (k == n-2) {
		int i = 1; while (u[i]) i++;
		double A = a[i];
		i++; while (u[i]) i++;
		double B = a[i];
		double C = sqrt(cur[k-1].first * cur[k-1].first + cur[k-1].second * cur[k-1].second);
		double f = (A*A+B*B-C*C) / (2*A*B);
		if (fabs(f) > 1+eps) return;
		else if (fabs(f-1) < eps)
			if (f == -1) {
				std::pair<double,double> p = cur[k-1]*(B/C);
				if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
					cur[k].first = round(p.first), cur[k].second = round(p.second);
					if (valid() && area() > ans) ans = area();
				}
			} else {
				std::pair<double,double> p = cur[k-1]*(-B/C);
				if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
					cur[k].first = round(p.first), cur[k].second = round(p.second);
					if (valid() && area() > ans) ans = area();
				}
			}
		else {
			double th1 = acos((A*A+C*C-B*B)/(2*A*C)), th2 = acos((B*B+C*C-A*A)/(2*B*C));
			std::pair<double, double> s1 = rotate(cur[k-1], th1), s2 = rotate(cur[k-1], pi-th2), p = line_line_cross(std::make_pair(0.0, 0.0), s1, cur[k-1], s2);
			if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
				cur[k].first = round(p.first), cur[k].second = round(p.second);
				if (valid() && area() > ans) ans = area();
			}
			s1 = rotate(cur[k-1], -th1), s2 = rotate(cur[k-1], th2-pi), p = line_line_cross(std::make_pair(0.0, 0.0), s1, cur[k-1], s2);
			if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
				cur[k].first = round(p.first), cur[k].second = round(p.second);
				if (valid() && area() > ans) ans = area();
			}
			std::swap(th1, th2);
			s1 = rotate(cur[k-1], th1), s2 = rotate(cur[k-1], pi-th2), p = line_line_cross(std::make_pair(0.0, 0.0), s1, cur[k-1], s2);
			if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
				cur[k].first = round(p.first), cur[k].second = round(p.second);
				if (valid() && area() > ans) ans = area();
			}
			s1 = rotate(cur[k-1], -th1), s2 = rotate(cur[k-1], th2-pi), p = line_line_cross(std::make_pair(0.0, 0.0), s1, cur[k-1], s2);
			if (fabs(p.first-round(p.first)) < 1e-8 && fabs(p.second-round(p.second)) < 1e-8) {
				cur[k].first = round(p.first), cur[k].second = round(p.second);
				if (valid() && area() > ans) ans = area();
			}
		}
	} else {
		for (int j = 0; j < n; j++) if (j == 0 && k == 0 || k != 0 && j > 0 && !u[j])
			for (int i = 0; i < b[j].size(); i++)
				if (k == 0 || (cur[k-1]-(k==1?std::pair<int,int>(0,0):cur[k-2])) % b[j][i] >= 0) {
					if (k == 0) cur[k] = b[j][i];
					else cur[k] = b[j][i]+cur[k-1];
					u[j] = 1;
					dfs(k+1);
					u[j] = 0;
				}
	}
}
void solve() {
	for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i] = -a[i];
	std::sort(a, a+n);
	for (int i = 0; i < n; i++) a[i] = -a[i];
	for (int i = 0; i < n; i++) {
		b[i].clear();
		for (int j = 0; j < a[i]; j++) {
			int t = int(sqrt(a[i]*a[i]-j*j)+1e-8);
			if (t*t+j*j == a[i]*a[i]) {
				b[i].push_back(std::make_pair(j, t));
				if (i > 0) {
					b[i].push_back(std::make_pair(-j, -t));
					b[i].push_back(std::make_pair(t, -j));
					b[i].push_back(std::make_pair(-t, j));
				}
			}
		}
	}
	ans = -1;
	dfs(0);
	if (ans <= 0) puts("-1");
	else printf("%d\n", ans/2);
}
int main() {
	freopen("G.txt", "r", stdin);
	while (scanf("%d", &n), n) solve();
	return 0;
}
