#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <vector>
#include <iostream>
using namespace std;

const int N = 80;
bitset<N> cover[N];
bitset<N> sp[N];
vector<int> can_cover[N];

bool res[N], prohibit[N];
int n, max_dep, first;

inline int h (bitset<N> b)
{
	first = -1;
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		if (!b[i])
		{
			b |= sp[i], ++res;
			if (first == -1 || can_cover[i].size() < can_cover[first].size()) first = i;
		}
	}
	return res;
}
bool dfs (int dep, bitset<N> b)
{
//	printf("N = %d, DFS %d (%d)  ", n, dep, max_dep);
//	cout << b << endl;
//	getchar();
//	
	if (h(b) + dep > max_dep) return false;
	int tf = first;
	if (tf == -1) return true;
//
//	printf("FIRST = %d\n", tf);
//
	for (int i = 0; i < can_cover[tf].size(); i++)
	{
		int c = can_cover[tf][i];
//
//		printf("COVERS %d (I %d, SIZE %d)\n", c, i, can_cover[tf].size());
//
		res[c] = true;
		if (dfs(dep + 1, b | cover[c])) return true;
		res[c] = false;
	}
	return false;
}

int main ()
{
	int kase = 0; while (scanf("%d", &n) == 1)
	{
		for (int i = 0; i < n; i++) cover[i].reset();
		for (int i = 0; i < n; i++)
		{
			char str[N]; scanf("%s", str);
			for (int j = 0; j < n; j++)
			{
				if (j == i || str[j] == '1') cover[i].set(j);
			}
			prohibit[i] = false;
//			cout << cover[i] << endl;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) if (i != j && (cover[i] & cover[j]) == cover[j]) prohibit[j] = true;//, printf("%d PROHIBITED\n", j);
		}
		for (int i = 0; i < n; i++)
		{
			sp[i].reset();
			can_cover[i].clear();
			for (int j = 0; j < n; j++) if (!prohibit[j] && cover[j][i]) sp[i] |= cover[j], can_cover[i].push_back(j);
		}
		for (max_dep = 0; ; ++max_dep)
		{
			bitset<N> b;
			b.reset();
			memset(res, 0, sizeof res);
			if (dfs(0, b)) break;
		}
		printf("Case %d: %d", ++kase, max_dep);
		for (int i = 0; i < n; i++) if (res[i]) printf(" %d", i + 1);
		puts("");
	}
	return 0;
}
