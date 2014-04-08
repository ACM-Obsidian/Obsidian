#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 300;
int kase;

struct rect {
	int type[3];double length[3];
}a[MAXN], b[MAXN];

int n, m, trans[MAXN][MAXN], father[MAXN], width, height;

inline int inside(int x, int y) {
	return a[x].length[0] < a[y].length[0] && a[x].length[2] < a[y].length[2]
		&& b[x].length[0] < b[y].length[0] && b[x].length[2] < b[y].length[2];
}
inline void make_container(void) {
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= n; j++) if (inside(i, j)) {
			int ok = 1;
			for (int k = 1; k <= n; k++) if (inside(i, k) && inside(k, j)) {
				ok = 0;
				break;
			}
			if (ok) {
				trans[i][j] = ok;
				father[j] = i;
			}
		}
}

vector<pair<int, double> > tmp;

inline void Make(double Old, double New) {
	double d = New / Old;
	for (int i = 0; i < (int)tmp.size(); ++i) tmp[i].second *= d;
}

inline void Dfs(int now, rect a[], int replace) {
	int f = father[now];
	double f_len = a[f].length[1], s = a[now].length[0] + a[now].length[1] + a[now].length[2];
	if (f_len == s) return;
	if (a[now].type[0] + a[now].type[1] + a[now].type[2] == 0) a[now].type[replace] = 1;
	tmp.clear();
	double old_s = 0, new_s = f_len;
	for (int i = 0; i < 3; i++) if (a[now].type[i] == 1) {
		tmp.push_back(make_pair(i, a[now].length[i]));
		old_s += a[now].length[i];
	} else new_s -= a[now].length[i];
	Make(old_s, new_s);
	for (int i = 0; i < (int)tmp.size(); i++) a[now].length[tmp[i].first] = tmp[i].second;
	for (int i = 1; i <= n; i++) if (trans[now][i]) Dfs(i, a, replace);
}

double relative[MAXN][3];

inline void get_relative(rect a[]) {
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= n; j++) if (trans[i][j]) {
			relative[j][0] = a[j].length[0] - a[i].length[0];
			relative[j][2] = a[j].length[2] - a[i].length[2];
		}
	for (int i = 1; i <= n; i++) a[i].length[0] = relative[i][0], a[i].length[2] = relative[i][2];
}

inline double get_sum(rect a[], int now) {
	double ret = 0;
	while (now != 0) ret += a[now].length[0], now = father[now];
	return ret;
}

inline void clear(void) {
	memset(trans, 0, sizeof trans);
}

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d%d%d%d", &n, &m, &width, &height), n || m || width || height) {
		++kase;
		clear();
		a[0].length[1] = width;
		b[0].length[1] = height;
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf%lf", &a[i].length[0], &b[i].length[0], &a[i].length[1], &b[i].length[1]);
			a[i].length[2] = width - a[i].length[0] - a[i].length[1];
			b[i].length[2] = height - b[i].length[0] - b[i].length[1];
			scanf("%d%d%d%d%d%d", &a[i].type[1], &b[i].type[1], &b[i].type[0], &b[i].type[2], &a[i].type[0], &a[i].type[2]);
		}
		make_container();
		get_relative(a);
		get_relative(b);
/*		puts("Relative Position:");
		for (int i = 1; i <= n; i++) {
			printf("a: %lf %lf %lf\n", a[i].length[0], a[i].length[1], a[i].length[2]);
			printf("b: %lf %lf %lf\n", b[i].length[0], b[i].length[1], b[i].length[2]);
		}*/
		for (int i = 1; i <= m; i++) {
			scanf("%lf%lf", &a[0].length[1], &b[0].length[1]);
			for (int j = 1; j <= n; j++) if (trans[0][j]) {
				Dfs(j, a, 2);
				Dfs(j, b, 0);
			}
			printf("Case %d, resize operation %d:\n", kase, i);
			for (int j = 1; j <= n; j++) {
				double X = get_sum(a, j);
				double Y = get_sum(b, j);
				printf("    Window %d, x = %.0lf, y = %.0lf, width = %.0lf, height = %.0lf\n", j, X, Y, a[j].length[1], b[j].length[1]);
			}
		}
	}
	return 0;
}

