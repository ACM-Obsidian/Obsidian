#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

struct triple
{
	int x, y, z;
	triple (void) {}
	triple (int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	bool operator== (const triple& a) const
	{
		return x == a.x && y == a.y && z == a.z;
	}
};
triple operator+ (triple a, triple b)
{
	return triple(a.x + b.x, a.y + b.y, a.z + b.z);
}
triple operator- (triple a, triple b)
{
	return triple(a.x - b.x, a.y - b.y, a.z - b.z);
}

triple d[6] = {triple(1, 0, 0), triple(-1, 0, 0), triple(0, 1, 0), triple(0, -1, 0), triple(0, 0, 1), triple(0, 0, -1)};

triple goal;
int g_dir;
bool occupied[21][21][21];
int xmax, ymax, zmax;

bool in (triple a)
{
	return a.x >= 0 && a.x < xmax && a.y >= 0 && a.y < ymax && a.z >= 0 && a.z < zmax;
}
bool& occu (triple a)
{
	return occupied[a.x][a.y][a.z];
}
bool dfs (int step, triple t, int dir)
{
	if (t == goal && dir == g_dir) return true;
	else if (step == 0) return false;

	triple s1, s2, s3, s4;
	for (int i = 0; i < 6; i++) if (i != dir && (i != (dir ^ 1)))
	{
		s1 = t + d[dir];
		s2 = s1 + d[dir];
		s3 = s2 + d[i];
		s4 = s3 + d[i];
		if (in(s1) && in(s2) && in(s3) && in(s4) && !occu(s1) && !occu(s2) && !occu(s3) && !occu(s4))
		{
			occu(s1) = occu(s2) = occu(s3) = occu(s4) = true;
			if (dfs(step - 1, s4, i)) return true;
			occu(s1) = occu(s2) = occu(s3) = occu(s4) = false;
		}
	}
	for (int i = 0; i < 6; i++) if (i != dir && (i != (dir ^ 1)))
	{
		s1 = t + d[dir];
		s2 = s1 + d[dir];
		s3 = s2 + d[dir];
		s4 = s3 + d[i];
		if (in(s1) && in(s2) && in(s3) && in(s4) && !occu(s1) && !occu(s2) && !occu(s3) && !occu(s4))
		{
			occu(s1) = occu(s2) = occu(s3) = occu(s4) = true;
			if (dfs(step - 1, s4, i)) return true;
			occu(s1) = occu(s2) = occu(s3) = occu(s4) = false;
		}
	}
	return false;
}

int str2dir (const char* a)
{
	int r1, r2;
	r1 = (a[0] == '-');
	if (a[1] == 'x') r2 = 0;
	else if (a[1] == 'y') r2 = 2;
	else r2 = 4;
	return r2 | r1;
}

int main ()
{
	int kase = 0;
	while (scanf("%d", &xmax), xmax)
	{
		scanf("%d %d", &ymax, &zmax);
		triple init, normal(-1, -1, -1); char str[5];
		scanf("%d %d %d", &init.x, &init.y, &init.z);
		scanf("%s", str);
		int idir = str2dir(str);
		init = init + normal - d[idir];
		scanf("%d %d %d", &goal.x, &goal.y, &goal.z);
		goal = goal + normal;
		scanf("%s", str);
		g_dir = str2dir(str);
		int ans;
		for (ans = 0; ans <= 6; ans++)
		{
			memset(occupied, 0, sizeof occupied);
			if (dfs(ans, init, idir)) break;
		}
		printf("Case %d: ", ++kase);
		if (ans <= 6) printf("%d\n", ans);
		else printf("Impossible\n");
	}
	return 0;
}
