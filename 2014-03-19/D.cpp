#include <cstdio>
#include <cstring>
#include <algorithm>
int f[2][10][100000], n;
int ansm, anss, ansn, anst;
std::pair<int,int> pre[10][100000], q[2000000];
bool check(int i) {
	ansm = pre[i][0].second, anss = pre[i][0].first;
	ansn = f[1][i][0] - ansm, anst = i;
	if (ansm + ansn <= 6) {
		int tmp = 0;
		for (int j = 0; j < ansm; j++) tmp = tmp*10+anss;
		for (int j = 0; j < ansn; j++) tmp = tmp*10+anst;
		return tmp == n;
	} else return 0;
}
int main() {
	while (scanf("%d", &n), n) {
		printf("%d: ", n);
		memset(f, -1, sizeof f);
		int l = 0, r = 0;
		for (int i = 1; i <= 9; i++)
			if (f[0][i][i%n] == -1)
				q[r++] = std::make_pair(i, i%n), f[0][i][i%n] = 1;
		while (l < r) {
			int s = 0, i = q[l].first, j = q[l].second;
			if (i <= 0) s = 1, i = -i;
			l++;
			if (!s) {
				for (int k = 0; k < i; k++)
					if (f[1][k][(j*10+k)%n] == -1 || (j*10+k)%n == 0) {
						f[1][k][(j*10+k)%n] = f[s][i][j]+1;
						pre[k][(j*10+k)%n] = std::make_pair(i, f[s][i][j]);
						if ((j*10+k)%n == 0 && !check(k))
							goto success;
						q[r++] = std::make_pair(-k, (j*10+k)%n);
					}
			}
			if (f[s][i][(j*10+i)%n] == -1 || s == 1 && (j*10+i)%n == 0) {
				f[s][i][(j*10+i)%n] = f[s][i][j]+1;
				if (s) pre[i][(j*10+i)%n] = pre[i][j];
				if (s == 1 && (j*10+i)%n == 0 && !check(i))
					goto success;
				q[r++] = std::make_pair(s ? -i : i, (j*10+i)%n);
			}
			if (!s) {
				for (int k = i+1; k <= 9; k++)
					if (f[1][k][(j*10+k)%n] == -1 || (j*10+k)%n == 0) {
						f[1][k][(j*10+k)%n] = f[s][i][j]+1;
						pre[k][(j*10+k)%n] = std::make_pair(i, f[s][i][j]);
						if ((j*10+k)%n == 0 && !check(k))
							goto success;
						q[r++] = std::make_pair(-k, (j*10+k)%n);
					}
			}
		}
success:
		for (int i = 0; i < r; i++) f[q[i].first <= 0][abs(q[i].first)][q[i].second] = -1;
		printf("%d %d %d %d\n", ansm, anss, ansn, anst);
	}
	return 0;
}
