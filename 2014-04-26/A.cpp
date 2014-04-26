#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;

const int N = 200010, M = 200010;
typedef vector<int> vint;

vint le[N];
long long hle[N];
map<long long, int> vid;

typedef pair<int, int> pii;
pii edge[M];
set<int> neig[N];
bool sch[N];
int id[N];

long long hash(vint x) {
	long long s = 0;
	for (int i = 0; i < x.size(); i++)
		s = (s * 2333333 + (x[i]+1)) % 23333333333333333LL;
	return s;
}

int main ()
{
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int x, y; scanf("%d %d", &x, &y); --x, --y;
		edge[i] = pii(x, y);
		le[x].push_back(y);
		le[y].push_back(x);
	}
	int idmr = 0;
	for (int i = 0; i < n; i++)
	{
		sort(le[i].begin(), le[i].end());
		hle[i] = hash(le[i]);
		if (vid.find(hle[i]) == vid.end()) vid[hle[i]] = idmr++;
	}
	for (int i = 0; i < m; i++)
	{
		int x = vid[hle[edge[i].first]], y = vid[hle[edge[i].second]];
		neig[x].insert(y), neig[y].insert(x);
	}
	memset(sch, 0, sizeof sch);
	int nowid = 1;
	for (int i = 0; i < idmr; i++) if (!sch[i])
	{
		if (neig[i].size() == 1)
		{
			int p = *neig[i].begin(), prev = i; sch[i] = true; id[i] = nowid++;
			while (1)
			{
				if (neig[p].size() >= 3) break;
				sch[p] = true;
				id[p] = nowid++;
				if (neig[p].size() == 1) break;
				set<int>::iterator ite = neig[p].begin();
				int t1 = *ite;
				++ite; int t2 = *ite;
				int tt = t1;
				if (t1 == prev) tt = t2;
				prev = p, p = tt;
			}
			nowid++;
		}
		else if (neig[i].size() == 0)
		{
			sch[i] = true;
			id[i] = nowid++;
			nowid++;
		}
	}
	bool ok = true;
	for (int i = 0; i < idmr; i++) if (!sch[i])
	{
		ok = false;
		break;
	}
	if (!ok) puts("NET");
	else
	{
		puts("DA");
		for (int i = 0; i < n; i++) printf("%d%c", id[vid[hle[i]]], " \n"[i == n - 1]);
	}
	return 0;
}
