#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

pair<int, int> a[100];
int n, N; int c, last, tmp, des[100];
map<int, int> M;

inline void Puts(const char *ch) {puts(ch); fflush(stdout);}
inline int round(const double t) {return (int)(t + 0.5);}

int main(void) {
	cin >>n >>c >>last;
	Puts("accept");
	int cnt = 0;
	while (1) {
		cin >>tmp;
		if (tmp > last) Puts("accept"), cnt = 0, last = tmp;
		else {
			Puts("decline"), cnt++;
			if (cnt > 100) break;
		}
	}
	while (1) {
		cin >>tmp;
		if (tmp < last) {
			M[last-tmp]++;
			Puts("accept"), last = tmp;
		} else Puts("decline");
		if (tmp == 0) break;
	}

	for (map<int, int>::iterator it = M.begin(); it != M.end(); ++it) {
		int t = it->second;
		while (t--) a[N].first = it->first, a[N++].second = 0;
	}

	int Ans = -1; int w;
	for (int S = 0; S < (1 << n); S++) {
		int tmp = 0;
		for (int i = 0; i < n; i++)
			if (S & 1<<i) tmp += a[i].first;
		if (tmp >= Ans && tmp <= c) Ans = tmp, w = S;
	}
	for (int i = 0; i < n; i++)
		if (w & 1<<i) des[i] = 1;

	int already = 1;
	for (int i = 0; i < n; i++)
		if (a[i].second != des[i]) already = 0;

	while (1) {
		cin>>tmp;
		int delta = tmp-last;
		int i = 0;
		for (; i < n; i++)
			if ((delta<0 && a[i].second || delta>0 && !a[i].second) && abs(a[i].first) == abs(delta))
				break;
		if (delta>0) {
			while (i < n && !a[i].second && abs(a[i].first) == abs(delta)) i++;
			i--;
		}
		if (a[i].second != des[i] || already) {
			already = 0;
			a[i].second = !a[i].second;
			last = tmp;
			int flag = 1;
			for (int i = 0; i < n; i++)
				if (a[i].second != des[i]) flag = 0;
			if (flag) {
				Puts("stop");
				break;
			} else
				Puts("accept");
		} else {
			Puts("decline");
		}
	}
	
	return 0;
}

