#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

struct point3
{
	double x, y, z;
	point3 (void) {}
	point3 (double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
};

double dot (point3 a, point3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
double len (point3 a)
{
	return sqrt(dot(a, a));
}
double angle (point3 a, point3 b)
{
	return acos(dot(a, b) / (len(a) * len(b)));
}

point3 star[510], tele[510];
double ang[510];

int main ()
{
	freopen("A.txt", "r", stdin);
	int n; while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; i++)
		{
			double x, y, z;
			scanf("%lf %lf %lf", &x, &y, &z);
			star[i] = point3(x, y, z);
		}
		int m; scanf("%d", &m);
		for (int i = 0; i < m; i++)
		{
			double x, y, z;
			scanf("%lf %lf %lf %lf", &x, &y, &z, &ang[i]);
			tele[i] = point3(x, y, z);
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			bool ok = false;
			for (int j = 0; !ok && j < m; j++)
			{
				if (angle(star[i], tele[j]) - ang[j] < 1e-10)
					ok = true;
			}
			if (ok) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
