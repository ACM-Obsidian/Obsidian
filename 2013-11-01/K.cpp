#include <cstdio>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

int n, father[MAXN]; vector<pair<long long, int> > tmp; int size[MAXN];
long long hash[MAXN];

set<long long> S;
map<long long, int> M;

long long pow[MAXN];

long long base = 1333333331ll;

inline void BFS(void) {
	for (int i = n; i >= 1; i--) {
		tmp.clear();
		size[father[i]] += ++size[i];
		for (Edge *p = a[i]; p; p = p->next) tmp.push_back(make_pair(hash[p->y], p->y) );
		sort(tmp.begin(), tmp.end());
		long long &ret = hash[i]; ret = size[i];
		for (int j = 0; j < (int)tmp.size(); j++) {
			ret = ret * pow[size[tmp[j].second]] + tmp[j].first;
		}
		S.insert(ret);
	}
}

int main(void) {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	scanf("%d", &n); pow[0] = 1;
	for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * base;
	for (int i = 2; i <= n; i++) {
		int y; scanf("%d", &y);
		a[y] = new Edge(i, a[y]);
		father[i] = y;
	}
	
	BFS();
	int L = 0;
	for (set<long long>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++L;
	for (int i = 1; i <= n; i++) printf("%d%c", M[hash[i]], " \n"[i == n]);
	return 0;
}

