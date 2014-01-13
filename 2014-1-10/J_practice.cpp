#include <cstdio>
void solve() {
	int a, b, c, p = 0;
	scanf("%d%d%d", &a, &b, &c);
	printf("0 ");
	switch (c%3) {
		case 0:
			for (int i = 1; i <= c/3; i++)
				printf("%d ", i*3);
			for (int i = c/3; i >= 0; i--)
				printf("%d ", i*3+1);
			for (int i = 0; i <= c/3; i++)
				printf("%d ", i*3+2);
			p = c+2;
			a -= 2;
			break;
		case 1:
			for (int i = 1; i <= c/3+1; i++)
				printf("%d ", i*3);
			for (int i = c/3; i >= 0; i--)
				printf("%d ", i*3+1);
			for (int i = 0; i <= c/3; i++)
				printf("%d ", i*3+2);
			printf("%d ", c+3);
			p = c+3;
			a--, b -= 2;
			break;
		case 2:
			for (int i = 1; i <= c/3+1; i++)
				printf("%d ", i*3);
			for (int i = c/3; i >= 0; i--)
				printf("%d ", i*3+2);
			for (int i = 0; i <= c/3+1; i++)
				printf("%d ", i*3+1);
			p = c+2;
			a -= 2;
	}
	while (a > 1) printf("%d ", ++p), a--;
	if (b%2) {
		for (int i = 1; i <= b/2+1; i++)
			printf("%d ", p+i*2);
		for (int i = b/2; i > 0; i--)
			printf("%d ", p+i*2+1);
		printf("%d\n", p+1);
	} else {
		for (int i = 1; i <= b/2; i++)
			printf("%d ", p+i*2);
		for (int i = b/2; i > 0; i--)
			printf("%d ", p+i*2+1);
		printf("%d\n", p+1);
	}
}
int main() {
	freopen("jumping.in", "r", stdin);
	freopen("jumping.out", "w", stdout);
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
