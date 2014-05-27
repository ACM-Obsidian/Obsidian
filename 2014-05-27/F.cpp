#include <cstdio>
#include <algorithm>
int a[100][100][6], b[100][100], val[5], u[5], v[100], now[5], n, p, c, r, k;
char buf[100];
int rev(int x) {
	int n = p-2, s = 1;
	for (; n; n >>= 1, x = 1LL * x * x % p)
		if (n & 1) s = 1LL * x * s % p;
	return s;
}
void dfs(int i, int id, int &x, int &y) {
	if (i == n) {
		int flag = 1;
		for (int u = 0; u < n-r; u++)
			for (int v = u+1; v < n-r; v++)
				if (now[u] > now[v]) flag = p-flag;
		int nowx = 0, nowy = flag;
		for (int u = 0; u < n-r; u++) {
			int tmpx = a[r+u][r+now[u]][id+1], tmpy = a[r+u][r+now[u]][0];
			for (int v = 0; v < k; v++)
				if (v != id)
					tmpy = (tmpy + 1LL*val[v]*a[r+u][r+now[u]][v+1]) % p;
			nowx = (1LL*nowx*tmpy+1LL*nowy*tmpx) % p;
			nowy = 1LL*tmpy*nowy % p;
		}
		x = (x+nowx)%p, y = (y+nowy)%p;
	} else {
		for (int j = r; j < n; j++)
			if (!u[j-r]) {
				now[i-r] = j-r, u[j-r] = 1;
				dfs(i+1, id, x, y);
				u[j-r] = 0;
			}
	}
}
void output() {
	puts("Yes");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%d%c", (b[i][j] < 0 ? val[-b[i][j]-1] : b[i][j]), " \n"[j == n-1]);
}
int main() {
	scanf("%d%d%d", &n, &p, &c);
	k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			scanf("%s", buf);
			if (buf[0] == '*') {
				k++;
				v[j] = 1;
				a[i][j][k] = 1;
				b[i][j] = -k;
			} else {
				sscanf(buf, "%d", &b[i][j]);
				a[i][j][0] = b[i][j];
			}
		}
	int j = n-1; while (j >= n-k && j >= 0 && v[j]) j--;
	for (int i = 0; i < n-k; i++)
		if (v[i]) {
			for (int t = 0; t < n; t++)
				for (int u = 0; u <= k; u++)
					std::swap(a[t][i][u], a[t][j][u]);
			std::swap(v[i], v[j]);
			while (j >= n-k && v[j]) j--;
			c = (p-c)%p;
		}
	int det = 1;
	for (int i = 0; i < n-k; i++) {
		int j = i; while (j < n && a[j][i][0] == 0) j++;
		if (j == n) {
			det = 0;
			break;
		}
		if (i != j) {
			det = (p-det)%p;
			for (int t = 0; t < n; t++)
				for (int u = 0; u <= k; u++)
					std::swap(a[i][t][u], a[j][t][u]);
		}
		det = 1LL*det*a[i][i][0]%p;
		int c = rev(a[i][i][0]);
		for (int t = i+1; t < n; t++) {
			int tmp = 1LL * c * (p - a[t][i][0]) % p;
			for (int u = i; u < n; u++)
				for (int v = 0; v <= k; v++)
					a[t][u][v] = (a[t][u][v] + 1LL * tmp * a[i][u][v]) % p;
		}
	}
	if (det == 0 && c != 0) {
		puts("No");
		return 0;
	} else if (det == 0) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (b[i][j] < 0) b[i][j] = 0;
		output();
		return 0;
	}
	c = 1LL * c * rev(det) % p;
	r = std::max(n-k, 0);
	for (int i = 0; i < k; i++)
		for (int T = 0; T < 10; T++) {
			for (int j = 0; j < k; j++)
				if (i != j)
					val[j] = ((((long long)rand()) << 31) + rand()) % p;
			int x = 0, y = 0;
			dfs(r, i, x, y);
			if (x != 0 || y == c) {
				val[i] = 1LL * (c-y+p) * rev(x) % p;
				output();
				return 0;
			}
		}
	puts("No");
	return 0;
}
