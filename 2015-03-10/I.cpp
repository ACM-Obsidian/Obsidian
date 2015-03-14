#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

map<string, int> M;
set<string> S;

int main(void) {
	freopen("bets.in", "r", stdin);
	freopen("bets.out", "w", stdout);
	int kase; scanf("%d", &kase); while (kase--) {
		M.clear();
		S.clear();
		for (int i = 1; i <= 16; i++) {
			string s1, s2; int t1, t2;
			cin >>s1>>s2>>t1>>t2;
			if (t1 > t2) M[s2]++; else M[s1]++;
			S.insert(s1);
			S.insert(s2);
		}
		for (__typeof(S.begin()) it = S.begin(); it != S.end(); ++it) {
			if (M[*it] == 0) {cout <<*it<<endl; break;}
		}
	}
	return 0;
}

