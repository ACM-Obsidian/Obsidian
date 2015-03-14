#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline char T (int x) {
	if (x <= 9) return x + '0';
	else return x - 10 + 'A';
}

void output_b (int);

void output_a (int k) {
	if (k == 2) printf("10");
	else {
		output_a(k - 1);
		output_b(k - 1);
		putchar(T(k - 1));
	}
}

void output_b (int k) {
	if (k == 2) printf("1");
	else {
		output_a(k - 1);
		output_b(k - 1);
	}
}

int main () {
	freopen("balanced.in", "r", stdin);
	freopen("balanced.out", "w", stdout);
	int k; scanf("%d", &k);
	output_a(k);
	output_b(k);
	printf("\n");
	return 0;
}
