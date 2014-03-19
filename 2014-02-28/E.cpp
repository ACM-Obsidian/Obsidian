#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

inline bool leap (int y)
{
	return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}
inline int day_year (int y)
{
	return leap(y) ? 366 : 365;
}
int md[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
inline int day_month (int y, int m)
{
	return (leap(y) && m == 2) ? 29 : md[m - 1];
}

inline int date2time (int y, int m, int d)
{
	int res = 0;
	for (int i = 1700; i < y; i++) res += day_year(i);
	for (int i = 1; i < m; i++) res += day_month(y, i);	
	res += (d - 1);
	return res;
}
inline void time2date (int dd, int &y, int &m, int &d)
{
	y = 1700, m = 1, d = 1;
	while (dd >= day_year(y))
	{
		dd -= day_year(y);
		++y;
	}
	while (dd >= day_month(y, m))
	{
		dd -= day_month(y, m);
		++m;
	}
	d += dd;
}

inline int readtime (void)
{
	char str[16];
	scanf("%s", str);
	for (int i = 0; i < 8; i++) str[i] -= '0';
	int y = str[0] * 1000 + str[1] * 100 + str[2] * 10 + str[3];
	int m = str[4] * 10 + str[5];
	int d = str[6] * 10 + str[7];
	return date2time(y, m, d);
}
inline void outdate (int dd)
{
	int y, m, d; time2date(dd, y, m, d);
	printf("%d/%d/%d", m, d, y);
}

const int N = 1010;
int st[N], ed[N];
int stcut[N], edcut[N];

typedef pair<int, int> pii;
#define X first
#define Y second

vector<pii> arr[2];

int main ()
{
	freopen("intersect.in", "r", stdin);
	int n, m, kase = 0; while (scanf("%d %d", &n, &m), n || m)
	{
		++kase;
		for (int i = 0; i < n; i++)
		{
			stcut[i] = readtime(), edcut[i] = readtime();
			if (stcut[i] > edcut[i]) swap(stcut[i], edcut[i]);
		}
		arr[0].clear(), arr[1].clear();
		int now = 0, last = 1;
		for (int i = 0; i < m; i++)
		{
			st[i] = readtime(), ed[i] = readtime();
			if (st[i] > ed[i]) swap(st[i], ed[i]);
			arr[now].push_back(pii(st[i], ed[i]));
		}
		for (int i = 0; i < n; i++)
		{
			swap(now, last);
			arr[now].clear();
			for (int j = 0; j < arr[last].size(); j++)
			{
				int x = arr[last][j].X, y = arr[last][j].Y;
				// Case 1
				if (stcut[i] <= x && y <= edcut[i])
					continue;
				// Case 5
				else if (edcut[i] < x || y < stcut[i])
				{
					arr[now].push_back(pii(x, y));
				}
				// Case 2
				else if (x < stcut[i] && y <= edcut[i])
					arr[now].push_back(pii(x, stcut[i] - 1));
				// Case 3
				else if (stcut[i] <= x && edcut[i] < y)
					arr[now].push_back(pii(edcut[i] + 1, y));
				// Case 4
				else if (x < stcut[i] && edcut[i] < y)
				{
					arr[now].push_back(pii(x, stcut[i] - 1));
					arr[now].push_back(pii(edcut[i] + 1, y));
				}
			}
		}
		sort(arr[now].begin(), arr[now].end());
		printf("Case %d:\n", kase);
		if (arr[now].size() == 0)
			printf("    No additional quotes are required.\n");
		else for (int i = 0; i < arr[now].size(); )
		{
			int p = i + 1;
			int x = arr[now][i].X, y = arr[now][i].Y;
			while (p < arr[now].size() && arr[now][p].X <= y + 1)
				y = max(y, arr[now][p].Y), ++p;
			i = p;
			printf("    ");
			outdate(x);
			if (y > x)
			{
				printf(" to ");
				outdate(y);
			}
			printf("\n");
		}
		printf("\n");
	}
	system("pause");
	return 0;
}
