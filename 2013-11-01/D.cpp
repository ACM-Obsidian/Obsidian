#include <cstdio>
#include <cstring>
const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int sum[100], suml[100], year[100], month[100], day[100], leap[100], after[100], afterl[100], op[100], f[2300][101], g[2300][101], ys, yf, n;
char tmps[100], tmpt[100], tmp[100], rec[100][100];
int main() {
	freopen("holidays.in","r",stdin);
	freopen("holidays.out","w",stdout);
	scanf("%d%d%d\n", &ys, &yf, &n);
	for (int i = 0; i < n; i++) {
		int monthh, dayh;
		scanf("%[^\n]\n", rec[i]);
		sscanf(rec[i], "%s%d, %s%s%d", tmps, &day[i], tmp, tmpt, &dayh);
		for (month[i] = 0; month[i] < 12; month[i]++)
			if (strcmp(months[month[i]], tmps) == 0) break;
		for (monthh = 0; monthh < 12; monthh++)
			if (strcmp(months[monthh], tmpt) == 0) break;
		leap[i] = (monthh == 1 && dayh == 29);
		after[i] = (monthh > month[i] || monthh == month[i] && dayh > day[i]);
		if (leap[i]) afterl[i] = after[i], after[i] = 0;
		if (strcmp(tmp, "added") == 0) op[i] = 1;
		else op[i] = -1;
		sum[i+1] = (!leap[i] ? op[i] : 0) + sum[i];
		suml[i+1] = (leap[i] ? op[i] : 0) + suml[i];
	}
	memset(f, 0xC0, sizeof f);
	f[ys-1][0] = 0;
	for (int y = ys; y <= yf; y++)
		for (int num = 0; num <= n; num++) {
			int cur = 0, leapy = !(y % 4) && (y % 100 || !(y % 400));
			for (int pre = num; pre >= 0; pre--) {
				if (pre < num-1 && (month[pre] > month[pre+1] || month[pre] == month[pre+1] && day[pre] >= day[pre+1])
						|| pre < num && month[pre] == 1 && day[pre] == 29 && !leapy)
					break;
				if (pre < num && (after[pre] || afterl[pre] && leapy))
					cur += op[pre];
				int val = f[y-1][pre] + sum[pre]+cur;
				if (leapy) val += suml[pre];
				if (val > f[y][num]) f[y][num] = val, g[y][num] = pre;
			}
		}
	for (int y = yf, m = n; y >= ys; m = g[y][m], y--)
		for (int i = g[y][m]; i < m; i++) year[i] = y;
	if (f[yf][n] < 0) puts("-1");
	else {
		printf("%d\n", f[yf][n]);
		for (int i = 0; i < n; i++) {
			int pos = 0; for (; rec[i][pos] != ','; pos++);
			rec[i][pos] = 0; printf("%s %d,%s\n", rec[i], year[i], rec[i]+pos+1);
		}
	}
	return 0;
}
