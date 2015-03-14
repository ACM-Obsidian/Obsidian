#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 210;

int a[MAXN][MAXN];
int b[MAXN][MAXN];
int d[MAXN];

int n, k, m, N;

priority_queue<pair<int, int> > Q;

void Dijkstra(int u, int *dis) {
	while (!Q.empty()) Q.pop();
	memset(dis, 0x3f, sizeof(int) * MAXN);
	Q.push(make_pair(0, u)); dis[u] = 0;
	for (int i = 1; i < N; i++) {
		while (!Q.empty() && -dis[Q.top().second] != Q.top().first) Q.pop();
		if (Q.empty()) break;
		int now = Q.top().second; Q.pop();
		for (int i = 1; i <= N; i++) if (dis[i] > dis[now] + a[now][i]) 
			Q.push(make_pair(-(dis[i] = dis[now] + a[now][i]), i));
	}
}

int vs, vt, inf;

// k -> number of doors, n -> number of sub rooms
int main(void) {
	freopen("fractal.in", "r", stdin);
	freopen("fractal.out", "w", stdout);
	scanf("%d%d%d", &k, &n, &m);
	memset(a, 0x3f, sizeof a); inf = a[0][0];
	N = (n + 1) * k;
	for (int i = 0; i <= N; i++) a[i][i] = 0;
	for (int i = 1; i <= m; i++) {
		int r1, id1, r2, id2;
		scanf("%d.%d - %d.%d", &r1, &id1, &r2, &id2); id1 ++; id2++;
		int x = r1 * k + id1, y = r2 * k + id2;
		if (x != y) a[x][y] = a[y][x] = 1;
	}
	scanf("%d%d", &vs, &vt); vs++; vt++;
	for (int _ = 1; (long long)_ <= 2000; _++) {
		for (int i = 1; i <= N; i++) Dijkstra(i, b[i]);
		int ok = 0;
		memcpy(a, b, sizeof a);
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++) {
				for (int d = 1; d <= n; d++) if (b[i][j] < a[d * k + i][d * k + j]) {
					ok = 1;
					a[d * k + i][d * k + j] = b[i][j];
				}
			}
		if (!ok) break;
	}
	if (a[vs][vt] < inf) printf("%d\n", a[vs][vt]); else printf("no solution\n");
	return 0;
}

