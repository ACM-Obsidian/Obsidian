#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
typedef long long LL;
typedef unsigned long long ULL;

template <class T> inline T modplus(T a,T b,T m){
	if(b<m-a)return a+b;
	else return b-(m-a);
}
inline ULL modmul(ULL x,ULL y,ULL m){
	register ULL t=x,ans=0;
	for(;y;y>>=1,t=modplus(t,t,m))
		if(y&1)ans=modplus(ans,t,m);
	return ans;
}
template <class T> inline T power(T n,T k,T r){
	register T t=n,s=1;
	for(;k;k>>=1,t=modmul(t,t,r))if(k&1)s=modmul(s,t,r);
	return s;
}

ULL sqrtofminus3(ULL p) {
	ULL r;
	while (1) {
		r = ((((ULL)rand())<<31) + rand() << 31) + rand();
		r %= p;
		if (power((modmul(r,r,p)+3)%p, (p-1)/2, p) != 1)
			break;
	}
	ULL a1 = r, a2 = 1, s1 = 1, s2 = 0, c = (modmul(r,r,p)+3)%p;
	for (ULL n = (p+1)/2; n; n>>=1) {
		if (n & 1) {
			ULL t1 = (modmul(a1,s1,p)+modmul(modmul(a2,s2,p),c,p))%p;
			ULL t2 = (modmul(a1,s2,p)+modmul(a2,s1,p))%p;
			s1 = t1, s2 = t2;
		}
		ULL t1 = (modmul(a1,a1,p)+modmul(modmul(a2,a2,p),c,p))%p;
		ULL t2 = (modmul(a1,a2,p)+modmul(a2,a1,p))%p;
		a1 = t1, a2 = t2;
	}
	return s1;
}

std::pair<LL, LL> mul(std::pair<LL, LL> a, std::pair<LL, LL> b) {
	return std::make_pair(a.first*b.first-a.second*b.second*3, a.first*b.second+a.second*b.first);
}
std::pair<LL, LL> mod(std::pair<LL, LL> a, std::pair<LL, LL> b) {
	long double n1 = 1.0L*a.first*b.first+3.0L*a.second*b.second, n2 = -1.0L*a.first*b.second+1.0L*a.second*b.first, d = 1.0L*b.first*b.first+3.0L*b.second*b.second;
	LL c1 = (LL)round(n1/d), c2 = (LL)round(n2/d);
	std::pair<LL, LL> res;
	res.first = a.first-(b.first*c1-b.second*c2*3);
	res.second = a.second-(b.first*c2+b.second*c1);
	return res;
}
std::pair<LL, LL> primsol(ULL p) {
	std::pair<LL, LL> p1, p2;
	p1.first = p, p1.second = 0;
	p2.first = sqrtofminus3(p), p2.second = 1;
	while (p2.first || p2.second) {
		std::pair<LL, LL> p3 = mod(p1, p2);
		p1 = p2, p2 = p3;
	}
	return p1;
}

std::vector<std::pair<LL, LL> > sol3kp1(ULL p, int k) {
	std::pair<LL, LL> prim = primsol(p);
	std::vector<std::pair<LL, LL> > res;
	for (int i = 0; i <= (k-1)/2; i++) {
		std::pair<LL, LL> tmp(1, 0), tmp2;
		for (int j = 0; j < i; j++) tmp = mul(tmp, std::pair<LL, LL>(p, 0));
		tmp2 = tmp;
		for (int j = i*2; j < k; j++) tmp2 = mul(tmp2, prim);
		res.push_back(tmp2);
		tmp2 = tmp;
		for (int j = i*2; j < k; j++) tmp2 = mul(tmp2, std::pair<LL, LL>(prim.first, -prim.second));
		res.push_back(tmp2);
	}
	if (!(k & 1)) {
		std::pair<LL, LL> tmp(1, 0);
		for (int j = 0; j < k/2; j++) tmp = mul(tmp, std::pair<LL, LL>(p, 0));
		res.push_back(tmp);
	}
	return res;
}

std::vector<std::pair<LL, LL> > cartesianprod(std::vector<std::pair<LL, LL> > v1, std::vector<std::pair<LL, LL> > v2) {
	std::vector<std::pair<LL, LL> > res;
	for (int i = 0; i < v1.size(); i++)
		for (int j = 0; j < v2.size(); j++)
			res.push_back(mul(v1[i], v2[j]));
	return res;
}

std::vector<std::pair<LL, LL> > solall(std::vector<std::pair<ULL, int> > decomp) {
	std::vector<std::pair<LL, LL> > res;
	res.push_back(std::pair<LL, LL>(1, 0));
	for (int i = 0; i < decomp.size(); i++) {
		std::vector<std::pair<LL, LL> > tmp;
		if (decomp[i].first == 2) {
			if (!(decomp[i].second & 1)) {
				ULL pow = 1;
				for (int j = 0; j < decomp[i].second/2-1; j++) pow *= decomp[i].first;
				tmp.push_back(std::pair<LL, LL>(2*pow, 0));
				tmp.push_back(std::pair<LL, LL>(pow, pow));
				tmp.push_back(std::pair<LL, LL>(pow, -pow));
			}
		} else if (decomp[i].first % 3 == 2) {
			if (!(decomp[i].second & 1)) {
				ULL pow = 1;
				for (int j = 0; j < decomp[i].second/2; j++) pow *= decomp[i].first;
				tmp.push_back(std::pair<LL, LL>(pow, 0));
			}
		} else if (decomp[i].first == 3) {
			ULL pow = 1;
			for (int j = 0; j < decomp[i].second/2; j++) pow *= 3;
			if (decomp[i].second & 1) tmp.push_back(std::pair<LL, LL>(0, pow));
			else tmp.push_back(std::pair<LL, LL>(pow, 0));
		} else tmp = sol3kp1(decomp[i].first, decomp[i].second);
		if (!tmp.size()) return tmp;
		res = cartesianprod(res, tmp);
	}
	int l = res.size();
	for (int i = 0; i < l; i++)
		res.push_back(std::make_pair(-res[i].first, -res[i].second));
	return res;
}

char s[100000];
void solve() {
	LL a, b;
	ULL x;
	scanf("%lld%lld", &a, &b);
	if (scanf("%[^\n]", s) < 1) s[0] = 0;
	std::stringstream ss(s);
	std::vector<ULL> v;
	while (ss >> x) {
		LL c = 3 * a - b * b;
		while (!(c % x)) v.push_back(x), c /= x;
	}
	if (v.empty()) {
		LL c = 3 * a - b * b;
		if (c < 0) return;
		if (c == 0) {
			if (!(b % 3))
				printf("%lld %lld %lld\n", b/3, b/3, b/3);
			return;
		}
	}
	v.push_back(2);
	std::sort(v.begin(), v.end());
	std::vector<std::pair<ULL, int> > v2;
	for (int i = 0, j = 0; i < v.size(); i = j) {
		for (; j < v.size() && v[i] == v[j]; j++);
		v2.push_back(std::make_pair(v[i], j - i));
	}
	std::vector<std::pair<LL, LL> > res = solall(v2);
	std::vector<std::pair<LL, std::pair<LL, LL> > > ans;
	for (int i = 0; i < res.size(); i++) {
		LL u = (res[i].first+res[i].second)/2, v = (res[i].second-res[i].first)/2;
		if (u >= 0 && v >= 0 && !((b-2*u-v) % 3)) {
			LL x = (b-2*u-v)/3, y = x+u, z = y+v;
			ans.push_back(std::make_pair(x, std::make_pair(y, z)));
		}
	}
	std::sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		printf("%lld %lld %lld\n", ans[i].first, ans[i].second.first, ans[i].second.second);
}

int main() {
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; _++)
		printf("Case #%d:\n", _), solve();
	return 0;
}
