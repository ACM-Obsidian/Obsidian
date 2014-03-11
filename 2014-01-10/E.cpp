#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

typedef unsigned long long ull;

struct pack
{
	int k;
	ull q;
	int cd;

	ull weight;
	pack (void) {}
	pack (int _k, ull _q, int _cd) : k(_k), q(_q), cd(_cd)
	{
		weight = q;
		int tk = k;
		while (tk) --tk, weight *= 10;
	}
	bool operator < (const pack& p) const
	{
		return weight < p.weight;
	}
};

const int N = 100010;

priority_queue<pack> pq;
bool res[N];
vector<pack> arr[20];

int main ()
{
	freopen("exact.in", "r", stdin);
	freopen("exact.out", "w", stdout);
	ull z; int n; cin >> z >> n;
	for (int i = 0; i < n; i++)
	{
		int x; ull y;
		cin >> x >> y;	
		arr[x].push_back(pack(x, y, i + 1));
	}
	ull mod = 1, rem = 0;
	bool ok = true;
	int ans = 0;
	for (int i = 0; i <= 18; i++)
	{
		mod *= 10;
		ull tt = z % mod;
		for (int j = 0; j < arr[i].size(); j++) pq.push(arr[i][j]);
		while (rem < tt && !pq.empty())
		{
			pack tp = pq.top(); pq.pop();
			rem += tp.weight, ++ans, res[tp.cd - 1] = true;
		}
		if (rem < tt)
		{
			ok = false;
			break;
		}
		rem -= tt;
		z -= tt;
	}
	if (!ok) printf("-1\n");
	else
	{
		printf("%d\n", ans);
		bool first = true;
		for (int i = 0; i < n; i++) 
		{
			if (res[i])
			{
				if (first) first = false;
				else printf(" ");
				printf("%d", i + 1);
			}
		}
		printf("\n");
	}
	return 0;
}
