#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int bit[16], n, m;
int runcode[16];

void decode (int a) {
	memset(bit, 0, sizeof bit);
	int c = 0;
	while (a) {
		bit[c++] = (a & 1);
		a >>= 1;
	}
}
int encode (void) {
	int ans = 0;
	for (int i = n - 1; i >= 0; i--)
		ans = (ans << 1) | bit[i];
	return ans;
}
bool ok (void) {
	int trun[16], t = 0, c = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0 && bit[i] != bit[i - 1]) {
			trun[t++] = c, c = 0;
		}
		++c;
	}
	trun[t++] = c;
	if (t != m) return false;
	for (int i = 0; i < m; i++) if (trun[i] != runcode[i]) return false;
	return true;
}

const int N = 100010;

int que[N], ll, rr;
int dist[N];

int main () {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &bit[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &runcode[i]);
	}
	int init = encode();
	memset(dist, -1, sizeof dist);
	dist[init] = 0;
	ll = rr = 0;
	que[rr++] = init;
	int ans = -1;
	while (rr > ll) {
		int c = que[ll++];
		decode(c);
		if (ok()) {
			ans = dist[c];
			break;
		}
		for (int i = 0; i + 1 < n; i++) {
			swap(bit[i], bit[i + 1]);
			int nc = encode();
			if (dist[nc] == -1) {
				dist[nc] = dist[c] + 1;
				que[rr++] = nc;
			}
			swap(bit[i], bit[i + 1]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
