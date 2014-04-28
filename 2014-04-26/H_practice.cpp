#include <cstdio>
#include <cstring>
#include <queue>
struct rec {
	int k, a, b;
};
std::queue<rec> q;
const int n = 700;
int hash(rec a) {
	return (((a.k+1) * 10LL * n + (a.a+1)) * 10LL * n + (a.b+1)) % 999983;
}
std::vector<std::pair<rec, long long> > table[999983];
int find(rec a, int h) {
	for (int i = 0; i < table[h].size(); i++)
		if (memcmp(&table[h][i].first, &a, sizeof(rec)) == 0) return i;
	return -1;
}
long long get(int i, int j, int k) {
	rec tmp; tmp.k = i, tmp.a = j, tmp.b = k;
	int h = hash(tmp), p = find(tmp, h);
	if (p == -1) return 0;
	else return table[h][p].second;
}
long long s[n+1];
int main() {
	rec tmp; tmp.k = 0, tmp.a = 0, tmp.b = 1;
	q.push(tmp); table[hash(tmp)].push_back(std::make_pair(tmp, 1LL));
	while (!q.empty()) {
		int i = q.front().k, j = q.front().a, k = q.front().b;
		int h = hash(q.front());
		long long f = table[h][find(q.front(), h)].second;
		if (j == k) s[i] += f;
		q.pop();
		if (i == n) continue;
		for (int l = 1; l <= 9; l++)
			if (k*l <= 1.2*n) {
				tmp.k = i+1, tmp.a = j+l, tmp.b = k*l;
				int tmph = hash(tmp);
				int p = find(tmp, tmph);
				if (p != -1) table[tmph][p].second += f;
				else {
					table[tmph].push_back(std::make_pair(tmp, f));
					q.push(tmp);
				}
			}
	}
	long long k; scanf("%lld", &k);
	long long t = 0;
	int m = 0; while (t + s[m] < k) t += s[m++];
	k -= t;
	int sum = 0, prod = 1;
	for (int i = 0; i < m; i++) {
		t = 0;
		int j = 1;
		for (; j <= 9; j++) {
			long long ts = 0;
			for (int l = 1; prod*j*l <= 1.2*n; l++)
				ts += get(m-i-1, prod*j*l-sum-j, l);
			if (t + ts >= k) break;
			t += ts;
		}
		putchar(j+48);
		sum += j, prod *= j;
		k -= t;
	}
	puts("");
	return 0;
}
