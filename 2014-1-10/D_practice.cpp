#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

const int M = 5010;
const int S = 10, N = (1 << S);
const int MASK = (1 << S) - 1;

struct NFA
{
	int hd[N], to[M], nxt[M];
	char ch[N];
	int v, e, fin;
	
	NFA (void) : v(0), e(0) {}
	
	inline int addv (void)
	{
		hd[v] = -1;
		return v++;
	}
	inline void link (int a, int b, char c) // c == 0: epsilon
	{
		to[e] = b, ch[e] = c, nxt[e] = hd[a];
		hd[a] = e++;
	}
	int _parse (char *regex, int le, int ri, int init, bool no_alt) // [le, ri)
	{
		if (le >= ri) // Empty expression
		{
			int res = addv();
			link(init, res, 0); 
			return res;
		}
		else if (ri - le == 1)
		{
			int res = addv();
			link(init, res, regex[le]);
			return res;
		}
		if (!no_alt) // Alternation
		{
			int st = 0;
			for (int i = le; i < ri; i++)
			{
				if (regex[i] == '(') ++st;
				else if (regex[i] == ')') --st;
				if (st == 0 && regex[i] == '|')
				{
					int s = addv(), t = addv(), z = addv();
					int ss = _parse(regex, le, i, s, true);
					int tt = _parse(regex, i + 1, ri, t, false);
					link(init, s, 0);
					link(init, t, 0);
					link(ss, z, 0);
					link(tt, z, 0);
					return z;
				}
			}
		}
		// Concatenation
		int st = 0, u = -1;
		for (int i = le; i < ri; i++)
		{
			if (regex[i] == '(') ++st;
			else if (regex[i] == ')') --st;
			if (st == 0)
			{
				u = i + 1;
				break;
			} 
		}
		assert(u != -1);
		int mid;
		if (regex[u] == '*') // Kleene star
		{	
			int x = addv(), y;
			if (regex[le] == '(')
			{
				// (...)*....
				// l    u    r
				y = _parse(regex, le + 1, u - 1, x, false);
			}
			else
			{
				// .*....
				// lu    r
				y = _parse(regex, le, u, x, false);
			}
			mid = addv();
			link(init, x, 0);
			link(y, mid, 0);
			link(y, x, 0);
			link(init, mid, 0);
			while (u < ri && regex[u] == '*') ++u;
			// (...)*....
			// l     u   r
		}
		else
		{
			if (regex[le] == '(')
			{
				// (...)....
				// l    u   r
				mid = _parse(regex, le + 1, u - 1, init, false);
			}
			else
			{
				// .......
				// lu     r
				mid = _parse(regex, le, u, init, false);
			}
		}
		return _parse(regex, u, ri, mid, false);
	}
	void parse (char *regex)
	{
		v = e = 0; addv();
		fin = _parse(regex, 0, strlen(regex), 0, false);
	}
	
	NFA (char *regex)
	{
		parse(regex);
	}
	
	/* void dot_show (void) const
	{
		printf("digraph NFA {\n");
		printf("0 [shape=box];\n");
		printf("%d [shape=doublecircle];\n", v - 1);
		for (int i = 0; i < v; i++)
		{
			for (int p = hd[i]; p != -1; p = nxt[p])
			{
				printf("%d->%d [label=%c];\n", i, to[p], ch[p] ? ch[p] : '0');
			}
		}
		printf("}\n");
	} */
};

inline int prd (int a, int b, int em)
{
	return (a << S) | b | ((em << S) << S);
}
inline int lsb (int x)
{
	return x & MASK;
}
inline int msb (int x)
{
	return (x >> S) & MASK;
}
inline int em (int x)
{
	return (x >> S) >> S;
}

const int QMAX = (1 << (S << 1)) << 1;
const int QMASK = QMAX - 1;

inline int qmask (int x)
{
	return (x + QMAX) & QMASK;
}

bool sch[QMAX];
char tran[QMAX];
int que[QMAX], pere[QMAX], fin;
bool intersect (const NFA& a, const NFA& b)
{
	memset(sch, 0, sizeof sch);
	int l = 0, r = 0; fin = prd(a.fin, b.fin, 1);
		
	sch[0] = true, que[qmask(r++)] = 0;
	while (r > l && !sch[fin])
	{
		int c = que[qmask(l++)], x;
		int sa = msb(c), sb = lsb(c);
		for (int p = a.hd[sa]; p != -1; p = a.nxt[p])
		{
			if (!a.ch[p]) // epsilon
			{
				x = prd(a.to[p], sb, em(c));
				if (!sch[x]) sch[x] = true, tran[x] = 0, pere[x] = c, que[qmask(--l)] = x;
			}
			for (int pp = b.hd[sb]; pp != -1; pp = b.nxt[pp]) if (a.ch[p] == b.ch[pp])
			{
				x = prd(a.to[p], b.to[pp], a.ch[p] ? 1 : em(c));
				if (!sch[x])
				{
					sch[x] = true, tran[x] = a.ch[p], pere[x] = c;
					if (a.ch[p]) que[qmask(r++)] = x;
					else que[qmask(l--)] = x;
				}
			}
		}
		for (int pp = b.hd[sb]; pp != -1; pp = b.nxt[pp])
		{
			if (!b.ch[pp]) // epsilon
			{
				x = prd(sa, b.to[pp], em(c));
				if (!sch[x]) sch[x] = true, tran[x] = 0, pere[x] = c, que[qmask(--l)] = x;
			}
		}
	}
	return sch[fin];
}

char s1[N], s2[N];
char res[QMAX];

int main ()
{
	freopen("disjoint.in", "r", stdin);
	freopen("disjoint.out", "w", stdout);
	
	scanf("%s %s", s1, s2);
	if (!intersect(s1, s2)) printf("Correct\n");
	else
	{
		printf("Wrong\n");
		int mr = 0;
		for (int t = fin; t; t = pere[t])
			if (tran[t]) res[mr++] = tran[t];
		for (int i = mr - 1; i >= 0; i--) printf("%c", res[i]); printf("\n");
	}
	return 0;
}
