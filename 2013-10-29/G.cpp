#include <cstdio>
#include <cstring>
char s[10001], t[10001], u[10001];
long long pow[10001];
int main() {
	freopen("given.in","r",stdin);
	freopen("given.out","w",stdout);
	pow[0] = 1;
	for (int i = 1; i < 5000; i++) pow[i] = pow[i-1]*13331;
	scanf("%s%s", t, s);
	int n = strlen(s);
	long long ht = 0;
	int flag = 0;
	for (int i = 0; i < n; i++) ht += (t[i]-48)*pow[i];
	for (int i = 0; i < n && !flag; i++) {
		for (int j = 0; j < n; j++)
			u[j] = (s[j] != s[(i+j)%n]);
		long long h = 0;
		for (int j = 0; j < n; j++) h += u[j]*pow[j];
		for (int j = n-1; j >= 0 && !flag; j--) {
			if (h == ht) flag = 1;
			h = (h - u[j]*pow[n-1])*13331 + u[j];
		}
	}
	puts(flag ? "Yes" : "No");
	return 0;
}
