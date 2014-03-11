#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
set<pii> sp;

const int N = 10010, M = 100010;
int price[N];
bool proc[N];

vector<pii> craft[N];

int main ()
{
	freopen("dwarf.in", "r", stdin);
	freopen("dwarf.out", "w", stdout);
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &price[i]), proc[i] = false, sp.insert(pii(price[i], i));
	for (int i = 0; i < m; i++)
	{
		int a, x, y; scanf("%d %d %d", &a, &x, &y); --a, --x, --y;
		craft[x].push_back(pii(y, a));
		craft[y].push_back(pii(x, a));
	}
	while (!sp.empty())
	{
		pii a = *sp.begin();
		sp.erase(a);
		int x = a.second;
		proc[x] = true;
		for (int i = 0; i < craft[x].size(); i++)
		{
			int y = craft[x][i].first, a = craft[x][i].second;
			if (proc[y] && !proc[a] && price[x] + price[y] < price[a])
			{
				sp.erase(pii(price[a], a));
				price[a] = price[x] + price[y];
				sp.insert(pii(price[a], a));
			}
		}
	}
	printf("%d\n", price[0]);
	fclose(stdin), fclose(stdout);
	return 0;
}
