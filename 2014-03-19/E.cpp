#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

const int N = 50;
char ori[N]; int len, to, tz;

struct status
{
	int one, zero, proc;
	status (void) {}
	status (int _o, int _z, int _p) : one(_o), zero(_z), proc(_p) {}
	bool operator < (const status& s) const
	{
		if (one != s.one) return one < s.one;
		else if (zero != s.zero) return zero < s.zero;
		return proc < s.proc;
	}
};

map<status, char> hash;
vector<status> que[N];
void trans (status cur)
{
	int pl = cur.proc, one = cur.one, zero = cur.zero;
	// printf("TRANS %d %d %d, HASH %d\n", pl, one, zero, hash[cur]);
	if (ori[pl] == '1')
	{
		assert(pl == 0 || ori[pl - 1] == '0');
		int tt = 0;
		for (int i = pl; i < len; i++)
		{
			tt = (tt << 1) + (ori[i] == '1');
			if (tt != 3 && tt + one > to) break;
			if (tt == 2) continue;
			if (i + 1 == len || ori[i + 1] == '0')
			{
				// to status(i + 1, one + tt, zero)
				status tar(one + tt, zero, i + 1);
				if (one + tt <= to)
				{
					// printf("TO %d %d %d\n", tar.proc, tar.one, tar.zero);
					if (hash.find(tar) == hash.end()) hash[tar] = hash[cur], que[i + 1].push_back(tar);
					else hash[tar] = 2;
				}

				if (tt == 3)
				{
					tar = status(one + 2, zero, i + 1);
					if (one + 2 <= to)
					{
						// printf("TO %d %d %d\n", tar.proc, tar.one, tar.zero);
						if (hash.find(tar) == hash.end()) hash[tar] = hash[cur], que[i + 1].push_back(tar);
						else hash[tar] = 2;
					}
				}
			}
		}
	}
	else // 0
	{
		// printf("TO %d %d %d\n", pl + 1, one, zero + 1);
		// to status (pl + 1, one, zero + 1)
		status tar(one, zero + 1, pl + 1);
		if (zero + 1 > tz) return;
		if (hash.find(tar) == hash.end()) hash[tar] = hash[cur], que[pl + 1].push_back(tar);
		else hash[tar] = 2;
	}
}

int main ()
{
	int l, n, kase = 0; while (scanf("%d %d", &l, &n), l)
	{
		scanf("%s", ori);
		len = strlen(ori);
		to = n, tz = l - n;
		// printf("TO = %d, TZ = %d\n", to, tz);
		hash.clear();
		hash[status(0, 0, 0)] = 1;
		que[0].push_back(status(0, 0, 0));
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < que[i].size(); j++)
				trans(que[i][j]);
		}
		for (int i = 0; i <= len; i++) que[i].clear();
		printf("Case #%d: ", ++kase);
		if (hash.find(status(to, tz, len)) == hash.end()) printf("NO\n");
		else if (hash[status(to, tz, len)] == 1) printf("YES\n");
		else printf("NOT UNIQUE\n");
	}
	return 0;
}
