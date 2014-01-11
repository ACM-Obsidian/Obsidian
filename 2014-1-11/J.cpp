#include <cstdio>
#include <cstring>
#include <algorithm>
const int dx[4] = {1, -1, -1, 1}, dy[4] = {1, 1, -1, -1};
struct path {
	long long xmin, xmax, ymin, ymax, dx, dy, dir;
	path() {
		xmin = xmax = ymin = ymax = dx = dy = dir = 0;
	}
};
struct info {
	int loop, len, com[100];
	path p;
} a[100];
int n, u[100], ent;
char tmp[6];
path prep, loopp;
void transform(long long dx, long long dy, int dir, long long &dx2, long long &dy2) {
	switch (dir) {
		case 0: dx2 = dx, dy2 = dy; break;
		case 1: dx2 = dy, dy2 = -dx; break;
		case 2: dx2 = -dx, dy2 = -dy; break;
		case 3: dx2 = -dy, dy2 = dx; break;
	}
}
void pathforward(path &p) {
	p.dx += dx[p.dir], p.dy += dy[p.dir];
	if (p.dx < p.xmin) p.xmin = p.dx;
	if (p.dx > p.xmax) p.xmax = p.dx;
	if (p.dy < p.ymin) p.ymin = p.dy;
	if (p.dy > p.ymax) p.ymax = p.dy;
}
void pathjoin(path &p, path p2) {
	long long dx, dy, dx2, dy2;
	transform(p2.xmin, p2.ymin, (4 - p.dir) & 3, dx, dy);
	transform(p2.xmax, p2.ymax, (4 - p.dir) & 3, dx2, dy2);
	if (dx > dx2) std::swap(dx, dx2);
	if (dy > dy2) std::swap(dy, dy2);
	if (dx + p.dx < p.xmin)
		p.xmin = dx + p.dx;
	if (dy + p.dy < p.ymin)
		p.ymin = dy + p.dy;
	if (dx2 + p.dx > p.xmax)
		p.xmax = dx2 + p.dx;
	if (dy2 + p.dy > p.ymax)
		p.ymax = dy2 + p.dy;
	transform(p2.dx, p2.dy, (4 - p.dir) & 3, dx, dy);
	p.dx += dx, p.dy += dy;
	p.dir = (p.dir + p2.dir) & 3;
}
void dfs(int k) {
	u[k] = 1;
	for (int i = 0; i < a[k].len; i++)
		if (a[k].com[i] == -1)
			pathforward(a[k].p);
		else if (a[k].com[i] == -2)
			a[k].p.dir = (a[k].p.dir + 1) & 3;
		else if (a[k].com[i] == -3)
			a[k].p.dir = (a[k].p.dir + 3) & 3;
		else {
			if (u[a[k].com[i]]) {
				ent = a[k].com[i];
				a[k].loop = 1;
				return;
			} else {
				if (a[a[k].com[i]].loop == -1)
					dfs(a[k].com[i]);
				if (a[a[k].com[i]].loop == 1) {
					a[k].loop = 1;
					return;
				}
				pathjoin(a[k].p, a[a[k].com[i]].p);
			}
		}
	a[k].loop = 0;
	u[k] = 0;
}
void dfs2(int k, int f) {
	if (f) pathjoin(prep, a[k].p);
	else pathjoin(loopp, a[k].p);
	for (int i = 0; i < a[k].len; i++)
		if (a[k].com[i] >= 0 && a[a[k].com[i]].loop) {
			if (a[k].com[i] == ent) {
				if (f) dfs2(a[k].com[i], 0);
			} else
				dfs2(a[k].com[i], f);
			return;
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i].len);
		for (int j = 0; j < a[i].len; j++) {
			scanf("%s", tmp);
			if (strcmp(tmp, "GO") == 0) a[i].com[j] = -1;
			else if (strcmp(tmp, "LEFT") == 0) a[i].com[j] = -2;
			else if (strcmp(tmp, "RIGHT") == 0) a[i].com[j] = -3;
			else sscanf(tmp+1, "%d", &a[i].com[j]), a[i].com[j]--;
		}
		a[i].loop = -1;
	}
	dfs(0);
	if (!a[0].loop)
		prep = a[0].p;
	else {
		dfs2(0, 1);
		if (loopp.dx == 0 && loopp.dy == 0)
			pathjoin(prep, loopp);
		else if (loopp.dir == 0) {
			puts("Infinity");
			return 0;
		} else {
			path tmpp = loopp;
			while (tmpp.dir != 0)
				pathjoin(tmpp, loopp);
			pathjoin(prep, tmpp);
		}
	}
	printf("%lld\n", std::max(std::max(-prep.xmin, prep.xmax), std::max(-prep.ymin, prep.ymax)));
	return 0;
}
