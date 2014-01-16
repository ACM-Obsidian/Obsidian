#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 110;

int arr[N][N], w, h, tw, th;
int cor[N][N];

struct Quad
{
	int a[4];
	Quad (void) {}
	Quad (int a0, int a1, int a2, int a3)
	{
		a[0] = a0, a[1] = a1, a[2] = a2, a[3] = a3;
	}
	int& operator[] (const int& x)
	{
		return a[x];
	}
	bool even (void)
	{
		bool res = true;
		for (int i = 0; i < 3; i++) for (int j = i + 1; j < 4; j++)
			if (a[i] > a[j]) res = !res;
		return res;
	}
};
Quad quad (int x, int y, int t[][N] = arr)
{
	int xx = h - 1 - x, yy = w - 1 - y;
	return Quad(t[x][y], t[x][yy], t[xx][y], t[xx][yy]);
}

int ans[1000010], ansmax;

inline int row_r (int x) { return x + 1; }
inline int col_r (int y) { return -y - 1; }
void turn (int cmd)
{
	ans[ansmax++] = cmd;
	if (cmd > 0)
	{
		cmd -= 1;
		for (int y = 0; y < tw; y++) swap(arr[cmd][y], arr[cmd][w - 1 - y]);
	}
	else
	{
		cmd = -cmd - 1;
		for (int x = 0; x < th; x++) swap(arr[x][cmd], arr[h - 1 - x][cmd]);
	}
}
void quad_sort (Quad& q, int x, int y)
{
	int xx = h - 1 - x, yy = w - 1 - y;
	Quad s = q;
	sort(&s[0], &s[4]);
	if (s[0] == q[3])
	{
		ans[ansmax++] = row_r(xx);
		ans[ansmax++] = col_r(yy);
		ans[ansmax++] = row_r(xx);
		ans[ansmax++] = col_r(yy);
		int t = q[1]; q[1] = q[3]; q[3] = q[2]; q[2] = t;
	}
	while (q[0] != s[0])
	{
		ans[ansmax++] = row_r(x);
		ans[ansmax++] = col_r(y);
		ans[ansmax++] = row_r(x);
		ans[ansmax++] = col_r(y);
		int t = q[0]; q[0] = q[1]; q[1] = q[2]; q[2] = t;
	}
	while (q[1] != s[1])
	{
		ans[ansmax++] = row_r(xx);
		ans[ansmax++] = col_r(yy);
		ans[ansmax++] = row_r(xx);
		ans[ansmax++] = col_r(yy);
		int t = q[1]; q[1] = q[3]; q[3] = q[2]; q[2] = t;
	}
}

int main ()
{
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		scanf("%d %d", &w, &h);
		tw = w / 2, th = h / 2;
		int cur = 1;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				scanf("%d", &arr[i][j]), cor[i][j] = cur++;
		bool ok = true;
		ansmax = 0;
		if (w & 1) // width is odd
		{
			if (arr[0][tw] != cor[0][tw]) turn(col_r(tw));
			for (int x = 0; ok && x < h; x++)
				if (arr[x][tw] != cor[x][tw]) ok = false;
		}
		if (ok && (h & 1)) // height is odd
		{
			if (arr[th][0] != cor[th][0]) turn(row_r(th));
			for (int y = 0; ok && y < w; y++)
				if (arr[th][y] != cor[th][y]) ok = false;
		}
		if (ok)
		{
			// row
			for (int y = 0; y < tw; y++)
				if (!quad(0, y).even()) turn(col_r(y));
			// col
			for (int x = 1; x < th; x++)
				if (!quad(x, 0).even()) turn(row_r(x));
			// all
			for (int x = 0; ok && x < th; x++)
				for (int y = 0; ok && y < tw; y++)
				{
					Quad q = quad(x, y);
					Quad s = quad(x, y, cor);
					if (!q.even()) ok = false;
					else quad_sort(q, x, y);
					for (int i = 0; i < 4; i++) if (q[i] != s[i]) ok = false;
				}
		}
		if (!ok) printf("IMPOSSIBLE\n");
		else
		{
			printf("POSSIBLE %d", ansmax);
			for (int i = 0; i < ansmax; i++)
			{
				if (ans[i] > 0) printf(" R%d", ans[i]);
				else printf(" C%d", -ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
