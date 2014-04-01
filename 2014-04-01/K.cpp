#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Edge {
	int y, z; Edge *next;
}*a[MAXN], POOL[MAXN << 2], *data;

inline void AddEdge(int x, int y, int z) {
	Edge *tmp = data++;
	tmp->y = y; tmp->z = z; tmp->next = a[x]; a[x] = tmp;
}

inline void clear(void) {
	memset(a, 0, sizeof a);
	data = POOL;
}

int n, m, vx, vy, tx, ty, vs, vt;
int R[2][110][110];

inline int Id(int x, int y) {
	return x * (m + 1) + y;
}
inline int turn_from(int x, int y, int dir) {
	return Id(x, y) * 8 + dir;
}
inline int straight_from(int x, int y, int dir) {
	return Id(x, y) * 8 + dir + 4;
}

int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
int Index[4][3] = {{1, -1, 0}, {0, 0, -1}, {1, 0, 0}, {0, 0, 0}};

inline int ok(int x, int y, int k) {
	int nx = x + dx[k], ny = y + dy[k];
	if (nx < 0 || nx > n || ny < 0 || ny > m) return false;
	return true;
}

priority_queue<pair<int, int> > Q;

int dis[MAXN], inf;

inline int Dijkstra(void) {
	while (!Q.empty()) Q.pop();
	memset(dis, 0x3f, sizeof dis); inf = dis[0]; dis[vs] = 0; Q.push(make_pair(0, vs));
	for (int i = 0; i < vt; i++) {
		while (!Q.empty() && dis[Q.top().second] != -Q.top().first) Q.pop();
		if (Q.empty()) break;
		int now = Q.top().second; Q.pop();
		for (Edge *p = a[now]; p; p = p->next) if (dis[p->y] > dis[now] + p->z) {
			Q.push(make_pair(-(dis[p->y] = dis[now] + p->z), p->y));
		}
	}
	return dis[vt];
}

int main(void) {
	freopen("steam.in", "r", stdin);
	int kase = 0;
	while (scanf("%d%d%d%d%d%d", &n, &m, &vx, &vy, &tx, &ty), n || m || vx || vy || tx || ty) {
		clear();
		printf("Case %d: ", ++kase);
		n--, m--; vx--, vy--, tx--, ty--;
		for (int i = 0; i < (2 * n) + 1; i++) {
			int k = i & 1;
			for (int j = 0; j < m + k; j++)
				scanf("%d", &R[k][i / 2][j]);
		}
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++) {
				for (int k = 0; k < 4; k++) if (ok(i, j, k)) {
					int nx = i + dx[k], ny = j + dy[k], op = k ^ 2;
					int p = Index[k][0], px = i + Index[k][1], py = j + Index[k][2];
					if (R[p][px][py]) {
						for (int lk = 0; lk < 4; lk++) {
							if (lk == op) {
							//	printf("straight(%d %d %d) to straight(%d %d %d) %d\n", i, j, lk, nx, ny, op, R[p][px][py]);
								AddEdge(straight_from(i, j, lk), straight_from(nx, ny, op), R[p][px][py]);
							//	printf("straight(%d %d %d) to turn(%d %d %d) %d\n", i, j, lk, nx, ny, op, R[p][px][py] * 2);
								AddEdge(straight_from(i, j, lk), turn_from(nx, ny, op), R[p][px][py] * 2);
							} else {
							//	printf("turn(%d %d %d) to straight(%d %d %d) %d\n", i, j, lk, nx, ny, op, R[p][px][py] * 2);
								AddEdge(turn_from(i, j, lk), straight_from(nx, ny, op), R[p][px][py] * 2);
							//	printf("turn(%d %d %d) to turn(%d %d %d) %d\n", i, j, lk, nx, ny, op, R[p][px][py] * 2);
								AddEdge(turn_from(i, j, lk), turn_from(nx, ny, op), R[p][px][py] * 2);
							}
						}
					}
				}
			}
		vs = straight_from(n, m, 3) + 1, vt = vs + 1;
		for (int k = 0; k < 4; k++) {
			AddEdge(vs, turn_from(vx, vy, k), 0);
			AddEdge(turn_from(tx, ty, k), vt, 0);
		}
		int Ans = Dijkstra();
		if (Ans < inf) printf("%d\n", Ans); else puts("Impossible");
	}
	return 0;
}

