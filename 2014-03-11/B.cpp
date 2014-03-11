#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int b, c, r, q;

const double eps = 1e-12;
const int inf = 19931005;
inline int fi (double x)
{
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}

typedef pair<double, double> pdd;
#define X first
#define Y second

pdd bts[60];

double dist (pdd x, pdd y)
{
	return (x.X - y.X) * (x.X - y.X) + (x.Y - y.Y) * (x.Y - y.Y);
}
int which_bts (pdd x)
{
	double mindist = inf;
	int res = -1;

	for (int i = 0; i < b; i++)
	{
		double d = dist(x, bts[i]);
		if (fi(d - mindist) < 0) mindist = d, res = i;
	}

	return res;
}
int change (pdd x, pdd y)
{
	int bx = which_bts(x), by = which_bts(y);
	if (bx == by) return 0;
	else if (fi(dist(x, y)) == 0) return 1;
	pdd mid((x.X + y.X) * 0.5, (x.Y + y.Y) * 0.5);
	return change(x, mid) + change(mid, y);
}

pdd city[60];
int len[60][60];

int main ()
{
	int kase = 0;
	while (scanf("%d %d %d %d", &b, &c, &r, &q), b)
	{
		for (int i = 0; i < b; i++)
			scanf("%lf %lf", &bts[i].X, &bts[i].Y);
		for (int i = 0; i < c; i++)
			scanf("%lf %lf", &city[i].X, &city[i].Y);
		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < c; j++) len[i][j] = inf;
			len[i][i] = 0;
		}
		for (int i = 0; i < r; i++)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			--x, --y;
			len[x][y] = len[y][x] = change(city[x], city[y]);
		}
		for (int k = 0; k < c; k++)
			for (int i = 0; i < c; i++)
				for (int j = 0; j < c; j++)
					len[i][j] = min(len[i][k] + len[k][j], len[i][j]);
		++kase; printf("Case %d:\n", kase);
		for (int i = 0; i < q; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			--x, --y;
			if (len[x][y] == inf) printf("Impossible\n");
			else printf("%d\n", len[x][y]);
		}
	}
	return 0;
}
