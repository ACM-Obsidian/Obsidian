#include <cstdio>
int match[50000], d[15], p[15], x[15], n;
int encode(int *x, int n) {
	int s = 0, t = 1;
	for (int i = 0; i < n; i++) s += x[i] * t, t *= d[i];
	return s;
}
void decode(int s, int n, int *x) {
	for (int i = 0; i < n; i++)
		x[i] = s % d[i], s /= d[i];
}
void addmatch(int x, int y) {
	match[x] = y, match[y] = x;
}
void duplicate(int n, int delta) {
	for (int i = 1; i < d[n-1]; i++)
		for (int j = 0; j < delta; j++)
			if (match[j] == -1) match[i*delta+j] = -1;
			else match[i*delta+j] = match[j]+i*delta;
}
void findmatch(int n, int *x) {
	int flag = 1, delta = 1;
	for (int i = 0; i < n; i++) flag &= d[i] & 1;
	for (int i = 0; i < n-1; i++) delta *= d[i];
	if (!flag) {
		if (n == 1) {
			for (int i = 0; i < d[0]; i += 2) addmatch(i, i+1);
		} else {
			flag = 1;
			for (int i = 0; i < n-1; i++) flag &= d[i] & 1;
			if (flag) {
				for (int i = 0; i < n-1; i++) x[i] = 0;
				findmatch(n-1, x);
				duplicate(n, delta);
				for (int i = 0; i < d[n-1]; i += 2) addmatch(delta*i, delta*(i+1));
			} else {
				findmatch(n-1, x);
				duplicate(n, delta);
			}
		}
	} else {
		if (n == 1) {
			for (int i = 0; i < x[0]; i += 2) addmatch(i, i+1);
			for (int i = x[0]+1; i < d[0]; i += 2) addmatch(i, i+1);
			match[x[0]] = -1;
		} else if (x[n-1] & 1) {
			int dir = -1;
			if (x[n-2] == 0) dir = 1;
			x[n-2] += dir;
			findmatch(n-1, x);
			duplicate(n, delta);
			int base1 = encode(x, n-1);
			x[n-2] -= dir;
			int base = encode(x, n-1), base2 = match[base];
			for (int i = 1; i < x[n-1]; i += 2) addmatch(delta*i+base, delta*(i+1)+base);
			for (int i = x[n-1]+1; i < d[n-1]-1; i += 2) addmatch(delta*i+base, delta*(i+1)+base);
			for (int i = 0; i < d[n-1]-1; i += 2) addmatch(delta*i+base1, delta*(i+1)+base1);
			addmatch(delta*(d[n-1]-1)+base1, delta*(d[n-1]-1)+base);
			for (int i = 1; i < d[n-1]; i += 2) addmatch(delta*i+base2, delta*(i+1)+base2);
			addmatch(base, base2);
			match[x[n-1]*delta+base] = -1;
		} else {
			findmatch(n-1, x);
			duplicate(n, delta);
			int base = encode(x, n-1);
			for (int i = 0; i < x[n-1]; i += 2) addmatch(delta*i+base, delta*(i+1)+base);
			for (int i = x[n-1]+1; i < d[n-1]; i += 2) addmatch(delta*i+base, delta*(i+1)+base);
			match[x[n-1]*delta+base] = -1;
		}
	}
}
int scanmove() {
	int d; char ch;
	scanf("%d %c", &d, &ch), d--;
	if (ch == '?') return -1;
	if (ch == '+') p[d]++;
	else p[d]--;
	return 0;
}
void printmove() {
	decode(match[encode(p, n)], n, x);
	int d = 0;
	while (d < n && x[d] == p[d]) d++;
	printf("%d %c\n", d+1, (x[d] < p[d] ? '-' : '+'));
	fflush(stdout);
	for (int i = 0; i < n; i++) p[d] = x[d];
}
void solve() {
	for (int i = 0; i < n; i++) scanf("%d", &d[i]), d[i]++;
	for (int i = 0; i < n; i++) scanf("%d", &p[i]);
	int flag1 = 1, flag2 = 0;
	for (int i = 0; i < n; i++) flag1 &= d[i] & 1;
	for (int i = 0; i < n; i++) flag2 = (flag2 + p[i]) & 1;
	if (flag1 && !flag2) {
		puts("Bob"); fflush(stdout);
		for (int i = 0; i < n; i++) x[i] = p[i];
		findmatch(n, x);
	} else {
		puts("Alice"); fflush(stdout);
		if (flag1) {
			for (int i = 0; i < n; i++) x[i] = 0;
			findmatch(n, x);
		} else {
			findmatch(n, x);
		}
		printmove();
	}
	while (1) {
		if (scanmove() == -1)
			break;
		printmove();
	}
}
int main() {
	while (scanf("%d", &n), n) solve();
	return 0;
}
