#include <cstdio>
#include <cmath>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
int inv[50000000], p, g, g2;
std::tr1::unordered_map<int, int> hash;
int power(int n, int k, int r) {
	int t = n, s = 1;
	for (; k; k >>= 1, t = 1LL*t*t%r)
		if (k & 1) s = 1LL*s*t%r;
	return s;
}
int ind2(int a) {
	int s = 1;
	std::tr1::unordered_map<int, int>::iterator it;
	for (int i = 0; i < (p+999999)/1000000; i++, s = 1LL*s*g2%p) {
		int t;
		if (s > p/2) t = 1LL*inv[p%s]*(p-p/s)%p;
		else t = inv[s];
		t = 1LL*a*t%p;
		if ((it = hash.find(t)) != hash.end())
			return i * 1000000 + it->second;
	}
	return -1;
}
void ext_gcd(int a, int b, int &x, int &y) {
	if (!b) x = 1, y = 0;
	else if (!a) x = 1, y = -1;
	else if (a > b) ext_gcd(a % b, b, x, y), y += a / b * x;
	else ext_gcd(a, b % a, x, y), x += b / a * y;
}
int ind(int a, int b) {
	int x = ind2(a), y = ind2(b), z = p-1;
	if (y % std::__gcd(x, p-1)) return -1;
	int t = std::__gcd(x, p-1), u;
	x /= t, y /= t, z /= t;
	ext_gcd(x, z, t, u);
	t = 1LL*t*y%z;
	return t;
}
int main() {
	freopen("alot.in", "r", stdin);
	freopen("alot.out", "w", stdout);
	int q; scanf("%d%d", &p, &q);
	inv[0] = -1, inv[1] = 1;
	for (int i = 2; i <= p/2; i++)
		inv[i] = 1LL*inv[p%i]*(p-p/i)%p;
	int phi = p-1;
	std::vector<int> pr;
	for (int i = 2; i*i <= phi; i++)
		if (!(phi%i)) {
			pr.push_back(i);
			while (!(phi%i)) phi /= i;
		}
	g = 1;
	for (; ; g++) {
		int flag = 1;
		for (int i = 0; i < pr.size(); i++)
			if (power(g, (p-1)/pr[i], p) == 1) {
				flag = 0;
				break;
			}
		if (flag) break;
	}
	g2 = 1;
	for (int i = 0; i < 1000000 && (!i || g2 != 1); i++, g2 = 1LL*g2*g%p)
		hash.insert(std::make_pair(g2, i));
	while (q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x && !y) puts("-1");
		else if (x) printf("%d\n", ind(x, y));
		else printf("%d\n", y == 1 ? 0 : (y == 0 ? 1 : -1));
	}
	return 0;
}
