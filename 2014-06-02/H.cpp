#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1000010, M = 4000010;

int to[M], nxt[M], val[M], mr = 0;

struct graph
{
	int vmr;
	vector<int> hd, pere, color, sg;

	graph (void) : vmr(0) {}

	int newNode (void)
	{
		hd.push_back(-1);
		pere.push_back(-1);
		sg.push_back(0);
		return vmr++;
	}
	void link (int a, int b, int v = -1)
	{
		// if (v == -1) printf("LINK %d %d\n", a, b);

		to[mr] = b, nxt[mr] = hd[a], val[mr] = v;
		hd[a] = mr++;
	}
	
	void cal_sg (int x)
	{
		sg[x] = 0;
		for (int p = hd[x]; p != -1; p = nxt[p])
		{
			cal_sg(to[p]);
		}

		// if (hd[0] != -1) printf("SG %d = %d\n", x, sg[x]);

		if (pere[x] != -1) sg[pere[x]] ^= (sg[x] + 1);
	}

	bool win_positive (void)
	{
		return sg[0] != 0;
	}
	bool win_negative (void)
	{
		bool exist2 = false;
		for (int p = hd[0]; !exist2 && p != -1; p = nxt[p])
		{
			if ((sg[to[p]] + 1) >= 2) exist2 = true;
		}
		if (sg[0] == 0 && !exist2) return true;
		else if (sg[0] != 0 && exist2) return true;
		return false;
	}
} t_graph[N], ori_graph;

int now_ptr[N];

void dfs (int x)
{
	for (int p = ori_graph.hd[x]; p != -1; p = nxt[p])
	{
		if (to[p] != ori_graph.pere[x])
		{
			ori_graph.pere[to[p]] = x;
			ori_graph.color[to[p]] = val[p];
			dfs(to[p]);
		}
	}
}
void dfs2 (int x, int cur_level)
{
	for (int p = ori_graph.hd[x]; p != -1; p = nxt[p])
	{
		if (to[p] != ori_graph.pere[x])
		{
			int v = val[p];
			int nd = t_graph[v].newNode();
			t_graph[v].pere[nd] = now_ptr[v];

			// printf("LINK @%d: ", v);

			if (v >= cur_level)
			{
				t_graph[v].link(now_ptr[v], nd);
				now_ptr[v] = nd;
			}

			dfs2(to[p], max(cur_level, v));
		}
	}
	int v = ori_graph.color[x];
	if (v != -1 && v >= cur_level)
	{
		now_ptr[v] = t_graph[v].pere[now_ptr[v]];
	}
}

int main ()
{
	int n; scanf("%d", &n);

	ori_graph.hd.resize(n);
	ori_graph.pere.resize(n);
	ori_graph.color.resize(n);
	for (int i = 0; i < n; i++) ori_graph.hd[i] = -1;

	for (int i = 0; i < n - 1; i++)
	{
		int a, b, v; scanf("%d %d %d", &a, &b, &v); --a, --b, --v;
		ori_graph.link(a, b, v);
		ori_graph.link(b, a, v);
	}
	ori_graph.pere[0] = -1;
	ori_graph.color[0] = -1;
	dfs(0);

	for (int i = 0; i < N; i++) now_ptr[i] = t_graph[i].newNode();
	dfs2(0, 0);

	bool first_win = false;
	for (int i = 0; i < N; i++)
	{
		// if (t_graph[i].hd[0] != -1) printf("CAL %d, LAST = %d\n", i, first_win);

		t_graph[i].cal_sg(0);
		if (!first_win) first_win = t_graph[i].win_positive();
		else first_win = t_graph[i].win_negative();
	}
	if (first_win) printf("Misha\n");
	else printf("Shura\n");

	return 0;
}
