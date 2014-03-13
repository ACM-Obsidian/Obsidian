#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const int hashmax = 133331;

typedef pair<int, int> pii;
#define X first
#define Y second

struct hashTable
{
	vector<pii> storage[hashmax];
	hashTable (void) {}
	void clear (void)
	{
		for (int i = 0; i < hashmax; i++) storage[i].clear();
	}
	void set (int a, int x)
	{
		int key = a % hashmax;
		for (int i = 0; i < storage[key].size(); i++)
			if (storage[key][i].X == a)
			{
				storage[key][i].Y = x;
				return;
			}
		storage[key].push_back(pii(a, x));
	}
	int get (int a)
	{
		int key = a % hashmax;
		for (int i = 0; i < storage[key].size(); i++)
			if (storage[key][i].X == a)
				return storage[key][i].Y;
		return -1;
	}
	void setMin (int a, int x)
	{
		int key = a % hashmax;
		for (int i = 0; i < storage[key].size(); i++)
			if (storage[key][i].X == a)
			{
				storage[key][i].Y = min(storage[key][i].Y, x);
				return;
			}
		storage[key].push_back(pii(a, x));
	}
};

inline int getPl (int s, int p)
{
	return (s & (3 << p * 2)) >> (p * 2);
}
inline int setPl (int s, int p, int v)
{
	return s & ~(3 << p * 2) | (v << p * 2);
}
inline int setPl2 (int s, int j, int v1, int v2)
{
	return setPl(setPl(s, j, v1), j + 1, v2);
}

int tmap[10][10];
hashTable ht[2];

int main ()
{
	freopen("E.txt", "r", stdin);
	int n, m; while (scanf("%d %d", &n, &m) == 2, n)
	{
		ht[0].clear(), ht[1].clear();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) scanf("%d", &tmap[i][j]);
		int now = 0, last = 1;
		ht[now].set(0, 0);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				swap(now, last);
				ht[now].clear();
				for (int key = 0; key < hashmax; key++)
					for (int tt = 0; tt < ht[last].storage[key].size(); tt++)
					{
						int s = ht[last].storage[key][tt].X, val = ht[last].storage[key][tt].Y, ts;
						int s1 = getPl(s, j), s2 = getPl(s, j + 1);
						if (tmap[i][j] == 0)
						{
							if (s1 == 0 && s2 == 0)
							{
								ht[now].setMin(s, val);
								ts = setPl2(s, j, 2, 2);
								ht[now].setMin(ts, val + 1);
								ts = setPl2(s, j, 3, 3);
								ht[now].setMin(ts, val + 1);
							}
							else if (s1 == 0 && s2 == 2 || s1 == 2 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 2);
								ht[now].setMin(ts, val + 1);
								ts = setPl2(s, j, 2, 0);
								ht[now].setMin(ts, val + 1);
							}
							else if (s1 == 0 && s2 == 3 || s1 == 3 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 3);
								ht[now].setMin(ts, val + 1);
								ts = setPl2(s, j, 3, 0);
								ht[now].setMin(ts, val + 1);
							}
							else if (s1 == 2 && s2 == 2 || s1 == 3 && s2 == 3)
							{
								ts = setPl2(s, j, 0, 0);
								ht[now].setMin(ts, val + 1);
							}
						}
						else if (tmap[i][j] == 1)
						{
							if (s1 == 0 && s2 == 0)
							{
								ht[now].setMin(s, val);
							}
						}
						else if (tmap[i][j] == 2)
						{
							if (s1 == 0 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 2);
								ht[now].setMin(ts, val + 1);
								ts = setPl2(s, j, 2, 0);
								ht[now].setMin(ts, val + 1);
							}
							else if (s1 == 0 && s2 == 2 || s1 == 2 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 0);
								ht[now].setMin(ts, val + 1);
							}
						}
						else if (tmap[i][j] == 3)
						{
							if (s1 == 0 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 3);
								ht[now].setMin(ts, val + 1);
								ts = setPl2(s, j, 3, 0);
								ht[now].setMin(ts, val + 1);
							}
							else if (s1 == 0 && s2 == 3 || s1 == 3 && s2 == 0)
							{
								ts = setPl2(s, j, 0, 0);
								ht[now].setMin(ts, val + 1);
							}
						}
					}
			}
			// in the end of each row
			swap(now, last);
			ht[now].clear();
			for (int key = 0; key < hashmax; key++)
				for (int tt = 0; tt < ht[last].storage[key].size(); tt++)
				{
					int s = ht[last].storage[key][tt].X, val = ht[last].storage[key][tt].Y, ts;
					if (getPl(s, m) == 0)
					{
						ts = s << 2;
						ht[now].setMin(ts, val);
					}
				}
		}
		int res = ht[now].get(0);
		if (res == -1) printf("0\n");
		else printf("%d\n", ht[now].get(0) - 2);
	}
	return 0;
}
