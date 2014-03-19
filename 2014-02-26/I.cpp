#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

inline bool leap (int y)
{
	return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}
inline int day (int y)
{
	return leap(y) ? 366 : 365;
}
int md[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

inline int day_m (int y, int m)
{
	return m == 2 ? (leap(y) ? 29 : 28) : md[m - 1];
}

int date_to_time (int y, int m, int d)
{
	int res = 100000;
	for (int i = 1900; i < y; i++) res += day(i);
	for (int i = 1; i < m; i++)
	{
		res += day_m(y, i);
	}
	res += (d - 1);
	return res;
}
void time_to_date (int tt, int &y, int &m, int &d)
{
	y = 1900, m = 1, d = 1;
	int cur = 100000;
	while (tt < cur)
	{
		--y;
		cur -= day(y);
	}
	while (cur + day(y) <= tt)
	{
		cur += day(y);
		++y;
	}
	while (cur + day_m(y, m) <= tt)
	{
		cur += day_m(y, m);
		++m;
	}
	d += (tt - cur);
}

char str[20];
priority_queue<int> pq;

bool have_test[300010];
vector<int> interval[300010];

int main ()
{
	freopen("jenny.in", "r", stdin);
	int last_day = date_to_time(2100, 12, 31);
	memset(have_test, 0, sizeof have_test);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", str);
		int y, m, d, test; scanf("%d.%d.%d", &d, &m, &y);
		test = date_to_time(y, m, d);
		have_test[test] = true;
		int dur; scanf("%d", &dur);
		interval[test].push_back(test - dur);
//		printf("[%d-%d-%d]: %d -> %d\n", y, m, d, test-dur, test);
	}
	int ans = last_day; bool ok = true;
	for (int i = last_day; i >= 0; i--)
	{
		for (int j = 0; j < interval[i].size(); j++) pq.push(interval[i][j]);//, printf("@%d: PUSH %d\n", i, interval[i][j]);
		if (!pq.empty() && pq.top() > i)
		{
			ok = false;
			break;
		}
		if (!have_test[i])
		{
			if (!pq.empty())
			{
				ans = i;
				pq.pop();
			}
		}
	}
	if (!ok) printf("Impossible\n");
	else
	{
		int y, m, d; time_to_date(ans, y, m, d);
		printf("%02d.%02d.%d\n", d, m, y);
	}
	return 0;
}
