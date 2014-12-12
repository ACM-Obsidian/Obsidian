#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1010, M = 1010;

int hd[N], to[M], nxt[M], deg[N], mr;
void link (int a, int b) {
	to[mr] = b, nxt[mr] = hd[a]; hd[a] = mr++;
	++deg[b];
}

int far[N];

int main () {
	int n, m; scanf("%d %d", &n, &m);
	++n;
	memset(hd, -1, sizeof hd);
	memset(deg, 0, sizeof deg);
	mr = 0;
	for (int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		--a, --b;
		link(b, a);
	}
	for (int i = 0; i < n; i++) far[i] = i;
	for (int i = n - 1; i >= 0; i--) {
		for (int p = hd[i]; p != -1; p = nxt[p]) {
			far[to[p]] = max(far[to[p]], far[i]);
		}
	}
	int ans = 0, farthest = 0;
	for (int i = 0; i < n; i++) {
		++ans;
		farthest = max(farthest, i);
		if (far[i] > farthest) ans += (far[i] - farthest) * 2, farthest = far[i];
	}
	printf("%d\n", ans);

	return 0;
}
