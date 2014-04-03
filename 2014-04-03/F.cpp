#include <cstdio>
#include <vector>
#include <algorithm>
struct edge {
	int n;
	edge *next;
} *g1[500], *g2[500], stack[10000];
struct edge2 {
	int x, y;
	edge2 *next;
} *g3[500][500], stack2[20000000];
int f[500][500], d[500][500], l[250000], pre[250000], n1, n2, m1, m2, top, top2, top3;
char l1[501], l2[501];
std::pair<int, int> t[250000], a[250000];
void solve() {
	top = 0;
	for (int i = 0; i < n1; i++) g1[i] = NULL;
	while (m1--) {
		int x, y; scanf("%d%d", &x, &y), x--, y--;
		edge *i = &stack[top++]; i->n = y, i->next = g1[x]; g1[x] = i;
	}
	scanf("%d%d%s", &n2, &m2, l2);
	for (int i = 0; i < n2; i++) g2[i] = NULL;
	while (m2--) {
		int x, y; scanf("%d%d", &x, &y), x--, y--;
		edge *i = &stack[top++]; i->n = y, i->next = g2[x]; g2[x] = i;
	}
	top2 = 0;
	int N = 0;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++) if (l1[i] == l2[j])
			d[i][j] = 0, N++;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++) if (l1[i] == l2[j]) {
			g3[i][j] = NULL;
			for (edge *k = g1[i]; k != NULL; k = k->next)
				for (edge *l = g2[j]; l != NULL; l = l->next)
					if (l1[k->n] == l2[l->n]) {
						edge2 *p = &stack2[top2++]; p->x = k->n, p->y = l->n;
						p->next = g3[i][j]; g3[i][j] = p;
						d[k->n][l->n]++;
					}
		}
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			if (l1[i] == l2[j] && d[i][j] == 0) t[top3++] = std::make_pair(i, j);
	int cnt = 0;
	while (top3) {
		int i = t[top3-1].first, j = t[top3-1].second; top3--;
		a[cnt] = t[top3]; f[i][j] = cnt++;
		for (edge2 *k = g3[i][j]; k != NULL; k = k->next)
			if ((--d[k->x][k->y]) == 0)
				t[top3++] = std::make_pair(k->x, k->y);
	}
	if (cnt < N) {
		puts("-1");
		return;
	}
	for (int i = 0; i < N; i++) l[i] = 1, pre[i] = -1;
	int ans = 0, ansi = -1;
	for (int i = 0; i < N; i++) {
		if (l[i] > ans) ans = l[i], ansi = i;
		for (edge2 *j = g3[a[i].first][a[i].second]; j != NULL; j = j->next)
			if (l[f[j->x][j->y]] < l[i]+1)
				l[f[j->x][j->y]] = l[i]+1, pre[f[j->x][j->y]] = i;
	}
	printf("%d\n", ans);
	if (ans == 0) {
		printf("\n\n");
		return;
	}
	std::vector<int> ansl1, ansl2;
	while (ansi != -1)
		ansl1.push_back(a[ansi].first), ansl2.push_back(a[ansi].second), ansi = pre[ansi];
	for (int i = ans-1; i >= 0; i--) printf("%d%c", ansl1[i]+1, " \n"[i == 0]);
	for (int i = ans-1; i >= 0; i--) printf("%d%c", ansl2[i]+1, " \n"[i == 0]);
}
int main() {
	int _ = 0;
	while (scanf("%d%d%s", &n1, &m1, l1) == 3)
		printf("Case %d: ", ++_), solve();
	return 0;
}
