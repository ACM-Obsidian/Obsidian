#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 200020;
int _inf;

struct Edge {
	int y; Edge *next, *opt; int flag;
	Edge(){flag = true;}
}*a[MAXN], POOL[MAXN], *data = POOL;

inline void AddEdge(int x, int y) {
	Edge* tmp = data++;
	tmp->y = y; tmp->next = a[x]; a[x] = tmp;
	tmp = data++;
	tmp->y = x; tmp->next = a[y]; a[y] = tmp;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
}

pair<int, int> _[MAXN];
int n, color[MAXN]; char ch[MAXN];
int d[MAXN], deep[MAXN], father[MAXN];

inline void Bfs(void) {
	int head = 1, tail = 1; d[1] = 1; deep[1] = 0;
	while (head <= tail) {
		int now = d[head++];
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			deep[p->y] = deep[now] + 1;
			father[p->y] = now;
			d[++tail] = p->y;
		}
	}
}

int Ans = 0, X, Y;

int sum[MAXN], stack[MAXN], top;
void getSum(int u, int father) {
	sum[u] = 1; stack[++top] = u;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag && p->y != father) getSum(p->y, u), sum[u] += sum[p->y];
}

pair<int, int> *fim = _ + 100005; int delta[MAXN];

int calstack[MAXN], caltop;
void Cal(int u, int father) {
	calstack[++caltop] = u;
	int other = -delta[u];
	if (1 + deep[u] + fim[other].first > Ans) {
		Ans = 1 + deep[u] + fim[other].first;
		X = u;
		Y = fim[other].second;
	}
	for (Edge *p = a[u]; p; p = p->next) if (p->flag && p->y != father) {
		deep[p->y] = deep[u] + 1;
		delta[p->y] = delta[u] + color[p->y];
		Cal(p->y, u);
	}
}

void Dfs(int u) {
	top = 0; getSum(u, 0);
	if (top == 1) return;
	int now = -1;
	for (int i = 1; i <= top; i++) {
		int ok = 1;
		for (Edge *p = a[stack[i]]; p; p = p->next) if (p->flag) {
			if (sum[p->y] < sum[stack[i]] && sum[p->y] > top / 2) ok = 0;
		}
		if (sum[u] - sum[stack[i]] > top / 2) ok = 0;
		if (ok) { now = stack[i]; break; }
	}
	/*
	printf("@divide %d\n", now);
	for (int i = 1; i <= top; i++) {
		printf("%d ", stack[i]);
	}
	puts("");
	*/
	fim[color[now]] = make_pair(0, now);
	for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
		caltop = 0;
		delta[p->y] = color[p->y]; deep[p->y] = 1;
		Cal(p->y, now);
		for (int i = 1; i <= caltop; i++) {
			int tmp = calstack[i];
			delta[tmp] += color[now];
			fim[delta[tmp]] = max(fim[delta[tmp]], make_pair(deep[tmp], tmp));
		}
	}
	for (int i = 1; i <= top; i++) fim[delta[stack[i]]] = make_pair(_inf, _inf);
	for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
		p->flag = p->opt->flag = 0;
		Dfs(p->y);
	}
}

int Ans1[MAXN], top1, Ans2[MAXN], top2;
int main(void) {
	freopen("shoes.in", "r", stdin);
	// freopen("shoes.out", "w", stdout);
	memset(_, 0x80, sizeof _);
	_inf = _[0].first;
	scanf("%d", &n);
	scanf("%s", ch + 1);
	for (int i = 1; i <= n; i++) color[i] = (ch[i] == 'R') * 2 - 1;
	for (int i = 1; i <  n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		AddEdge(x, y);
	}
	Dfs(1);
	if (Ans > 0) {
		Bfs();
		printf("%d\n", Ans);
		if (deep[X] > deep[Y]) swap(X, Y);
		while (deep[Y] > deep[X]) Ans2[++top2] = Y, Y = father[Y];
		while (X != Y) Ans2[++top2] = Y, Ans1[++top1] = X, Y = father[Y], X = father[X];
		Ans1[++top1] = X;
		for (int i = 1; i <= top1; i++) printf("%d ", Ans1[i]);
		for (int i = top2; i >= 1; i--) printf("%d ", Ans2[i]);
		puts("");
	} else puts("0\n");
	return 0;
}

