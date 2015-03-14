#include <cstdio>
#include <cstring>
#include <cmath>
struct point {
	double x, y;
} a[20], b[20], goal;
bool f[21][21];
int n, q[21], u[21];
bool judge(point x, point y) {
	for (int i = 0; i < n; i++) {
		double dis = sqrt((y.x-x.x)*(y.x-x.x)+(y.y-x.y)*(y.y-x.y));
		double proj = ((b[i].x-x.x)*(y.x-x.x)+(b[i].y-x.y)*(y.y-x.y)) / dis;
		if (proj < 0 || proj > dis)
			continue;
		double dis2 = sqrt((b[i].x-x.x)*(b[i].x-x.x)+(b[i].y-x.y)*(b[i].y-x.y) - proj*proj);
		if (dis2 <= proj / 3)
			return false;
	}
	return true;
}
int main() {
	freopen("score.in", "r", stdin);
	freopen("score.out", "w", stdout);
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &b[i].x, &b[i].y);
		scanf("%lf%lf", &goal.x, &goal.y);
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= n; j++)
				if (i != j)
					f[i][j] = judge(a[i], j == n ? goal : a[j]);
		bool flag = false;
		for (int i = 1; i < n; i++) {
			memset(u, 0, sizeof u);
			int l = 0, r = 1; q[0] = 0;
			while (l < r) {
				int t = q[l++];
				for (int j = 0; j <= n; j++)
					if (i != j && !u[j] && f[t][j])
						q[r++] = j, u[j] = true;
			}
			if (!u[n]) {
				flag = true;
				break;
			}
		}
		puts(flag ? "No goal" : "Goal");
	}
	return 0;
}
