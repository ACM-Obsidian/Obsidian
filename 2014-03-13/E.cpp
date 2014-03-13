#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> tmp;

const int MAXN = 100010, base = 13331;

int a[MAXN], n, ret[MAXN], next[MAXN], prev[MAXN], marknum; char ch[MAXN];
long long sum[MAXN], sum_rev[MAXN], pow[MAXN];long double pow26[MAXN];

inline long long getHash(int l, int r) {
	return sum[r] - sum[l - 1] * pow[r - l + 1];
}
inline long long getHashrev(int l, int r) {
	return sum_rev[l] - sum_rev[r + 1] * pow[r - l + 1];
}

int main(void) {
	freopen("palindromes.in", "r", stdin);
	freopen("palindromes.out", "w", stdout);
	scanf("%s", ch); n = strlen(ch);
	pow26[0] = pow[0] = 1; for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * base, pow26[i] = pow26[i - 1] * 26;
	for (int i = 1; i <= n; i++) {
		if (ch[i - 1] != '?') a[i] = ch[i - 1] - 'a' + 1; else a[i] = 27, marknum++;
		sum[i] = sum[i - 1] * base + a[i];
	}
	for (int i = n; i >= 1; i--) sum_rev[i] = sum_rev[i + 1] * base + a[i];
	for (int i = 1; i <= n; i++) if (a[i] == 27) prev[i] = i; else prev[i] = prev[i - 1];
	for (int i = n; i >= 1; i--) if (a[i] == 27) next[i] = i; else next[i] = next[i + 1];
	long double Ans = 0;
	for (int i = 1; i <= n; i++) {
		tmp.clear();
		for (int j = next[i + 1], k = 1; 2 * i - j >= 1 && j && k <= 20; j = next[j + 1], k++) {
			tmp.push_back(j - i);
		}
		for (int j = prev[i - 1], k = 1; 2 * i - j <= n && j && k <= 20; j = prev[j - 1], k++) {
			tmp.push_back(i - j);
		}
		sort(tmp.begin(), tmp.end());
		tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
		int last = 0, t = 0;
		for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
			long long L = getHash(i - *it + 1, i - last - 1);
			long long R = getHashrev(i + last + 1, i + *it - 1);
			if (L != R && abs(*it - last) > 1) break;
			t++;
			Ans += (25.0 / pow26[t]) * (2 * (*it) - 1);
			last = *it;
		}
		int pos = t ? tmp[t - 1] + 1 : 1;
		int l = pos, r = min(n - i, i - 1);
		while (l <= r) {
			int mid = (l + r) >> 1;
			long long L = getHash(i - mid, i - pos); 
			long long R = getHashrev(i + pos, i + mid);
			if (L == R) l = mid + 1; else r = mid - 1;
		}
		Ans += (1.0 / pow26[t]) * (2 * r + 1);
	}
	printf("%lf\n", (double)Ans / n);
	return 0;
}

