//#define Debug 
#include <cstring> 
#include <cstdio> 
#include <algorithm> 
#include <cctype> 
using namespace std;

const int MAXN = 40020; 

inline int ScanInt(void) { 
	int r = 0, c; 
	while (c = getchar(), !isdigit(c)) {} 
	r = c - '0'; 
	while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0'; 
	return r; 
} 

struct Edge { 
	int y; bool flag; Edge *next, *opt; 
}*a[MAXN], POOL[400010], *data = POOL;

struct pair { 
	int x, y; 
}E[400010]; 

inline int get(int x) {
	if (isdigit(x)) return x - '0'; else return x - 'A' + 10;
}

inline void AddEdge(int x, int y, bool t = true) {
	Edge *tmp = a[x];
	a[x] = data++; a[x]->y = y; a[x]->next = tmp; a[x]->flag = true;
	tmp = a[y];
	a[y] = data++; a[y]->y = x; a[y]->next = tmp; a[y]->flag = t;
	a[x]->opt = a[y];
	a[y]->opt = a[x];
}

int n, m; 
char ch[10];

inline void Input(void) { 
	for (int i = 1; i <= m; i++) { 
		scanf("%s", ch);
		int x = get(ch[0]) * 32 * 32 + get(ch[1]) * 32 + get(ch[2]);
		int y = get(ch[3]) * 32 * 32 + get(ch[4]) * 32 + get(ch[5]);
		x++, y = n + y + 1;
		//printf("%d %d\n", x, y);
		AddEdge(x, y);
		E[i].x = x, E[i].y = y;
	}
}

bool match[MAXN];  
int levelx[MAXN], levely[MAXN], link[MAXN]; 
int d[MAXN]; 

inline bool Bfs(void) { 
	int head = 1, tail = 0; 
	memset(levely, 0, sizeof levely); 
	for (int i = 1; i <= n; i++) { 
		if (!match[i]) d[++tail] = i; 
		levelx[i] = 0; 
	} 
	bool ret = false; 
	while (head <= tail) { 
		int now = d[head++]; 
		for (Edge *p = a[now]; p; p = p->next) if (levely[p->y] == 0) { 
			levely[p->y] = levelx[now] + 1; 
			if (link[p->y] == 0) ret = true; 
			else levelx[link[p->y]] = levely[p->y] + 1, d[++tail] = link[p->y]; 
		} 
	} 
	return ret; 
} 

bool Find(int u) { 
	for (Edge *p = a[u]; p; p = p->next) if (levely[p->y] == levelx[u] + 1) { 
		levely[p->y] = 0; 
		if (link[p->y] == 0 || Find(link[p->y])) { 
			match[u] = true; link[p->y] = u; 
			return true; 
		} 
	} 
	return false; 
} 

inline void Match(void) { 
	while (Bfs()) 
		for (int i = 1; i <= n; i++) 
			if (!match[i]) Find(i); 
} 

inline void Adjust(void) { 
	for (int i = 1; i <= n; i++) 
		for (Edge *p = a[i]; p; p = p->next) 
			if (link[p->y] == i) 
				p->opt->flag = false; 
			else 
				p->flag = false; 
} 

int cnt = 0, tim[MAXN], belong[MAXN], low[MAXN], sum = 0, stack[MAXN], top; 
bool in_stack[MAXN]; 

void Dfs(int u) { 
	tim[u] = low[u] = ++cnt; 
	in_stack[stack[++top] = u] = true; 
	for (Edge *p = a[u]; p; p = p->next) if (p->flag) { 
		if (tim[p->y] == 0) { 
			Dfs(p->y); 
			low[u] = std::min(low[u], low[p->y]); 
		}else if (in_stack[p->y])  
			low[u] = std::min(low[u], tim[p->y]); 
	} 
	if (low[u] == tim[u]) { 
		sum++; int j; 
		do { 
			j = stack[top--]; 
			in_stack[j] = false; 
			belong[j] = sum; 
		}while (j != u); 
	} 
} 

int Ans[MAXN], T;

inline void clear(void) {
	data = POOL;
	memset(a, 0, sizeof a);
	cnt = 0; top = 0; T = 0;
	memset(in_stack, 0, sizeof in_stack);
	memset(tim, 0, sizeof tim);
	memset(belong, 0, sizeof belong);
	memset(low, 0, sizeof low);
	sum = 0;
	memset(stack, 0, sizeof stack);
	memset(levelx, 0, sizeof levelx);
	memset(levely, 0, sizeof levely);
	memset(link, 0, sizeof link);
	memset(match, 0, sizeof match);
	memset(d, 0, sizeof d);
}

void solve(void) { 
	int nY;
	while (scanf("%d%d%d", &n, &nY, &m) == 3) {
		clear();
		n = max(n, nY);
		Input(); 
		Match(); 
		Adjust(); 
		for (int i = 1; i <= n; i++) if (match[i]) {
			AddEdge(n * 2 + 1, i, false);
		} else AddEdge(i, n * 2 + 1, false);
		for (int i = n + 1; i <= n * 2; i++) if (link[i]) {
			AddEdge(i, n * 2 + 2, false);
		} else AddEdge(n * 2 + 2, i, false);
		for (int i = 1; i <= n * 2 + 2; i++) 
			if (!tim[i]) 
				Dfs(i); 
		for (int i = 1; i <= m; i++) { 
			int x = E[i].x, y = E[i].y; 
			if (belong[x] == belong[y]) ; //putchar('0');
			else if (match[x] && 0 != link[y] && link[y] != x) Ans[++T] = i - 1;
			//putchar('2'- (x == link[y]));
		}
		printf("%d\n", T);
		for (int i = 1; i < T; i++) printf("%d ", Ans[i]); if (T) printf("%d", Ans[T]); puts("");
	}
} 

int main(int argc, char** argv) { 
	//freopen("in", "r", stdin); 
	solve(); 
	return 0; 
}
