#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <algorithm>

#pragma GCC optimize("O2")

using namespace std;

const int MAXN = 300010;

char ch[MAXN]; int n;

inline int get(int x) {
	if (isupper(x)) return x - 'A'; else return x - 'a' + 26;
}

const int Mod = 1200007;

struct Edge {
	Edge *next; long long y; int cnt;
}*a[Mod], POOL[MAXN << 1], *data = POOL;

inline long long Cal(long long h) {
	int t = h % Mod, ret = 0;
	for (Edge *p = a[t]; p; p = p->next) if (p->y == h) ret += p->cnt;
	return ret;
}

inline void Insert(long long h) {
	int t = h % Mod;
	for (Edge *p = a[t]; p; p = p->next) if (p->y == h) {
		p->cnt++;
		return;
	}
	Edge *tmp = data++; tmp->next = a[t]; tmp->y = h; tmp->cnt = 1; a[t] = tmp;
}

int main(void) {
	freopen("hyperdrome.in", "r", stdin);
	freopen("hyperdrome.out", "w", stdout);
	while (scanf("%d", &n) == 1) {
		memset(POOL, 0, sizeof POOL); data = POOL; memset(a, 0, sizeof a);
		char *p = ch, t;
		while (!isalpha(t = getchar())); *p++ = t;
		for (int i = 1; i < n; i++) *p++ = getchar(); 
		long long S = 0; long long Ans = 0; Insert(0);
		for (int i = 0; i < n; i++) {
			S ^= 1ll << get(ch[i]);
			for (int j = 0; j < 52; j++) Ans += Cal(S ^ (1ll << j));
			Ans += Cal(S);
			Insert(S);
		}
		cout <<Ans<<endl;
	}
	return 0;
}

