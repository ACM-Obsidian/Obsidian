#include <cstdio>
const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
unsigned long long p, k, kc, mask[64];
char s[3];
int main() {
	int T;
	for (int i = 0; i < 64; i++) {
		int x = i >> 3, y = i & 7;
		mask[i] = 0;
		for (int d = 0; d < 8; d++)
			if (x+dx[d] >= 0 && x+dx[d] < 8 && y+dy[d] >= 0 && y+dy[d] < 8)
				mask[i] |= 1ULL << (x+dx[d])*8+(y+dy[d]);
	}
	for (scanf("%d", &T); T--; ) {
		int n; scanf("%d", &n);
		p = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			p |= 1ULL << (s[1]-49)*8+(s[0]-97);
		}
		k = 0;
		for (int i = 63; i >= 0; i--) {
			k |= (1ULL << i) - 1;
			kc = 0;
			for (int j = 0; j < 64; j++)
				if (k & 1ULL << j) kc |= mask[j];
			k &= -(1ULL << i);
			if ((p & kc) != p) k |= 1ULL << i;
		}
		printf("%llu\n", k);
	}
	return 0;
}
