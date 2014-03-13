#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const double eps = 1e-12;
inline int fi (double x)
{
	return x > eps ? 1 : (x < -eps ? -1 : 0);
}

int p[3][3], t[3];

typedef pair<double, double> pdd;
#define X first
#define Y second

struct line
{
	int a, b, c;
	line (void) {}
	line (int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
	bool parallel (const line& l)
	{
		return a * l.b == b * l.a;
	}
	bool same (const line& l)
	{
		return parallel(l) && a * l.c == c * l.a;
	}
	pdd intersect (const line& l)
	{
		// it's assumed that *this and l isn't parallel
		return pdd((double)(c * l.b - b * l.c) / (a * l.b - b * l.a),
				   (double)(c * l.a - a * l.c) / (b * l.a - a * l.b));
	}
};

line tt[3];
bool valid[3];
line xa(1, 0, 0), ya(0, 1, 0), ta(1, 1, 1);

int main ()
{
	while (scanf("%d %d %d", &p[0][0], &p[0][1], &p[0][2]), p[0][0] + p[0][1] + p[0][2])
	{
		bool ok = true, single = false;
		for (int i = 1; i < 3; i++)
			for (int j = 0; j < 3; j++) scanf("%d", &p[i][j]);
		for (int i = 0; i < 3; i++)
		{
			scanf("%d", &t[i]), tt[i] = line(p[0][i] - p[2][i], p[1][i] - p[2][i], t[i] - p[2][i]);//, printf("%d %d %d\n", tt[i].a, tt[i].b, tt[i].c);
			if (tt[i].a == 0 && tt[i].b == 0)
			{
				if (tt[i].c) ok = false;
				valid[i] = false;
			}
			else valid[i] = true;
		}
		pdd p;
		for (int i = 0; ok && i < 3; i++) if (valid[i])
		{
			for (int j = i + 1; ok && j < 3; j++) if (valid[j])
			{
				if (tt[i].parallel(tt[j]) && !tt[i].same(tt[j])) ok = false;//, printf("PARALLEL\n");
				else if (!tt[i].parallel(tt[j]))
				{
					pdd pp = tt[i].intersect(tt[j]);
					if (!single) single = true, p = pp;
					else
					{
						if (fi(p.X - pp.X) || fi(p.Y - pp.Y)) ok = false;//, printf("NO THE SAME POINT\n");
					}
				}
			}
		}
		if (ok)
		{
			// printf("OK = %d\n", ok);
			if (single)
			{
				// printf("SINGLE: %lf %lf\n", p.X, p.Y);
				if (fi(p.X) <= 0 || fi(p.Y) <= 0 || fi(p.X + p.Y - 1) >= 0) ok = false;
			}
			else
			{
				for (int i = 0; i < 3; i++) if (valid[i])
				{
					tt[0] = tt[i];
					valid[0] = true;
				}
				if (valid[0])
				{
					ok = false;
					if (!tt[0].parallel(xa))
					{
						p = tt[0].intersect(xa);
						if (fi(p.Y) > 0 && fi(p.Y - 1) < 0) ok = true;
					}
					if (!tt[0].parallel(ya))
					{
						p = tt[0].intersect(ya);
						if (fi(p.X) > 0 && fi(p.X - 1) < 0) ok = true;
					}
					if (!tt[0].parallel(ta))
					{
						p = tt[0].intersect(ta);
						if (fi(p.X) > 0  && fi(p.X - 1) < 0) ok = true;
					}
				}
			}
		}
		printf("%s\n", ok ? "YES" : "NO");
	}
	return 0;
}
