#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#pragma GCC optimize("O3")

using namespace std;

const int MAXN = 252;

int n, m;

struct Node {
	Node *ch[26], *fail, *trans[26]; int end;
}POOL[MAXN], *data = POOL, *root;

Node *d[MAXN];

inline Node* Trans(Node* now, int t) {
	if (now->trans[t]) return now->trans[t];
	Node *tmp = now;
	while (tmp != root && !tmp->ch[t]) tmp = tmp->fail;
	if (tmp->ch[t]) tmp = tmp->ch[t];
	return now->trans[t] = tmp;
}

long long f[27][1 << 10][10 * 10 + 10]; int L;
struct T {int i, s, k, prev; T(int i, int s, int k, int prev):i(i), s(s), k(k), prev(prev){} };
vector<T> g[27][1 << 10][10 * 10 + 10];

vector<string> list;
vector<string> input;

inline void Dp() {
	f[0][0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int s = 0; s < (1 << m); s++) {
			for (int k = 0; k < L; k++) if (f[i][s][k]) {
				long long tmp = f[i][s][k];
				for (int next = 0; next < 26; next++) {
					Node *next_node = Trans(POOL + k, next);
					f[i + 1][s | next_node->end][next_node - POOL] += tmp;
					g[i + 1][s | next_node->end][next_node - POOL].push_back(T(i, s, k, next + 'a'));
				}
			}
		}
	}
}

int del[30];

void clear(void) {
	memset(POOL, 0, sizeof POOL);
	memset(del, 0, sizeof del);
	data = POOL;
	root = data++;
	list.clear();
	input.clear();
	for (int i = 0; i <= n; i++)
		for (int s = 0; s < (1 << m); s++)
			for (int k = 0; k <= 10 * m; k++) g[i][s][k].clear(), f[i][s][k] = 0;
}

inline void Dfs(int i, int s, int k, string st) {
	if (g[i][s][k].empty()) {
		list.push_back(st);
	}
	for (vector<T>::iterator it = g[i][s][k].begin(); it != g[i][s][k].end(); ++it) {
		Dfs(it->i, it->s, it->k, st + (char)it->prev);
	}
}

int main(void) {
	// freopen("password.in", "r", stdin);
	int kase = 0;
	while (scanf("%d%d", &n, &m), n || m) {
		clear(); printf("Case %d: ", ++kase);
		for (int i = 0; i < m; i++) {
			char ch[12]; scanf("%s", ch); 
			input.push_back(string(ch));
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) if (input[i] != input[j] && input[j].find(input[i]) != string::npos) {
				del[i] = 1;
			}
		}
		int M = 0;
		for (int i = 0; i < m; i++) if (!del[i]) {
			int len = input[i].size(); Node *tmp = root;
			for (int j = 0; j < len; j++) {
				int t = input[i][j] - 'a';
				if (!tmp->ch[t]) tmp->ch[t] = data++;
				tmp = tmp->ch[t];
			}
			tmp->end |= 1 << M;
			M++;
		}
		m = M;
		L = data - POOL;
		int head = 1, tail = 1; d[1] = root; root->fail = root;
		while (head <= tail) {
			Node *now = d[head++];
			for (int j = 0; j < 26; j++) if (now->ch[j]) {
				d[++tail] = now->ch[j];
				if (now != root) {
					Node *tmp = now->fail;
					while (tmp != root && !tmp->ch[j]) tmp = tmp->fail;
					if (tmp->ch[j]) tmp = tmp->ch[j];
					now->ch[j]->fail = tmp;
				} else now->ch[j]->fail = root;
			}
		}
		Dp();
		long long Ans = 0;
	   	for (int i = 0; i < L; i++) Ans += f[n][(1 << m) - 1][i];
		printf("%lld suspects\n", Ans);
		if (Ans <= 42) {
			for (int i = 0; i < L; i++) if (f[n][(1 << m) - 1][i]) {
				Dfs(n, (1 << m) - 1, i, string(""));
			}
			for (int i = 0; i < (int)list.size(); i++) reverse(list[i].begin(), list[i].end());
			sort(list.begin(), list.end());
			for (int i = 0; i < (int)list.size(); i++) {
				printf("%s\n", list[i].c_str());
			}
		}
	}
	return 0;
}

