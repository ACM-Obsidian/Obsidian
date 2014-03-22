#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 100, inf = 10000000;

int a[MAXN][MAXN], n, m;
vector<pair<string, string> > E;
set<string> S; map<string, int> M;

int main(void) {
	int kase = 0;
	while (cin >>n >>m, n || m) {
		cout <<"Network "<<++kase<<": ";
		E.clear(); S.clear(); M.clear();
		for (int i = 1; i <= m; i++) {
			string s1, s2; cin >>s1 >>s2;
			E.push_back(make_pair(s1, s2));
			S.insert(s1);
			S.insert(s2);
		}
		int L = 0;
		for (set<string>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++L;
		for (int i = 1; i<= n; i++)
			for (int j = 1; j <= n; j++) a[i][j] = inf;
		for (int i = 1; i <= n; i++) a[i][i] = 0;
		for (int i = 0; i < E.size(); i++) {
			int x = M[E[i].first], y = M[E[i].second];
			a[x][y] = a[y][x] = 1;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		int Ans = -1, ok = 1;
		for (int i = 1; i<= n; i++)
			for (int j = 1; j <= n; j++) if (i != j) {
				Ans = max(Ans, a[i][j]);
				if (a[i][j] >= 1000) ok = 0;
			}
		if (ok) cout <<Ans<<endl; else cout <<"DISCONNECTED"<<endl;
		cout <<endl;
	}
	return 0;
}

