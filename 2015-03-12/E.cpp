#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;

const char *Ans_G4 = "B4-D4\nC2-C4\nA3-C3\nA5-A3\nC4-C2\nC1-C3\nC5-A5\nC7-C5\nD3-B3\nA3-C3\nD1-D3\nD3-B3\nD5-D3\nD7-D5\nD5-B5\nA5-C5\nE3-C3\nB3-D3\nE1-E3\nE4-E2\nF5-D5\nE7-E5\nG3-E3\nD3-F3\nG5-G3\nG3-E3\nE2-E4\nE4-E6\nC5-E5\nE6-E4\nE4-G4\n";

const char *Ans_D4 = "B4-D4\nC2-C4\nA3-C3\nA5-A3\nC4-C2\nC1-C3\nC5-A5\nC7-C5\nD3-B3\nA3-C3\nD1-D3\nD3-B3\nD5-D3\nD7-D5\nD5-B5\nA5-C5\nE3-C3\nB3-D3\nE1-E3\nE4-E2\nF5-D5\nE7-E5\nG3-E3\nD3-F3\nG5-G3\nG3-E3\nE2-E4\nE4-E6\nC5-E5\nE6-E4\nF4-D4\n";

typedef pair<int, int> coord;
#define X first
#define Y second

coord rotate (const coord& a) {
	return coord(-a.Y, a.X);
}

coord str2crd (char *a) {
	return coord(a[0] - 'A' - 3, a[1] - '1' - 3);
}

char hehe[4];
char* crd2str (coord a) {
	hehe[0] = a.X + 3 + 'A';
	hehe[1] = a.Y + 3 + '1';
	return hehe;
}

char ans[1010];

void turn (void) {
	char *p = ans;
	while (*p) {
		coord c = str2crd(p);
		c = rotate(c);
		char *k = crd2str(c);
		p[0] = k[0], p[1] = k[1];
		p += 3;
	}
}

int main () {
freopen("endspiel.in", "r", stdin);
freopen("endspiel.out", "w", stdout);
	char s[4]; scanf("%s", s);
	if (strcmp(s, "D4") == 0) {
		printf("%s", Ans_D4);
	} else if (strcmp(s, "G4") == 0) {
		printf("%s", Ans_G4);
	}
	else if (strcmp(s, "D7") == 0) {
		strcpy(ans, Ans_G4);
		turn();
		printf("%s\n", ans);
	} 
	else if (strcmp(s, "A4") == 0) {
		strcpy(ans, Ans_G4);
		turn();
		turn();
		printf("%s\n", ans);
	} 
	else if (strcmp(s, "D1") == 0) {
		strcpy(ans, Ans_G4);
		turn();
		turn();
		turn();
		printf("%s\n", ans);
	} 
	else {
		printf("Impossible\n");
	}
	return 0;
}
