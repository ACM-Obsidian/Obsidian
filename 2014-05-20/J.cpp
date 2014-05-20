#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

typedef pair<long long, long long> pii;
#define X first
#define Y second

long long cross (const pii& a, const pii& b)
{
	return a.X * b.Y - a.Y * b.X;
}

const int N = 200010, M = 2000010;

pii point[N];

typedef pair<int, int> edge;
typedef pair<int, int> s_rec;
map<edge, int> mei;
int vr;
vector<s_rec> rec[N];
int nxt[M], left[M];
long long cr[M];

int qt[M], qa[M], qb[M]; long long ans[M];

int ufs[M]; long long area[M];
int ufs_query (int x)
{
	return (ufs[x] == x) ? x : (ufs[x] = ufs_query(ufs[x]));
}

inline int quadr (pii a)
{
	if (a.X < 0 && a.Y <= 0) return 0;
	else if (a.X >= 0 && a.Y < 0) return 1;
	else if (a.X > 0 && a.Y >= 0) return 2;
	else return 3;
}
int base;
bool comp (const s_rec& a, const s_rec& b)
{
	pii ta(point[a.X].X - point[base].X, point[a.X].Y - point[base].Y);
	pii tb(point[b.X].X - point[base].X, point[b.X].Y - point[base].Y);
	if (quadr(ta) != quadr(tb)) return quadr(ta) < quadr(tb);
	else return cross(ta, tb) > 0;
}

bool sch[M];

void dfs (long long s_area, int x, int start, bool first, int id)
{
	if (!first && x == start)
	{
		// printf("AREA %d = %lld\n", id, s_area);

		if (s_area <= 0) s_area = -1;
		area[id] = s_area;
	}
	else
	{
		left[x] = id;

		// printf("%d ASSOCIATED TO %d\n", x, id);

		sch[x] = true;
		dfs(s_area + cr[x], nxt[x], start, false, id);
	}
}

int main ()
{
	// freopen("in", "r", stdin);

	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld %lld", &point[i].X, &point[i].Y);
	int q; scanf("%d", &q);
	vr = 0;
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d %d", &qt[i], &qa[i], &qb[i]);
		if (qt[i] == 1) 
		{
			mei[edge(qa[i], qb[i])] = vr;

			// printf("%d -> %d: %d\n", qa[i], qb[i], vr);

			cr[vr] = cross(point[qa[i]], point[qb[i]]);
			rec[qa[i]].push_back(s_rec(qb[i], vr++));
			
			mei[edge(qb[i], qa[i])] = vr;

			// printf("%d -> %d: %d\n", qb[i], qa[i], vr);

			cr[vr] = cross(point[qb[i]], point[qa[i]]);
			rec[qb[i]].push_back(s_rec(qa[i], vr++));
		}
	}
	for (int k = 0; k < n; k++)
	{
		base = k;
		sort(rec[k].begin(), rec[k].end(), comp);
		int s = rec[k].size();
		for (int i = 0; i < s; i++)
		{
			int j = i - 1;
			if (j == -1) j = s - 1;
			nxt[rec[k][i].Y ^ 1] = rec[k][j].Y;
			
			// printf("NEXT %d = %d\n", rec[k][i].Y ^ 1, rec[k][j].Y);
		}
	}
	memset(sch, 0, sizeof sch);
	int ar = 0;
	for (int i = 0; i < vr; i++) if (!sch[i]) dfs(0, i, i, true, ar++);
	for (int i = 0; i < ar; i++) ufs[i] = i;
	for (int i = q - 1; i >= 0; i--)
	{
		int v = left[mei[edge(qa[i], qb[i])]];
		// printf("EDGE %d %d = %d\n", qa[i], qb[i], v);
		if (qt[i] == 0) ans[i] = area[ufs_query(v)];//, printf("AREA %d\n", ufs_query(v));
		else
		{
			int vt = left[mei[edge(qb[i], qa[i])]];
			v = ufs_query(v), vt = ufs_query(vt);
			if (v != vt)
			{
				// printf("MERGE %d %d\n", v, vt);
				ufs[vt] = v;
				if (area[v] >= 0 && area[vt] >= 0) area[v] += area[vt];
				else area[v] = -1;
			}
		}
	}
	for (int i = 0; i < q; i++) if (qt[i] == 0)
	{
		printf("%lld\n", ans[i]);
	}
	// system("pause");
	return 0;
}
