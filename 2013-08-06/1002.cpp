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
	const int MAXN = 100100, N = MAXN;

	struct Node {
		Node *p, *go[26]; int val;
		Node(int _val = 0):p(NULL), val(_val){memset(go, 0, sizeof go);}
	}*root, *last, POOL[MAXN << 1], *data = POOL;

	inline void Add(int x) {
		Node *p = last;
		Node *np = data++; np->val = p->val + 1;
		while (p && !p->go[x]) p->go[x] = np, p = p->p;
		if (p == 0) {
			np->p = root;
		} else {
			Node *q = p->go[x];
			if (q->val == p->val + 1) {
				np->p = q;
			} else {
				Node *nq = data++; nq->val = p->val + 1;
				memcpy(nq->go, q->go, sizeof q->go);
				nq->p = q->p;
				q->p = np->p = nq;
				while (p && p->go[x] == q) p->go[x] = nq, p = p->p;
			}
		}
		last = np;
	}

	//****************************
	char str[N], tmp[N], res[N];

	inline int tr (char a)
	{
		if (a == '$') return 0;
		else return a - 'a' + 1;
	}
	vector<int> vec[27];
	int ptr[N], prev[N];

	void trans ()
	{
		memset(ptr, 0, sizeof ptr);
		memset(prev, 0, sizeof prev);
		memset(tmp, 0, sizeof tmp);
		for (int i = 0; i < 27; i++) vec[i].clear();
		int len = strlen(str);
		for (int i = 0; i < len; i++) tmp[i] = str[i];
		sort(tmp, tmp + len);
		for (int i = 0; i < 27; i++) vec[i].clear(), ptr[i] = 0;
		for (int i = 0; i < len; i++) vec[tr(tmp[i])].push_back(i);
		for (int i = 0; i < len; i++)
		{
			int c = tr(str[i]);
			prev[i] = vec[c][ptr[c]++];
		}
		int f = 0;
		for (int i = 0; i < len; i++) if (str[i] == '$')
		{
			f = i; break;
		}
		for (int i = len - 1; i >= 0; i--)
		{
			res[i] = str[f];
			f = prev[f];
		}
		res[len] = 0;
	}
	//*******************
	
	int n; char ch[MAXN];

	inline void solve(void) {
		while (scanf("%s", str) == 1) {
			memset(POOL, 0, sizeof POOL);
			data = POOL; root = last = data++;
			trans(); 
			int len = strlen(str);
			for (int i = 0; i < len - 1; i++) Add(res[i] - 'a');
			scanf("%d", &n);
			for (int i = 1; i <= n; i++) {
				scanf("%s", ch); int len = strlen(ch);
				Node *tmp = root; bool ok = true;
				for (int i = 0; i < len; i++) {
					if (!tmp->go[ch[i] - 'a']) { ok = false; break; }
					tmp = tmp->go[ch[i] - 'a'];
				}
				puts(ok?"YES":"NO");
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
