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
	freopen("lines.in", "r", stdin);
	freopen("lines.out", "w", stdout);
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

	int q; scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int x1, y1, x2, y2, dx, dy; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		dx = x2 - x1, dy = y2 - y1;
		if (dx < 0 || dx == 0 && dy < 0) dx = -dx, dy = -dy;
		int l = 0, r = t1-1;
		while (l < r) {
			int mid = l+r>>1;
			if (cross(cv1[mid]-cv1[mid+1], pii(dx, dy)) > 0) l = mid+1;
			else r = mid;
		}
		int c1 = l;
		l = 0, r = t2-1;
		while (l < r) {
			int mid = l+r>>1;
			if (cross(cv2[mid]-cv2[mid+1], pii(-dx, -dy)) > 0) l = mid+1;
			else r = mid;
		}
		int c2 = l;
		long long s1 = cross(pii(x1, y1)-cv1[c1], pii(dx, dy)), s2 = cross(pii(x1, y1)-cv2[c2], pii(dx, dy));
		if (s1 == 0 || s2 == 0 || s1 > 0 && s2 < 0 || s1 < 0 && s2 > 0) puts("1");
		else puts("0");
	}
	return 0;
}
