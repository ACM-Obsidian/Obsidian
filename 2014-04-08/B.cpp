#include <cstdio>
#include <vector>
std::vector<int> G[27];
int d[27], stack[27], a[27], tmp[27], o[19], in[19][2], obs[256][27], n, m, g, u;
char s[4], t[4], op[19];
int check() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n+g; j++)
			if (a[j] < n) tmp[a[j]] = obs[i][a[j]];
			else {
				switch (op[a[j]-n]) {
					case '0': tmp[a[j]] = 0; break;
					case '1': tmp[a[j]] = 1; break;
					case 'a': case 'A': tmp[a[j]] = tmp[in[a[j]-n][0]] & tmp[in[a[j]-n][1]]; break;
					case 'o': case 'O': tmp[a[j]] = tmp[in[a[j]-n][0]] | tmp[in[a[j]-n][1]]; break;
					case 'x': case 'X': tmp[a[j]] = tmp[in[a[j]-n][0]] ^ tmp[in[a[j]-n][1]]; break;
					case 'n': case 'N': tmp[a[j]] = !tmp[in[a[j]-n][0]];
				}
				if (op[a[j]-n] >= 'A' && op[a[j]-n] <= 'Z') tmp[a[j]] = !tmp[a[j]];
			}
		//for (int j = 0; j < n+g; j++) printf("%d ", tmp[j]); puts("");
		for (int j = 0; j < u; j++)
			if (tmp[o[j]+n] != obs[i][n+j]) return 0;
	}
	return 1;
}
void solve() {
	for (int i = 0; i < n+g; i++) G[i].clear(), d[i] = 0;
	for (int i = 0; i < g; i++) {
		scanf("%c %s", &op[i], s);
		if (op[i] != 'n') scanf("%s", t);
		scanf("\n");
		int x, y;
		sscanf(s+1, "%d", &x), x--;
		if (op[i] != 'n') sscanf(t+1, "%d", &y), y--;
		if (s[0] == 'g') x += n;
		if (op[i] != 'n' && t[0] == 'g') y += n;
		G[x].push_back(i+n);
		if (op[i] != 'n') G[y].push_back(i+n);
		in[i][0] = x;
		if (op[i] != 'n') in[i][1] = y;
	}
	for (int i = 0; i < n+g; i++)
		for (int j = 0; j < G[i].size(); j++)
			d[G[i][j]]++;
	int top = 0;
	for (int i = 0; i < n+g; i++)
		if (d[i] == 0) stack[top++] = i;
	m = 0;
	while (top > 0) {
		int x = stack[--top];
		a[m++] = x;
		for (int i = 0; i < G[x].size(); i++) {
			d[G[x][i]]--;
			if (d[G[x][i]] == 0) stack[top++] = G[x][i];
		}
	}
	for (int i = 0; i < u; i++) scanf("%d", &o[i]), o[i]--;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n+u; j++) scanf("%d", &obs[i][j]);
	if (check()) puts("No faults detected");
	else {
		char rop; int rg, cnt = 0;
		for (int i = 0; i < g; i++) {
			char tmp = op[i];
			op[i] -= 32; if (check()) cnt++, rg = i, rop = op[i];
			op[i] = '0'; if (check()) cnt++, rg = i, rop = op[i];
			op[i] = '1'; if (check()) cnt++, rg = i, rop = op[i];
			op[i] = tmp;
		}
		if (cnt != 1) puts("Unable to totally classify the failure");
		else {
			printf("Gate %d is failing; output ", rg+1);
			if (rop == '0') puts("stuck at 0");
			else if (rop == '1') puts("stuck at 1");
			else puts("inverted");
		}
	}
}
int main() {
	int _ = 0;
	while (scanf("%d%d%d\n", &n, &g, &u), n)
		printf("Case %d: ", ++_), solve();
	return 0;
}
