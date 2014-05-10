#include <cstdio>
#include <cstring>
int f[10][11][10], trs[100], t[10][10], te[10], tmp[10][11];
char trt[100][12], dest[12];
void solve() {
	int n; scanf("%d", &n);
	int m = 0;
	memset(te, 0x3F, sizeof te);
	memset(t, 0x3F, sizeof t);
	memset(f, 0x3F, sizeof f);
	for (int i = 0; i < 10; i++) t[i][i] = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d%s", &trs[m], trt[m]);
		if (trt[m][1] == 0)
			if (trt[m][0] == 'e') te[trs[m]] = 1;
			else t[trt[m][0]-48][trs[m]] = 1;
		else m++;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < m; j++) {
			int flag = 0, l = strlen(trt[j]);
			for (int k = 0; k < l; k++)
				if (te[trt[j][k]-48] > 99999999) flag = 1;
			if (flag) continue;
			int tmp = 0;
			for (int k = 0; k < l; k++)
				tmp += te[trt[j][k]-48];
			if (tmp+1 < te[trs[j]]) te[trs[j]] = tmp+1;
		}
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				if (t[k][j] == 1 && te[k] < 99999999 && te[k]+1 < te[j])
					te[j] = te[k] + 1;
	}
	for (int i = 0; i < m; i++) {
		int l = strlen(trt[i]);
		for (int j = 0; j < l; j++) {
			int flag = 0;
			for (int k = 0; k < l; k++)
				if (k != j && te[trt[i][k]-48] > 99999999) flag = 1;
			if (flag) continue;
			int sum = 1;
			for (int k = 0; k < l; k++)
				if (k != j) sum += te[trt[i][k]-48];
			if (sum < t[trt[i][j]-48][trs[i]]) t[trt[i][j]-48][trs[i]] = sum;
		}
	}
	for (int k = 0; k < 10; k++)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (t[i][k] + t[k][j] < t[i][j]) t[i][j] = t[i][k] + t[k][j];
	scanf("%s", dest);
	n = strlen(dest);
	for (int i = 0; i < n; i++) f[i][i+1][dest[i]-48] = 0;
	for (int len = 1; len <= n; len++)
		for (int i = 0; i <= n-len; i++) {
			int j = i+len;
			if (len > 1)
				for (int t = 0; t < m; t++) {
					int k = trs[t], l = strlen(trt[t]);
					memset(tmp, 0x3F, sizeof tmp);
					for (int p = i+1; p <= j; p++) tmp[0][p] = f[i][p][trt[t][0]-48];
					tmp[0][i] = te[trt[t][0]-48];
					for (int u = 1; u < l; u++)
						for (int p = i; p <= j; p++) {
							if (tmp[u-1][p] + te[trt[t][u]-48] < tmp[u][p])
								tmp[u][p] = tmp[u-1][p] + te[trt[t][u]-48];
							for (int q = i; q < p; q++) {
								int x = tmp[u-1][q] + f[q][p][trt[t][u]-48];
								if (x < tmp[u][p]) tmp[u][p] = x;
							}
						}
					if (tmp[l-1][j]+1 < f[i][j][k]) f[i][j][k] = tmp[l-1][j]+1;
				}
			for (int p = 0; p < 10; p++)
				for (int k = 0; k < 10; k++)
					for (int l = 0; l < 10; l++)
						if (f[i][j][l] + t[l][k] < f[i][j][k]) f[i][j][k] = f[i][j][l] + t[l][k];
		}
	int ans = ~0U>>1;
	for (int i = 0; i < 10; i++)
		if (f[0][n][i] < ans) ans = f[0][n][i];
	if (ans > 88888888) puts("-1");
	else printf("%d\n", ans);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
