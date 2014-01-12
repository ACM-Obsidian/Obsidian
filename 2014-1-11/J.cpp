#include <cstdio>
#include <cstring>
#include <algorithm>
const int dx[4] = {1, -1, -1, 1}, dy[4] = {1, 1, -1, -1};
struct bigint {
	int s, h, a[100];
	bigint() {
		s = h = 0;
		memset(a, 0, sizeof a);
	}
	bigint(const bigint &x) {
		s = x.s, h = x.h;
		memcpy(a, x.a, sizeof a);
	}
	bigint(int x) {
		memset(a, 0, sizeof a);
		if (x < 0) s = 1, x = -x;
		else s = 0;
		h = 0;
		while (x) a[h++] = x % 10000, x /= 10000;
		if (h) h--;
	}
	bigint& operator = (const bigint &x) {
		s = x.s, h = x.h;
		memcpy(a, x.a, sizeof a);
		return *this;
	}
	bigint& operator = (int x) {
		memset(a, 0, sizeof a);
		if (x < 0) s = 1, x = -x;
		else s = 0;
		h = 0;
		while (x) a[h++] = x % 10000, x /= 10000;
		if (h) h--;
		return *this;
	}
	bigint& operator += (const bigint &x);
};
void absadd(const bigint &a, const bigint &b, bigint &c) {
	int h = std::max(a.h, b.h)+1;
	for (int i = h+1; i <= c.h; i++) c.a[i] = 0;
	c.h = h;
	for (int i = 0, g = 0; i <= c.h; i++)
		c.a[i] = a.a[i]+b.a[i]+g, c.a[i] >= 10000 ? (c.a[i] -= 10000, g = 1) : g = 0;
	while (c.h && !c.a[c.h]) c.h--;
}
void absminus(const bigint &a, const bigint &b, bigint &c) {
	int h = std::max(a.h, b.h);
	for (int i = h+1; i <= c.h; i++) c.a[i] = 0;
	c.h = h;
	for (int i = 0, g = 0; i <= c.h; i++)
		c.a[i] = a.a[i]-b.a[i]-g, c.a[i] < 0 ? (c.a[i] += 10000, g = 1) : g = 0;
	while (c.h && !c.a[c.h]) c.h--;
}
int absless(const bigint &a, const bigint &b) {
	if (a.h > b.h) return 0;
	else if (a.h < b.h) return 1;
	for (int i = a.h; i >= 0; i--)
		if (a.a[i] > b.a[i]) return 0;
		else if (a.a[i] < b.a[i]) return 1;
	return 0;
}
int operator < (const bigint &a, const bigint &b) {
	if (a.s < b.s) return 0;
	else if (a.s > b.s) return 1;
	if (a.s) return absless(b, a);
	else return absless(a, b);
}
int operator == (const bigint &a, const bigint &b) {
	return a.s == b.s && memcmp(a.a, b.a, sizeof a.a) == 0;
}
bigint& bigint::operator += (const bigint &x) {
	if (s == x.s) absadd(*this, x, *this);
	else if (absless(*this, x)) {
		s = x.s;
		absminus(x, *this, *this);
	} else absminus(*this, x, *this);
	return *this;
}
bigint operator + (const bigint &a, const bigint &b) {
	bigint c;
	if (a.s == b.s) {
		c.s = a.s;
		absadd(a, b, c);
	} else if (absless(a, b)) {
		c.s = b.s;
		absminus(b, a, c);
	} else {
		c.s = a.s;
		absminus(a, b, c);
	}
	return c;
}
bigint operator - (const bigint &a) {
	bigint c(a);
	if (c.h || c.a[c.h]) c.s = !c.s;
	return c;
}
void print(const bigint &a) {
	if (a.s) putchar('-');
	for (int i = a.h; i >= 0; i--) {
		if (i < a.h) {
			if (a.a[i] < 1000) putchar('0');
			if (a.a[i] < 100) putchar('0');
			if (a.a[i] < 10) putchar('0');
		}
		printf("%d", a.a[i]);
	}
	puts("");
}
struct path {
	bigint xmin, xmax, ymin, ymax, dx, dy;
	int dir;
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
void transform(const bigint &dx, const bigint &dy, int dir, bigint &dx2, bigint &dy2) {
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
	if (p.xmax < p.dx) p.xmax = p.dx;
	if (p.dy < p.ymin) p.ymin = p.dy;
	if (p.ymax < p.dy) p.ymax = p.dy;
}
void pathjoin(path &p, path p2) {
	bigint dx, dy, dx2, dy2;
	transform(p2.xmin, p2.ymin, (4 - p.dir) & 3, dx, dy);
	transform(p2.xmax, p2.ymax, (4 - p.dir) & 3, dx2, dy2);
	if (dx2 < dx) std::swap(dx, dx2);
	if (dy2 < dy) std::swap(dy, dy2);
	if (dx + p.dx < p.xmin)
		p.xmin = dx + p.dx;
	if (dy + p.dy < p.ymin)
		p.ymin = dy + p.dy;
	if (p.xmax < dx2 + p.dx)
		p.xmax = dx2 + p.dx;
	if (p.ymax < dy2 + p.dy)
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
	bigint ans = std::max(std::max(-prep.xmin, prep.xmax), std::max(-prep.ymin, prep.ymax));
	print(ans);
	return 0;
}
