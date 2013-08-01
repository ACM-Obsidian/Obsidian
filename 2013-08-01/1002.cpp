#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int mod = 10007;
const int inv = 417;

int plc[6][5] = {
	{1, 2, 3, 4, 5},
	{0, 4, 5, 2, 3},
	{0, 1, 5, 3, 4},
	{0, 2, 5, 4, 1},
	{0, 3, 5, 1, 2},
	{1, 4, 3, 2, 0}
};

// faces: 0 ~ 53
	// center: 0 ~ 5
	// edge: 6 ~ 29
	// corner: 30 ~ 53
// edges: 54 ~ 65
// corners: 66 ~ 73

const int FES = 6, FCS = 30, ES = 54, CS = 66;

int fEdge[110], fCor[1010];
int edge[110], cor[1010];

int tar[74], star[74], tmr;
int group[110], gmr;

inline int pack1 (int a, int b)
{
	if (a > b) swap(a, b);
	return a * 10 + b;
}
inline int pack2 (int a, int b, int c)
{
	int t[3] = {a, b, c};
	sort(t, t + 3);
	return t[0] * 100 + t[1] * 10 + t[2];
}
void faceAdder (int t, int u, int r, int d, int l, int b)
{
	tar[tmr++] = t;
	
	tar[tmr++] = FES + fEdge[t * 10 + u];
	tar[tmr++] = FES + fEdge[t * 10 + r];
	tar[tmr++] = FES + fEdge[t * 10 + d];
	tar[tmr++] = FES + fEdge[t * 10 + l];
	
	tar[tmr++] = FCS + fCor[t * 100 + u * 10 + r];
	tar[tmr++] = FCS + fCor[t * 100 + r * 10 + d];
	tar[tmr++] = FCS + fCor[t * 100 + d * 10 + l];
	tar[tmr++] = FCS + fCor[t * 100 + l * 10 + u];
}

int nxt[74]; bool sch[74];
void dfs (int x)
{
	if (!sch[nxt[x]])
	{
		sch[nxt[x]] = true;
		dfs(nxt[x]);
	}
}

int main ()
{
	memset(fEdge, -1, sizeof fEdge);
	memset(fCor, -1, sizeof fCor);
	memset(edge, -1, sizeof edge);
	memset(cor, -1, sizeof cor);
	int ptr = 0, ptr2 = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int r = i * 10 + plc[i][j];
			fEdge[r] = ptr++;	
			int r2 = pack1(i, plc[i][j]);
			if (edge[r2] == -1) edge[r2] = ptr2++;
		}
	}
	ptr = 0, ptr2 = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int k = (j + 1) % 4;
			int r = i * 100 + plc[i][j] * 10 + plc[i][k];
			fCor[r] = ptr++;
			int r2 = pack2(i, plc[i][j], plc[i][k]);
			if (cor[r2] == -1) cor[r2] = ptr2++;
		}
	}
	gmr = 0;
	for (int top = 0; top < 6; top++)
	{
		for (int front = 0; front < 4; front++)
		{
			tmr = 0;
			faceAdder(top,
				plc[top][front],
				plc[top][(front + 1) % 4],
				plc[top][(front + 2) % 4],
				plc[top][(front + 3) % 4],
				plc[top][4]);
			for (int i = 0; i < 4; i++)
			{
				faceAdder(plc[top][(front + i) % 4],
					top,
					plc[top][(front + i + 3) % 4],
					plc[top][4],
					plc[top][(front + i + 1) % 4],
					plc[top][(front + i + 2) % 4]);
			}
			faceAdder(plc[top][4],
				plc[top][front],
				plc[top][(front + 3) % 4],
				plc[top][(front + 2) % 4],
				plc[top][(front + 1) % 4],
				top);
			for (int i = 0; i < 4; i++)
				tar[tmr++] = ES + edge[pack1(top, plc[top][(front + i) % 4])];
			for (int i = 0; i < 4; i++)
				tar[tmr++] = ES + edge[pack1(plc[top][4], plc[top][(front + i) % 4])];
			for (int i = 0; i < 4; i++)
				tar[tmr++] = ES + edge[pack1(plc[top][(front + i) % 4], plc[top][(front + i + 1) % 4])];
			for (int i = 0; i < 4; i++)
				tar[tmr++] = CS + cor[pack2(top, plc[top][(front + i) % 4], plc[top][(front + i + 1) % 4])];
			for (int i = 0; i < 4; i++)
				tar[tmr++] = CS + cor[pack2(plc[top][4], plc[top][(front + i) % 4], plc[top][(front + i + 3) % 4])];
			
			if (gmr == 0)
			{
				for (int i = 0; i < 74; i++) star[i] = tar[i];
			}
			for (int i = 0; i < 74; i++)
				nxt[star[i]] = tar[i];
			int g = 0;
			memset(sch, 0, sizeof sch);
			for (int i = 0; i < 74; i++) if (!sch[i])
			{
				++g; sch[i] = true;
				dfs(i);
			}
			group[gmr++] = g;
		}
	}
	
	int kase; scanf("%d", &kase);
	for (int tkase = 1; tkase <= kase; ++tkase)
	{
		int n; scanf("%d", &n);
		int ans = 0;
		for (int i = 0; i < gmr; i++)
		{
			int tt = 1;
			for (int j = 0; j < group[i]; j++) tt = (tt * n) % mod;
			ans += tt;
		}
		printf("Case %d: %d\n", tkase, ans * inv % mod);
	}
	return 0;
}
