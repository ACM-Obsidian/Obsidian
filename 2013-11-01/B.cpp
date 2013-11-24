#include <cstdio>
#include <cstdlib>
#include <set>
typedef std::pair<int, int> pair;
typedef std::set<pair> set;
set T, T2;
int main() {
	freopen("control.in","r",stdin);
	freopen("control.out","w",stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y, l;
		scanf("%d%d%d", &x, &y, &l);
		for (int dx = -l-1; dx <= l+1; dx++)
			for (int dy = -l-2+abs(dx); dy <= l+2-abs(dx); dy++) {
				if (dx == 0 && abs(dy) == l+2) continue;
				T.insert(pair(x+dx, y+dy));
			}
		for (int dy = -2; dy <= 2; dy++)
			T2.insert(pair(x-l-2, y+dy)), T2.insert(pair(x+l+2, y+dy));
		for (int dx = -1; dx <= 1; dx++)
			T2.insert(pair(x+dx, y-l-2)), T2.insert(pair(x+dx, y+l+2));
		for (int dx = -l-1; dx <= l+1; dx++) if (abs(dx) > 1)
			for (int dy = l+3-abs(dx); dy <= l+4-abs(dx); dy++)
				T2.insert(pair(x+dx, y+dy)), T2.insert(pair(x+dx, y-dy));
	}
	int ans = T.size();
	for (set::iterator it = T2.begin(); it != T2.end(); it++) {
		if (T.find(*it) != T.end()) continue;
		int x = it->first, y = it->second;
		int Flag = 0;
		for (int dx1 = -1; !Flag && dx1 <= 0; dx1++)
			for (int dy1 = -1; !Flag && dy1 <= 0; dy1++) {
				int flag = 1;
				for (int dx = dx1; flag && dx <= dx1+1; dx++)
					for (int dy = dy1; flag && dy <= dy1+1; dy++)
						if (T.find(pair(x+dx, y+dy)) != T.end()) flag = 0;
				if (flag) Flag = 1;
			}
		if (!Flag) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
