#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 200010;

typedef pair<int, int> pii;
#define X first
#define Y second

pii pt[N];
pii cv1[N], cv2[N];

inline long long cross (pii a, pii b)
{
	return (long long)a.X * b.Y - (long long)a.Y * b.X;
}
pii operator- (const pii& a, const pii& b)
{
	return pii(b.X - a.X, b.Y - a.Y);
}

int main ()
{
	freopen("points.in", "r", stdin);
	freopen("points.out", "w", stdout);

	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d %d", &pt[i].X, &pt[i].Y);
	int minX = 0;
	for (int i = 1; i < n; i++)
	{
		if (pt[i].X < pt[minX].X) minX = i;
		else if (pt[i].X == pt[minX].X && pt[i].Y < pt[minX].Y) minX = i;
	}
	int t1 = 0;
	for (int i = 0; i < n; i++)
	{
		int ii = minX + i;
		if (ii >= n) ii -= n;
		if (t1 && cv1[t1 - 1].X == pt[ii].X && cv1[t1 - 1].Y == pt[ii].Y) continue;
		if (t1 && cv1[t1 - 1].X >= pt[ii].X) break;
		cv1[t1++] = pt[ii];
	}
	int maxX = 0;
	for (int i = 1; i < n; i++)
	{
		if (pt[i].X > pt[maxX].X) maxX = i;
		else if (pt[i].X == pt[maxX].X && pt[i].Y > pt[maxX].Y) maxX = i; 
	}
	int t2 = 0;
	for (int i = 0; i < n; i++)
	{
		int ii = maxX + i;
		if (ii >= n) ii -= n;
		if (t2 && cv2[t2 - 1].X == pt[ii].X && cv2[t2 - 1].Y == pt[ii].Y) continue;
		if (t2 && cv2[t2 - 1].X <= pt[ii].X) break;
		cv2[t2++] = pt[ii];
	}
	reverse(cv2, cv2 + t2);

	int q; scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		if (x < pt[minX].X || x > pt[maxX].X)
		{
			puts("0");
			continue;
		}
		else if (x == pt[minX].X)
		{
			if (y >= cv1[0].Y && y <= cv2[0].Y) puts("1");
			else puts("0");
			continue;
		}
		else if (x == pt[maxX].X)
		{
			if (y >= cv1[t1 - 1].Y && y <= cv2[t2 - 1].Y) puts("1");
			else puts("0");
			continue;
		}
		int r1, r2, l, r;
		l = 0, r = t1 - 1;
		while (r - l > 1)
		{
			int mid = (l + r) / 2;
			if (cv1[mid].X > x) r = mid;
			else l = mid;
		}
		r1 = l;
		l = 0, r = t2 - 1;
		while (r - l > 1)
		{
			int mid = (l + r) / 2;
			if (cv2[mid].X > x) r = mid;
			else l = mid;
		}
		r2 = l;
		pii c1 = cv1[r1 + 1] - cv1[r1], c2 = cv2[r2] - cv2[r2 + 1];
		pii b1 = cv1[r1], b2 = cv2[r2 + 1];
		pii o(x, y);
		if (cross(c1, o - b1) < 0) puts("0");
		else if (cross(c1, o - b1) == 0) puts("1");
		else if (cross(c2, o - b2) < 0) puts("0");
		else if (cross(c2, o - b2) == 0) puts("1");
		else puts("2");
	}
	return 0;
}
