#define FILEIO

#define INPUT "in"
#define OUTPUT "ou"

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

	const int inf = 1000000000;

	typedef long long Int64;

	struct Node {
		int l, r; Node *ch[2]; Int64 sum, d;int isModify[2]; int isSame;
		Node(){ch[0] = ch[1] = 0; sum = d = 0; isModify[0] = isModify[1] = 0; isSame = inf;}
		inline void Modify(int dir, int t = 1) {
			Int64 tmp = (long long) t * ((1ll + r - l + 1ll) * (r - l + 1ll) >> 1ll);
			sum += tmp;
			isModify[dir] += t;
		}
		inline void Same(int t) {
			sum = (long long) t * (r - l + 1);
			d = isModify[0] = isModify[1] = 0;
			isSame = t;
		}
		inline void setD(Int64 t) {
			d += t; sum += t * (r - l + 1);
		}
		inline void Push(void) {
			if (ch[0]) {
				if (isSame != inf) {
					ch[0]->Same(isSame);
					ch[1]->Same(isSame);
					isSame = inf;
				}
				REP(i,0,1) if (isModify[i]) {
					ch[i]->Modify(i, isModify[i]);
					ch[!i]->Modify(i, isModify[i]);
					Int64 tmp = (long long)isModify[i] * (long long)(ch[i]->r - ch[i]->l + 1) + d;
					ch[!i]->setD(tmp);
					ch[i]->setD(d);
					isModify[i] = 0; d = 0;
				}
			}
		}
		inline void Update(void) {
			sum = ch[0]->sum + ch[1]->sum;
		}
		void Add(int L, int R, int dir, int d = 0) {
			if (L > R) return;
			if (L <= l && r <= R) {
				Modify(dir); setD(d); return;
			}
			int mid = (l + r) >> 1;
			Push();
			if (R <= mid) ch[0]->Add(L, R, dir, d); else
			if (L > mid) ch[1]->Add(L, R, dir, d); else {
				if (dir == 0) {
					ch[0]->Add(L, mid, dir, d);
					ch[1]->Add(mid + 1, R, dir, d + (mid - L + 1));
				} else {
					ch[0]->Add(L, mid, dir, d + (R - mid));
					ch[1]->Add(mid + 1, R, dir, d);
				}
			}
			Update();
		}
		void setSame(int L, int R, int t) {
			if (L > R) return;
			if (L <= l && r <= R) {Same(t); return;}
			int mid = (l + r) >> 1;
			Push();
			ch[0]->setSame(L, min(mid, R), t);
			ch[1]->setSame(max(mid + 1, L), R, t);
			Update();
		}
		Int64 Cal(int L, int R) {
			if (L > R) return 0;
			if (L <= l && r <= R) return sum;
			int mid = (l + r) >> 1;
			Push();
			return ch[0]->Cal(L, min(mid, R)) + ch[1]->Cal(max(mid + 1, L), R);
		}
	}*root;

	Node *Build(int L, int R) {
		int mid = (L + R) >> 1;
		Node *tmp = new Node(); tmp->l = L, tmp->r = R;
		if (L == R) return tmp;
		tmp->ch[0] = Build(L, mid);
		tmp->ch[1] = Build(mid + 1, R);
		return tmp;
	}

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline void solve(void) {
		char ch[10]; root = Build(1, 250000);
		int T; scanf("%d", &T); while (T--) {
			scanf("%s", ch);
			if (ch[0] == 'A') {
				int l = ScanInt(), r = ScanInt();
				root->Add(l, r, 0);
			}
			if (ch[0] == 'B') {
				int l = ScanInt(), r = ScanInt();
				root->Add(l, r, 1);
			}
			if (ch[0] == 'C') {
				int l = ScanInt(), r = ScanInt(), t = ScanInt();
				root->setSame(l, r, t);
			}
			if (ch[0] == 'S') {
				int l = ScanInt(), r = ScanInt();
				Int64 Ans = root->Cal(l, r);
				printf("%lld\n", Ans);
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
