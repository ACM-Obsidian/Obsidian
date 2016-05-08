#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000001;
const int MAXM = 10000001;

struct Edge {
	int y, z; Edge *next;
}*a[MAXN], POOL[MAXM], *data = POOL;

int n, seed;

void addEdge(int x, int y, int z) {
	Edge *tmp = data++;
	tmp->y = y; tmp->z = z; tmp->next = a[x]; a[x] = tmp;
}

void buildGraph(int N, int Seed) {
	int nextRand = Seed;

	for (int x = 1; x <= N; x++) {
		int w = x % 10 + 1;
		int d = 10 - w;
		for (int i = 1; i <= d; i++) {
			addEdge(x, nextRand % N + 1, w);
			nextRand = (long long)nextRand * 233 % N;
		}
		addEdge(x, x % N + 1, w);
	}
}

int dis[MAXN];
priority_queue<pair<int, int> > Q;

int main(void) {
	// freopen("in" ,"r", stdin);
	int T; scanf("%d", &T); while (T--) {
		memset(a, 0, sizeof a);
		data = POOL;
		scanf("%d%d", &n, &seed);
		buildGraph(n, seed);

		while (!Q.empty()) Q.pop();
		Q.push(std::make_pair(0, 1));
		memset(dis, 0x3f, sizeof dis); dis[1] = 0;
		while (true) {
			while (!Q.empty() && dis[Q.top().second] != -Q.top().first)
				Q.pop();
			if (Q.empty()) break;
			int now = Q.top().second; Q.pop();
			if (now == n) break;
			for (Edge *p = a[now]; p; p = p->next) if (dis[p->y] > dis[now] + p->z) {
				dis[p->y] = dis[now] + p->z;
				Q.push(std::make_pair(-dis[p->y], p->y));
			}
		}
		printf("%d\n", dis[n]);
	}
	return 0;
}
