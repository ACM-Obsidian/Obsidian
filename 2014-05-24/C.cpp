#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 4010, M = 40010;

int hd[N], to[M], nxt[M], flow[M], mr;

inline int L (int x)
{
	return x << 1;
}
inline int R (int x)
{
	return (x << 1) | 1;
}
void link (int a, int b)
{
	to[mr] = b, nxt[mr] = hd[a], flow[mr] = 1;
	hd[a] = mr++;
	to[mr] = a, nxt[mr] = hd[b], flow[mr] = 0;
	hd[b] = mr++;
}

int que[N], pere[N], ed[N];
bool bfs (int s, int t)
{
	int l = 0, r = 0;
	memset(pere, -1, sizeof pere);
	pere[s] = -2;
	que[r++] = s;
	while (r > l)
	{
		int c = que[l++];
		// printf("C = %d\n", c);
		for (int p = hd[c]; p != -1; p = nxt[p]) if (flow[p] == 1)
		{
			if (pere[to[p]] == -1)
			{
				pere[to[p]] = c;
				ed[to[p]] = p;
				que[r++] = to[p];
			}
		}
	}
	// printf("END BFS\n");
	if (pere[t] == -1) return false;
	else
	{
		int tt = t;
		while (tt != s)
		{
			--flow[ed[tt]];
			++flow[ed[tt] ^ 1];
			// printf("ELIMINATE %d -> %d\n", pere[tt], tt);
			tt = pere[tt];
		}
		return true;
	}
}

bool sel[N];
int next_pos[N];

vector<vector<int> > ans;

int main ()
{
	int n; scanf("%d", &n);
	mr = 0;
	memset(hd, -1, sizeof hd);
	for (int i = 0; i < n; i++) link(R(i), L(i));
	for (int i = 0; i < n; i++)
	{
		int m; scanf("%d", &m);
		for (int j = 0; j < m; j++)
		{
			int x; scanf("%d", &x); --x;
			link(L(i), R(x));
		}
	}
	// edge(i << 1) : R(i) -> L(i)
	// edge((i << 1) | 1) : Reverse(R(i) -> L(i))
	for (int i = 0; i < n; i++) if (flow[i << 1])
	{
		// printf("BFS %d\n", i);
		if (bfs(L(i), R(i)))
		{
			--flow[i << 1];
			sel[i] = true;
		}
		else sel[i] = false;
	}
	else
	{
		--flow[(i << 1) | 1];
		sel[i] = true;
	}
	// printf("END FLOW\n");
	for (int i = 0; i < n; i++) if (sel[i])
	{
		for (int p = hd[L(i)]; p != -1; p = nxt[p])
		{
			if (to[p] != R(i) && flow[p] == 0)
			{
				next_pos[i] = (to[p] >> 1);
				break;
			}
		}
		// printf("NEXT_POS %d = %d\n", i, next_pos[i]);
	}
	for (int i = 0; i < n; i++) if (sel[i])
	{
		vector<int> round;
		round.push_back(i);
		sel[i] = false;
		for (int k = next_pos[i]; k != i; round.push_back(k), sel[k] = false, k = next_pos[k]);
		ans.push_back(round);
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
	{
		printf("%d", ans[i].size());
		for (int j = 0; j < ans[i].size(); j++)
			printf(" %d", ans[i][j] + 1);
		printf("\n");
	}
	return 0;
}
