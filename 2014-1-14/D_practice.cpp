#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); ++it)

using namespace std;

const int MAXN = 1010;

struct Node {
	Node *next[26], *fail;
}*root, POOL[MAXN], *data = POOL + 1;

int n; char ch[MAXN]; Node *d[MAXN];

typedef pair<int, int> PII;
PII tmp[MAXN]; PII E[MAXN * 3]; int m;
int dis[MAXN][MAXN], dis_b[MAXN][MAXN]; int Map[MAXN][MAXN], Map_b[MAXN][MAXN];
int vis[MAXN], q[MAXN], inp[MAXN], fim[MAXN][MAXN], link[MAXN];

inline void AddEdge(int x, int y, int z) {
	Map_b[x][y] = Map[x][y] = 1;
	dis_b[x][y] = dis[x][y] = z;
	E[++m] = PII(x, y);
	fim[x][y] = m;
}

int Dfs(int u) {
	vis[u] = true; int ret = 1;
	for (int i = 1; i <= n; i++) if (Map[u][i] && !vis[i]) ret += Dfs(i);
	return ret;
}

int used[MAXN];
map<int, int> edge[MAXN];
int Merge[MAXN];

int Zhuliu(void) {
	memset(vis, 0, sizeof vis);
	if (Dfs(1) != n) return -1;
	int done = 0;
	for (int i = 1; i <= m; i++) edge[i][i] = 1;
	while (true) {
		memset(inp, 0, sizeof inp);
		int Ans = 0;
		for (int i = 2; i <= n; i++) {
			tmp[i] = PII(1000000000, 0);
			for (int j = 1; j <= n; j++) 
				if (Map[j][i] == 1 && (tmp[i].first > dis[j][i] || tmp[i].first == dis[j][i] && fim[j][i] < fim[tmp[i].second][i])) 
					tmp[i] = PII(dis[j][i], j);
			inp[tmp[i].second]++; 
			if (tmp[i].second) {
				Ans += tmp[i].first;
				int t = fim[tmp[i].second][i];
				foreach(it, edge[t]) {
					if (it->second > 0) used[it->first] = 1;
					if (it->second < 0) used[it->first] = 0;
				}
			}
		}
		for (int i = 1; i <= n; i++) vis[i] = i;
		int head = 1, tail = 0;
		for (int i = 1; i <= n; i++) if (!inp[i]) q[++tail] = i;
		while (head <= tail) {
			int now = q[head++];
			if (!--inp[tmp[now].second]) q[++tail] = tmp[now].second;
		}
		bool ok = true;
		for (int i = 1, t; i <= n; i++) if (inp[i] > 0) {
			t = i; ok = false;
			do {
				inp[t] = -i;
				t = tmp[t].second;
				vis[t] = i;
			} while (t != i);
		}
		if (ok) return Ans + done;
		memset(Merge, 0, sizeof Merge);
		for (int i = 1; i <= n; i++) if (inp[i] < 0) {
			done += tmp[i].first;
			int t = fim[tmp[i].second][i];
			for (int j = 1; j <= n; j++) if (vis[j] != vis[i]) {
				if (Map[j][i]) {
					if (Merge[fim[j][i]] == 0) Merge[fim[j][i]] = t;
					if (Map[vis[j]][vis[i]] == 0 || (dis[vis[j]][vis[i]] > dis[j][i] - tmp[i].first || dis[vis[j]][vis[i]] == dis[j][i] - tmp[i].first && fim[vis[j]][vis[i]] > fim[j][i])) {
						Map[vis[j]][vis[i]] = 1;
						dis[vis[j]][vis[i]] = dis[j][i] - tmp[i].first;
						Merge[fim[j][i]] = t;
						fim[vis[j]][vis[i]] = fim[j][i];
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) if (inp[i] < 0) {
			for (int j = 1; j <= n; j++) if (vis[j] != vis[i]) {
				if (Map[i][j]) {
					if (Map[vis[i]][vis[j]] == 0 || (dis[vis[i]][vis[j]] > dis[i][j] || dis[vis[i]][vis[j]] == dis[i][j] && fim[vis[i]][vis[j]] > fim[i][j])) {
						Map[vis[i]][vis[j]] = 1;
						dis[vis[i]][vis[j]] = dis[i][j];
						fim[vis[i]][vis[j]] = fim[i][j];
					}
				}
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (vis[i] != i || vis[j] != j) Map[i][j] = 0;
		for (int i = 1; i <= m; i++) if (Merge[i]) 
			foreach(it, edge[Merge[i]]) {
				edge[i][it->first] -= it->second;
			}
		for (int i = 1; i <= m; i++) edge[Merge[i]].clear();
	}
}

int tag[MAXN], C[MAXN], exists[MAXN], tim;
void Color(int u, int c = -1) {
	if (c != -1) tag[u] = c; else tag[u] = ++tim, exists[u] = 1;
	for (int i = 1; i <= n; i++) if (link[i] == u) {
		if (Map_b[u][i] && dis_b[u][i] == 0) Color(i, tag[u]);
		else Color(i);
	}
}

vector<pair<int, int> > Ans;
int main(void) {
	freopen("dictionary.in", "r", stdin);
	freopen("dictionary.out", "w", stdout);
	scanf("%d", &n); root = data++;
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch);
		Node *tmp = root; int len = strlen(ch);
		for (int j = 0; j < len; j++) {
			if (!tmp->next[ch[j] - 'a']) {
				tmp->next[ch[j] - 'a'] = data++;
				C[tmp->next[ch[j] - 'a'] - POOL] = ch[j];
				AddEdge(tmp - POOL, tmp->next[ch[j] - 'a'] - POOL, 1);
			}
			tmp = tmp->next[ch[j] - 'a'];
		}
	}
	int head = 1, tail = 0;
	for (int i = 0; i < 26; i++) if (root->next[i]) d[++tail] = root->next[i], root->next[i]->fail = root, AddEdge(root->next[i] - POOL, 1, 0);
	while (head <= tail) {
		Node *now = d[head++];
		for (int i = 0; i < 26; i++) if (now->next[i]) {
			Node *tmp = now->fail;
			while (tmp != root && !tmp->next[i]) tmp = tmp->fail;
			if (tmp->next[i]) tmp = tmp->next[i];
			now->next[i]->fail = tmp;
			AddEdge(now->next[i] - POOL, tmp - POOL, 0);
			d[++tail] = now->next[i];
		}
	}
	n = data - POOL - 1;
	int ans = Zhuliu();
	for (int i = 1; i <= m; i++) if (used[i]) link[E[i].second] = E[i].first;
	Color(1);
	printf("%d\n0\n", ans + 1);
	for (int i = 2; i <= n; i++) if (exists[i]) {
		Ans.push_back(make_pair(tag[i], i));
	}
	sort(Ans.begin(), Ans.end());
	for (vector<pair<int, int> >::iterator it = Ans.begin(); it != Ans.end(); ++it)
		printf("%d %c\n", tag[link[it->second]], (char)C[it->second]);
	return 0;
}

