#include <cstdio>
int a[10][5000], t[10];
int main() {
	a[0][0] = 1;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 4600; j++)
			if (a[i][j])
				for (int k = 0; k < 10; k++)
					a[i+1][j+k*(1<<i)] += a[i][j];
	for (int i = 0; i <= 9; i++)
		for (int j = 1; j < 4600; j++) a[i][j] += a[i][j-1];
	int T; scanf("%d", &T);
	for (int _ = 1; _ <= T; _++) {
		int A, B;
		scanf("%d%d", &A, &B); B++;
		int x = 0, ans = 0;
		for (int i = 0; A; A /= 10, i++)
			x += A % 10 * (1 << i);
		for (int i = 0; i < 9; i++)
			t[i] = B % 10, B /= 10;
		for (int i = 8, y = 0; i >= 0; y += t[i] * (1 << i), i--)
			for (int j = 0; j < t[i]; j++)
				if (y + j * (1 << i) <= x)
					ans += a[i][x - y - j*(1<<i)];
		printf("Case #%d: %d\n", _, ans);
	}
	return 0;
}
