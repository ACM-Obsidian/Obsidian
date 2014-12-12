#include <cstdio>
#include <cmath>
#include <unordered_map>
int x[50], y[50], z[50], n, k;
double a, b, c;
inline double solve(double x0, double y0, double z0, double x, double y, double z, double a, double b, double c, double s) {
	if ((x0+x)*(y0+y)*(z0+z) <= s)
		return 0;
	double ans = -1e10;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			double w = (s / ((x0+i*x)*(y0+j*y)) - z0) / z;
			if (w >= 0 && w <= 1+1e-10 && a*i+b*j+c*w > ans) ans = a*i+b*j+c*w;
			w = (s / ((x0+i*x)*(z0+j*z)) - y0) / y;
			if (w >= 0 && w <= 1+1e-10 && a*i+b*w+c*j > ans) ans = a*i+b*w+c*j;
			w = (s / ((y0+i*y)*(z0+j*z)) - x0) / x;
			if (w >= 0 && w <= 1+1e-10 && a*w+b*i+c*j > ans) ans = a*w+b*i+c*j;
		}
	return a+b+c-ans;
}

/*
namespace std {
	template<> size_t hash<std::pair<int, int> >::operator()(std::pair<int, int> x) const {
		return x.first * 5003 + x.second;
	}
};
*/

struct Edge {
	int y; int value; std::pair<int, int> p; Edge *next;
} *POOL = NULL, *data;
const int mod = 1200007;
struct HASH {
	inline int getHash(const std::pair<int, int>& x) {
		return x.first * 5003 + x.second;
	}
	Edge *e[mod]; int vis[mod], stack[mod], top;
	inline void insert(const std::pair<int, int>& key, const int& value) {
		int h = getHash(key), t = h % mod;
		if (POOL == NULL || data == POOL + 65536) {
			POOL = new Edge[65536];
			data = POOL;
		}
		data->y = h, data->value = value, data->p = key, data->next = e[t];
		e[t] = data++;
		if (!vis[t]) {
			vis[t] = 1;
			stack[top++] = t;
		}
	}

	inline Edge* find(const std::pair<int, int>& key) {
		int h = getHash(key), t = h % mod;
		for (Edge *p = e[t]; p; p = p->next) if (p->y == h) {
			return p;
		}
		return NULL;
	}
}f[51];

int main() {
	scanf("%d%d%lf%lf%lf", &n, &k, &a, &b, &c);
	if (k == n) {
		puts("0.0");
		return 0;
	}
	for (int i = 0; i < n; i++) scanf("%d%d%d", &x[i], &y[i], &z[i]);
	f[0].insert(std::pair<int, int>(0, 0), 0);
	for (int i = 1; i < n; i++)
		for (int j = k, r = std::max(0, k-1-(n-i)); j > r; j--)
			for (int index = 0; index < f[j-1].top; index++)
				for (Edge *it = f[j-1].e[f[j-1].stack[index]]; it; it = it->next) {
					int tx = it->p.first, ty = it->p.second, tz = it->value;
					tx += x[i], ty += y[i], tz += z[i];
					auto key = std::make_pair(tx, ty);
					auto it = f[j].find(key);
					if (it == NULL)
						f[j].insert(key, tz);
					else if (tz < it->value)
						it->value = tz;
				}
	double ans = 1e10;
	double s = 1e20;
	for (int index = 0; index < f[k].top; index++) {
		for (auto it = f[k].e[f[k].stack[index]]; it; it = it->next) {
			double tmp = 1.0 * it->p.first * it->p.second * it->value;
			if (tmp < s) s = tmp;
		}
	}
	for (int index = 0; index < f[k - 1].top; index++) {
		for (auto it = f[k-1].e[f[k-1].stack[index]]; it; it = it->next) {
			double x0 = it->p.first, y0 = it->p.second, z0 = it->value;
			double t = solve(x0, y0, z0, x[0], y[0], z[0], a, b, c, s);
			if (t < ans) ans = t;
		}
	}
	printf("%lf\n", ans);
	return 0;
}
