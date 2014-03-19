#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int L, R; double dis;

const int MAXN = 100;

int left[MAXN], right[MAXN];

inline int getBottom(int cur) {
	return (cur - 1) * 3 + 1;
}

vector<double> list;

inline bool check(double now) {
	if (now < 1) return false;
	if (now > (min(getBottom(L), getBottom(R))) - 2) return false;
	bool isCat = false;
	for (int i = 1; i <= L; i++) if (left[i] == 1) {
		double t = getBottom(i);
		if (now > t - 3 && now < t + 0.5) {
			isCat = true;
			break;
		}
	}
	for (int i = 1; i <= R; i++) if (right[i] == 1) {
		double t = getBottom(i);
		if (now > t - 3 && now < t + 0.5) {
			isCat = true;
			break;
		}
	}
	if (isCat) {
		for (int i = 1; i <= L; i++) if (left[i] == -1) {
			double t = getBottom(i);
			if (now > t - 0.5 && now < t + 3) {
				return false;
			}
		}
		for (int i = 1; i <= R; i++) if (right[i] == -1) {
			double t = getBottom(i);
			if (now > t - 0.5 && now < t + 3) {
				return false;
			}
		}
	}
	return true;
}

double area(double x, double y, double fl, double fmid, double fr) {
	return (fl+4*fmid+fr)*(y-x)/6;
}
double area_simpson_solve(double (*f)(double), double x, double mid, double y, double fl, double fmid, double fr, double pre, double zero) {
	double lmid = (x+mid)/2, rmid = (mid+y)/2;
	double flmid = f(lmid), frmid = f(rmid);
	double al = area(x, mid, fl, flmid, fmid), ar = area(mid, y, fmid, frmid, fr);
	if (fabs(al+ar-pre)<zero) return al+ar;
	else return area_simpson_solve(f,x,lmid,mid,fl,flmid,fmid,al,zero) + area_simpson_solve(f,mid,rmid,y,fmid,frmid,fr,ar,zero);
}
double area_simpson(double (*f)(double), double x, double y, double zero=1e-8) {
	double mid=(x+y)/2, fl = f(x), fmid = f(mid), fr = f(y);
	return area_simpson_solve(f,x,mid,y,fl,fmid,fr,area(x,y,fl,fmid,fr),zero);
}
double _a, _b;
double f(double x) {
	double y_ = 2*_a*x+_b;
	return sqrt(1+y_*y_);
}
inline double Cal(double A, double B, double H, double dis) {
	double k;
	if (A == B) {
		k = dis*0.5;
		_a = 4*(A-H)/(dis*dis);
		_b = -2*_a*k;
	} else {
		k = ((A-H)-sqrt((A-H)*(B-H)))/(A-B)*dis;
		_a = (A-B)/(2*k*dis-dis*dis);
		_b = -2*_a*k;
	}
	return area_simpson(f, 0, dis);
}

int main(void) {
	freopen("suspense.in", "r", stdin);
	int kase = 0;
	while (scanf("%d%d%lf", &L, &R, &dis) == 3 && (L || R || dis)) {
		printf("Case %d: ", ++kase);
		list.clear(); memset(left, 0, sizeof left); memset(right, 0, sizeof right);
		for (int i = 1; i <= L; i++) {
			char ch[3]; scanf("%s", ch);
			if (ch[0] == 'C') left[i] = 1;
			if (ch[0] == 'B') left[i] = -1;
		}
		for (int i = 1; i <= R; i++) {
			char ch[3]; scanf("%s", ch);
			if (ch[0] == 'C') right[i] = 1;
			if (ch[0] == 'B') right[i] = -1;
		}
		for (int i = 1; i <= max(L, R); i++) {
			double bottom = getBottom(i);
			list.push_back(bottom - 0.5);
			list.push_back(bottom + 0.5);
			list.push_back(bottom - 3);
			list.push_back(bottom + 3);
		}
		list.push_back(1); list.push_back(max(getBottom(L), getBottom(R)) - 2);
		sort(list.begin(), list.end());
		list.resize(unique(list.begin(), list.end()) - list.begin());
		double minH = -1;
		for (int i = 0; i < list.size(); i++) {
			if (check(list[i])) {
				minH = list[i];
				break;
			}
		}
		minH += 1;
		//printf("%f\n", minH);
		if (minH <= 0) puts("impossible"); else {
			double Ans = Cal(getBottom(L), getBottom(R), minH, dis);
			printf("%.3f\n", Ans);
		}
		puts("");
	}
	return 0;
}

