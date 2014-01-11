#include <cstdio>
#include <set>

using namespace std;

const int MAXN = 200010;

int person[MAXN], n, m, k; char ch[10];
int f[MAXN], color[MAXN];

inline int get(int x) {return x == f[x] ? x: f[x] = get(f[x]);}

inline void Merge(int x, int y) {
	x = get(x); y = get(y); 
	if (x != y) f[x] = y;
}

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i < MAXN; i++) f[i] = i;
	for (int i = 1; i <= n; i++) scanf("%s", ch), person[i] = ch[0] == 'F';
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d", &x);
		if (x < 0) person[-x] = -1; else {
			scanf("%d %s", &y, ch);
			person[++n] = ch[0] == 'F'; 
			if (person[x] == 1) Merge(x, n); else Merge(y, n);
		}
	}
	int alive = 0;
	for (int i = 1; i <= n; i++) {
		if (person[i] != -1) alive ++;
		get(i);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		int x, t; scanf("%d%d", &x, &t);
		color[get(x)] = t;
	}
	int no = 0, T = -1, S = -1;
	for (int i = 1; i <= n; i++) {
		if (person[i] != -1 && color[get(i)]) {
			if (S == -1) S = color[get(i)]; else
			if (S != color[get(i)]) S = -2;
		}
		if (person[i] != -1 && color[get(i)] == 0) no = 1;
		if (person[i] != -1) {
			if (T == -1) T = get(i); else if (T != get(i)) T = -2;
		}
	}
	if (T > 0 || S > 0 && no == 0) puts("YES"); else
	if (S == -2) puts("NO"); else puts("POSSIBLY");
	return 0;
}

