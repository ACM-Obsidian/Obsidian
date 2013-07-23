#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define cl(a) memset(a,0,sizeof a);
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	const int MAXN = 50010;

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	int n, inp[MAXN], d[MAXN], father[MAXN], isC[MAXN], belong[MAXN], sum[MAXN], deep[MAXN];

	void Dfs(int u, int c) {
		belong[u] = c;
		for (Edge *p = a[u]; p; p = p->next) if (!isC[p->y]) {
			deep[p->y] = deep[u] + 1;
			Dfs(p->y, c);
		}
	}

	inline void solve(void) {
		int kase; scanf("%d", &kase); rep(_,kase) {
			cl(inp); cl(father); cl(isC); cl(belong); cl(sum); cl(deep); cl(a);
			scanf("%d", &n);
			for (int j = 1; j <= n; j++) {
				int i, t; scanf("%d%d", &i,&t);
				a[t] = new Edge(i, a[t]);
				inp[t]++; father[i] = t;
			}
			int head = 1, tail = 0;
			rep(i,n) if (inp[i] == 0) d[++tail] = i;
			while (head <= tail) {
				int now = d[head++];
				if (!--inp[father[now]]) d[++tail] = father[now];
			}
			int circle = 0;
			rep(i,n) if (inp[i]) {
				circle++;
				int t = i; do {
					isC[t] = circle, inp[t] = 0, t = father[t], sum[circle]++;
				}while (t != i);
			}
			rep(i,n) if (isC[i]) Dfs(i,isC[i]);
			pair<int, int> Ans = mp(0,0);
			rep(i,n) Ans = max(Ans, mp(deep[i] + sum[belong[i]], -i));
			printf("Case %d: %d\n", _, -Ans.second);
		}
	}
}

int main(void) {
	#ifdef FILEIO
//		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
