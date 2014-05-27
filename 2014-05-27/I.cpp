#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<long long, long long> pii;
typedef pair<pii, int> rec;
#define X first
#define Y second

const int N = 200010;
rec point[N], temp[N], setL[N];
pii ori[N];

inline long long sqr (long long x)
{
	return x * x;
}
inline long long dist (int x, int y)
{
	return sqr(ori[x].X - ori[y].X) + sqr(ori[x].Y - ori[y].Y);
}
bool compY (const rec& a, const rec& b)
{
	if (a.X.Y != b.X.Y) return a.X.Y < b.X.Y;
	else if (a.X.X != b.X.X) return a.X.X < b.X.X;
	return a.Y < b.Y;
}
pair<int, int> min_dist (int l, int r)
{
	// printf("MIN_DIST %d %d\n", l, r);

	if (r - l <= 5)
	{
		int a = point[l].Y, b = point[l + 1].Y;
		for (int i = l; i < r; i++)
			for (int j = i + 1; j < r; j++)
			{
				// printf("DIST %d %d = %lld\n", point[i].Y, point[j].Y, dist(point[i].Y, point[j].Y));
				if (dist(point[i].Y, point[j].Y) < dist(a, b)) a = point[i].Y, b = point[j].Y;
			}
		sort(point + l, point + r, compY);
		return make_pair(a, b);
	}
	else
	{
		int m = (l + r) / 2;
		long long midline = point[m].X.X;
		pair<int, int> tl = min_dist(l, m), tr = min_dist(m, r), res;
		if (dist(tl.X, tl.Y) < dist(tr.X, tr.Y)) res = tl;
		else res = tr;
		// printf("TL = (%d, %d), TR = (%d, %d), RES = (%d, %d)\n", tl.X, tl.Y, tr.X, tr.Y, res.X, res.Y);
		long long td = dist(res.X, res.Y);
		long long dlt = (long long)(sqrt((double) td) + 0.5);
		if (dlt * dlt < td) ++dlt;

		// merge
		int ll = l, rr = m, p = l;
		while (ll < m || rr < r)
		{
			if (ll == m) temp[p++] = point[rr++];
			else if (rr == r) temp[p++] = point[ll++];
			else
			{
				if (compY(point[ll], point[rr])) temp[p++] = point[ll++];
				else temp[p++] = point[rr++];
			}
		}
		// printf("MIDLINE = %lld\n", midline);
		p = 0;
		for (int i = l; i < r; i++)
		{
			point[i] = temp[i];
			// printf("ARR %d -> ((%lld, %lld), %d)", i, temp[i].X.X, temp[i].X.Y, temp[i].Y);
			if (point[i].Y < m && midline - point[i].X.X <= dlt) setL[p++] = point[i];//, printf(", MID");
			else if (point[i].Y >= m && point[i].X.X - midline <= dlt) setL[p++] = point[i];//, printf(", MID");
			// printf("\n");
		}

		// cal
		for (int i = 0; i < p; i++)
			for (int j = i + 1; j < p && j < i + 10; j++)
			{
				long long dd = dist(setL[i].Y, setL[j].Y);
				if (dd < td)
				{
					td = dd;
					res = make_pair(setL[i].Y, setL[j].Y);
				}
			}

		// printf("[%d, %d) : RES = (%d, %d)\n", l, r, res.X, res.Y);
		return res;
	}
}

int main ()
{
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld", &ori[i].X, &ori[i].Y);
		point[i].X = ori[i];
		point[i].Y = i;
	}
	sort(point, point + n);
	// for (int i = 0; i < n; i++)
	// 	printf("((%lld, %lld), %d)\n", point[i].X.X, point[i].X.Y, point[i].Y);
	pair<int, int> res = min_dist(0, n);
	printf("%d %d\n", res.X + 1, res.Y + 1);
	return 0;
}
