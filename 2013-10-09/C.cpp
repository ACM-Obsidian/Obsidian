#include <cstdio>
#include <cstring>
#include <cstdlib>
int f[1001][10][10], n;
char s[1003], t[1003];
int main() {
	for (; scanf("%s%s", s, t) != EOF; ) {
		n = strlen(s);
		for (int i = 0; i < n; i++) s[i] -= 48, t[i] -= 48;
		s[n] = s[n+1] = t[n] = t[n+1] = 0;
		memset(f, 0x3F, sizeof f);
		for (int i = -4; i <= 5; i++)
			for (int j = -4; j <= 5; j++) {
				int a = s[0]+i, b = s[1]+j;
				if (a < 0) a += 10;
				if (a >= 10) a -= 10;
				if (b < 0) b += 10;
				if (b >= 10) b -= 10;
				if (f[0][a][b] > abs(i)+abs(j))
					f[0][a][b] = abs(i)+abs(j);
			}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 10; j++)
				for (int k = 0; k < 10; k++)
					for (int p = -4; p <= 5; p++)
						for (int q = -4; q <= 5; q++) {
							int r = (t[i]-j-p-q) % 10;
							if (r < -4) r += 10;
							if (r > 5) r -= 10;
							int a = (k+p+q) % 10, b = (s[i+2]+q) % 10;
							if (a < 0) a += 10;
							if (b < 0) b += 10;
							if (f[i+1][a][b] > f[i][j][k] + abs(p)+abs(q)+abs(r))
								f[i+1][a][b] = f[i][j][k] + abs(p)+abs(q)+abs(r);
						}
		int ans = ~0U>>1;
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				if (f[n][j][k] < ans) ans = f[n][j][k];
		printf("%d\n", ans);
	}
	return 0;
}