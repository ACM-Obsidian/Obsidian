#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

inline void rot (double &x, double &y, double al)
{
	double c = cos(al), s = sin(al);
	double tx = x * c - y * s;
	double ty = x * s + y * c;
	x = tx, y = ty;
}

int main ()
{
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase)
	{
		double w, h, xc, yc, x0, y0, al, s;
		scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &w, &h, &xc, &yc, &x0, &y0, &al, &s);
		double deg = al;
		double width = w * s, height = h * s;
		al = al / 180 * 3.14159265358979;

		double rx = x0 - xc, ry = y0 - yc;
		double cen_x = rx + w / 2, cen_y = ry + h / 2;
		double dx = cen_x - x0, dy = cen_y - y0;

		rot(dx, dy, al);
		dx *= s, dy *= s;
		cen_x = x0 + dx, cen_y = y0 + dy;
		double left = cen_x - width / 2, top = cen_y - height / 2;

		printf(".item%d { width: %.1fpx; height: %.1fpx; left: %.1fpx; top: %.1fpx; transform: rotate(%.1fdeg); }\n",
				kase, width, height, left, top, deg);
	}
	return 0;
}
